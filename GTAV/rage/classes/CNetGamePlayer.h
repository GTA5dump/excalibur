#pragma once
#include <cstdint>
#include "NetPlayer.h"
#include "ClanData.h"
#include "SessionInfo.h"

#pragma pack(push, 8)
class CNetGamePlayer : public rage::netPlayer {
public:
	class CPlayerInfo* m_player_info; //0x00A0
	uint32_t m_matchmaking_group; //0x0008
	bool m_is_spectating; //0x000C
	int16_t m_spectating_net_id; //0x000AD
	uint64_t unk_00B0; //0x00B0
	char unk_00B8; //0x00B8
	char pad_00B9[3]; //0x00B9
	uint32_t unk_00BC; //0x00BC
	uint32_t unk_00C0; //0x00C0
	char pad_00C4[4]; //0x00C4
	class ClanData m_clan_data; //0x00C8
	char m_crew_rank_title[25]; //0x0180
	bool m_is_rockstar_dev; //0x0199
	bool m_is_rockstar_qa; //0x019A
	bool m_is_cheater; //0x019B
	uint32_t unk_019C; //0x019C
	uint16_t unk_01A0; //0x01A0
	char unk_01A2; //0x01A2
	char pad_01A3; //0x01A3
	uint32_t m_phone_explosion_vehicle_net_id; //0x01A4
	uint16_t unk_01A8; //0x01A8
	bool m_has_started_transition; //0x01AA
	char pad_01AB[5]; //0x01AB
	class rage::rlSessionInfo m_transition_session_info; //0x01A3
	char pad_0273[16]; //0x0273
	uint64_t unk_0283; //0x0283
	uint64_t unk_028B; //0x028B
	uint32_t m_mute_count; //0x0293
	uint32_t m_mute_talkers_count; //0x0297
	char pad_029B[5]; //0x029B
	bool m_have_communication_privileges; //0x02A0
	uint16_t unk_02A1; //0x02A1
	uint16_t unk_02A3; //0x02A3
	char pad_02A5[2]; //0x02A5
	uint32_t m_cheat_report_ids[20]; //0x02A7
	uint32_t m_num_cheat_reports; //0x02F7
	uint8_t unk_02FB; //0x02FB
	char pad_02FC[3]; //0x02FC
	uint32_t unk_02FF; //0x02FF
	char unk_0303; //0x0303
	char pad_0304[3]; //0x0304
	uint32_t unk_0307; //0x0307
	uint32_t m_account_id; //0x030B
	uint32_t unk_030F; //0x030F
}; //Size: 0x0320
static_assert(sizeof(CNetGamePlayer) == 0x320);
#pragma pack(pop)