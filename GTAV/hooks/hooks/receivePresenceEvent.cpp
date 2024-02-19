#include "pch.h"
#include "hooks/hooks.h"
#include "hooks/patterns.h"
#include "util/caller.h"
#include "rage/engine.h"
#include "menu/submenus/main/protections/protections_presence.h"
#include "menu/submenus/main/protections/protections_join_blocking.h"
#include "util/json.h"
#include "gui/util/notify.h"
#include "rage/classes/snSession.h"

namespace base::hooks {

	void hooks::writeGSItemHook(int index, rage::gs_session* data, const char* type) {
		if (menu::protections::join_blocking::vars::m_vars.m_block) {
			memset(data, 0, sizeof(rage::gs_session));
		}

		ogWriteGSItemHook(index, data, type);
	}

	bool hooks::updatePresenceAttributeIntHook(void* presence_data, int profile_index, char* attr, std::uint64_t value)
	{
		auto hash = rage::joaat(attr);
		if (menu::protections::join_blocking::vars::m_vars.m_block && (hash == RAGE_JOAAT("gstok") || hash == RAGE_JOAAT("gsid") || hash == RAGE_JOAAT("gstype") || hash == RAGE_JOAAT("gshost") || hash == RAGE_JOAAT("gsjoin")))
		{
			return true;
		}

		return ogUpdatePresenceAttributeIntHook(presence_data, profile_index, attr, value);
	}

	bool hooks::updatePresenceAttributeStringHook(void* presence_data, int profile_index, char* attr, char* value)
	{
		auto hash = rage::joaat(attr);
		if (menu::protections::join_blocking::vars::m_vars.m_block && hash == RAGE_JOAAT("gsinfo"))
		{
			return true;
		}

		// shouldn't have any side effects
		if (hash == RAGE_JOAAT("peeraddr"))
		{
			value = (char*)"";
		}

		return ogUpdatePresenceAttributeStringHook(presence_data, profile_index, attr, value);
	}

	bool receivePresenceEvent(uint64_t rcx, uint64_t rdx, const char** payload, uint64_t r9) {
		LOG(*payload);

		auto& var = menu::protections::presence::vars::m_vars;

		try {
			const char* key = "gm.evt";

			nlohmann::json json = nlohmann::json::parse(*payload);
			if (json[key].is_null()) {
				if (json["gta5.game.event"].is_null()) {
					return true;
				}

				key = "gta5.game.event";
			}

			nlohmann::json& event_payload = json[key];
			if (event_payload["e"].is_null() || event_payload["d"].is_null()) {
				return true;
			}

			uint32_t presence_hash = MISC::GET_HASH_KEY(event_payload["e"].get<std::string>().c_str());
			switch (presence_hash) {
			case PRESENCE_TEXT_MESSAGE: {
				switch (var.text_message_id)
				{
				case 0:
					break;
				case 1:
					return true;
					break;
				case 2:
					menu::notify::stacked(std::format("Blocked Text Message").c_str());
					return true;
					break;
				default:
					break;
				}

				break;
			}

			case PRESENCE_CREW_MESSAGE: {
				switch (var.crew_message_id)
				{
				case 0:
					break;
				case 1:
					return true;
					break;
				case 2:
					menu::notify::stacked(std::format("Blocked Crew Message").c_str());
					return true;
					break;
				default:
					break;
				}

				break;
			}

			case PRESENCE_GAME_INVITE: {
				std::string name = "LLLLLLLLLLLLLLLLLLLLLLLL";
				if (!event_payload["d"]["n"].is_null()) {
					name = event_payload["d"]["n"];
				}

				switch (var.crew_message_id)
				{
				case 0:
					break;
				case 1:
					return true;
					break;
				case 2:
					menu::notify::stacked(std::format("Blocked Game Invite From {}", name).c_str());
					return true;
					break;
				default:
					break;
				}

				break;
			}

			case PRESENCE_GAME_SERVER: {
				switch (var.game_award_id)
				{
				case 0:
					break;
				case 1:
					return true;
					break;
				case 2:
					menu::notify::stacked(std::format("Blocked Server Award").c_str());
					return true;
					break;
				default:
					break;
				}

				break;
			}

			case PRESENCE_ADMIN_INVITE: {
				switch (var.admin_invite_id)
				{
				case 0:
					break;
				case 1:
					return true;
					break;
				case 2:
					menu::notify::stacked(std::format("Blocked Admin Invite").c_str());
					return true;
					break;
				default:
					break;
				}

				break;
			}
			case PRESENCE_ROCKSTAR_MESSAGE: {
				switch (var.admin_invite_id)
				{
				case 0:
					break;
				case 1:
					return true;
					break;
				case 2:
					menu::notify::stacked(std::format("Blocked Rockstar Message").c_str());
					return true;
					break;
				default:
					break;
				}

				break;
			}

			case PRESENCE_BOUNTY: {
				std::string name = "LLLLLLLLLLLLLLLLLLLLLLLL";
				if (!event_payload["d"]["from"].is_null()) {
					name = event_payload["d"]["from"];
				}

				switch (var.bounty_id)
				{
				case 0:
					break;
				case 1:
					return true;
					break;
				case 2:
					menu::notify::stacked(std::format("Blocked Bounty From {}", name).c_str());
					return true;
					break;
				default:
					break;
				}

				break;
			}

			case PRESENCE_VOICE_SESSION_INVITE: {
				std::string name = "LLLLLLLLLLLLLLLLLLLLLLLL";
				if (!event_payload["d"]["from"].is_null()) {
					name = event_payload["d"]["from"];
				}

				switch (var.voice_invite_id)
				{
				case 0:
					break;
				case 1:
					return true;
					break;
				case 2:
					menu::notify::stacked(std::format("Blocked Voice Session Invite From {}", name).c_str());
					return true;
					break;
				default:
					break;
				}

				break;
			}
			case PRESENCE_STAT_UPDATE: {
				std::string name = "LLLLLLLLLLLLLLLLLLLLLLLL";
				if (!event_payload["d"]["from"].is_null()) {
					name = event_payload["d"]["from"];
				}

				switch (var.stat_update_id)
				{
				case 0:
					break;
				case 1:
					return true;
					break;
				case 2:
					menu::notify::stacked(std::format("Blocked Stat Update From {}", name).c_str());
					return true;
					break;
				default:
					break;
				}

				break;
			}
			}
		}
		catch (...) {
			return true;
		}

		return ogReceivePresenceEvent(rcx, rdx, payload, r9);
	}
}