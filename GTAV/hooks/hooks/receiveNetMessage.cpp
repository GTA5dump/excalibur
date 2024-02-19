#include "pch.h"
#include "hooks/hooks.h"
#include "rage/classes/datBitBuffer.h"
#include "rage/classes/netGameEvent.h"

namespace base::hooks {
	
	class rate_limiter
	{
		std::uint32_t m_attempts_allowed_in_time_period;
		std::chrono::milliseconds m_time_period;
		std::chrono::system_clock::time_point m_last_event_time{};
		std::uint32_t m_num_attempts_allowed = 0;

	public:
		rate_limiter(std::chrono::milliseconds time_period, std::uint32_t num_allowed_attempts) :
			m_attempts_allowed_in_time_period(num_allowed_attempts),
			m_time_period(time_period)
		{
		}

		// Returns true if the rate limit has been exceeded
		bool process()
		{
			if (std::chrono::system_clock::now() - m_last_event_time < m_time_period)
			{
				if (++m_num_attempts_allowed > m_attempts_allowed_in_time_period)
					return true;
			}
			else
			{
				m_last_event_time = std::chrono::system_clock::now();
				m_num_attempts_allowed = 1;
			}
			return false;
		}

		// Check if the rate limit was exceeded by the last process() call. Use this to prevent the player from being flooded with notifications
		bool exceeded_last_process()
		{
			return (m_num_attempts_allowed - 1) == m_attempts_allowed_in_time_period;
		}
	};

	inline void gamer_handle_deserialize(rage::rlGamerHandle& hnd, rage::datBitBuffer& buf)
	{
		constexpr int PC_PLATFORM = 3;
		if ((hnd.m_platform = buf.Read<uint8_t>(8)) != PC_PLATFORM)
			return;

		buf.ReadInt64((int64_t*)&hnd.m_rockstar_id, 64);
		hnd.unk_0009 = buf.Read<uint8_t>(8);
	}

	inline bool is_kick_instruction(rage::datBitBuffer& buffer)
	{
		rage::rlGamerHandle sender, receiver;
		char name[18];
		gamer_handle_deserialize(sender, buffer);
		gamer_handle_deserialize(receiver, buffer);
		buffer.ReadString(name, 17);
		int instruction = buffer.Read<int>(32);
		return instruction == 8;
	}


	bool get_msg_type(rage::netConnection::eNetMessage& msgType, rage::datBitBuffer& buffer)
	{
		uint32_t pos;
		uint32_t magic;
		uint32_t length;
		uint32_t extended{};
		if ((buffer.m_flagBits & 2) != 0 || (buffer.m_flagBits & 1) == 0 ? (pos = buffer.m_curBit) : (pos = buffer.m_maxBit),
			buffer.m_bitsRead + 15 > pos || !buffer.ReadDword(&magic, 14) || magic != 0x3246 || !buffer.ReadDword(&extended, 1))
		{
			msgType = rage::netConnection::eNetMessage::MsgInvalid;
			return false;
		}
		length = extended ? 16 : 8;
		if ((buffer.m_flagBits & 1) == 0 ? (pos = buffer.m_curBit) : (pos = buffer.m_maxBit),
			length + buffer.m_bitsRead <= pos && buffer.ReadDword((uint32_t*)&msgType, length))
			return true;
		else
			return false;
	}

	rate_limiter m_host_migration_rate_limit{ 2s, 15 };
	rate_limiter m_play_sound_rate_limit{ 1s, 10 };

	bool hooks::receiveNetMessageHook(void* netConnectionManager, void* a2, rage::netConnection::InFrame* frame) {

		if (frame->get_event_type() != rage::netConnection::InFrame::EventType::FrameReceived) {
			//LOG_WARN("Bad Frame Execution - 1");
			return ogReceiveNetMessageHook(netConnectionManager, a2, frame);
		}

		if (frame->m_data == nullptr || frame->m_length == 0) {
			//LOG_WARN("Bad Frame Execution - 2");
			return ogReceiveNetMessageHook(netConnectionManager, a2, frame);
		}

		rage::datBitBuffer buffer(frame->m_data, frame->m_length);
		buffer.m_flagBits = 1;

		rage::netConnection::eNetMessage msgType;

		CNetGamePlayer* player{};
		for (auto p : (*patterns::network_player_mgr)->m_player_list) {
			if (p)
				if (p->m_msg_id == frame->m_msg_id) player = p;
		}

		if (!get_msg_type(msgType, buffer)) {
			//LOG_WARN("Bad Frame Execution - 3");
			return ogReceiveNetMessageHook(netConnectionManager, a2, frame);
		}


		if (player) {
			switch (msgType) {
			case rage::netConnection::eNetMessage::MsgTransitionGamerInstruction:
			{
				// this kick is still a thing
				if (is_kick_instruction(buffer))
				{
					LOG_WARN("Bad Frame Execution - 4");
					return true;
				}
				break;
			}
			case rage::netConnection::eNetMessage::MsgScriptMigrateHost:
			{
				if (m_host_migration_rate_limit.process())
				{
					if (m_host_migration_rate_limit.exceeded_last_process())
					{
						LOG_WARN("Bad Frame Execution - 5");
					}
					return true;
				}
				break;
			}
			case rage::netConnection::eNetMessage::MsgRadioStationSyncRequest:
			{
				return true;
				break;
			}
			case rage::netConnection::eNetMessage::MsgNetComplaint:
			{
				uint64_t host_token{};
				buffer.ReadQWord(&host_token, 64);

				std::vector<CNetGamePlayer*> players;

				uint32_t num_of_tokens{};
				buffer.ReadDword(&num_of_tokens, 32);
				return true; // block desync kicks as host
			}
			}
		}

		return ogReceiveNetMessageHook(netConnectionManager, a2, frame);
	}
}