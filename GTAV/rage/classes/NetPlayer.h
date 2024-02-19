#pragma once
#include <cstdint>
#include "vector.h"
#include "GamerInfo.h"
#include "RTTI.h"
#include "CNonPhysicalPlayerData.h"

class CNetGamePlayer; //Bruh momento. The compiler really can't figure this one out, huh?
namespace rage {
#pragma pack(push, 8)
	class netPlayer : public atRTTI<netPlayer> {
	public:
		virtual ~netPlayer();
		virtual void Reset();
		virtual bool IsConnected();
		virtual const char* GetName();
		virtual void ActiveUpdate();
		virtual bool IsNetworkHost();
		virtual rlGamerInfo* GetGamerInfo();
		virtual void DestroyGamerDataSyncNode();

		char pad_0008[8]; //0x0008
		class CNonPhysicalPlayerData* m_non_physical_player; //0x0010
		uint32_t m_msg_id; //0x0018
		char pad_001C[4]; //0x001C
		uint8_t m_active_id; //0x0020
		uint8_t m_player_id; //0x0021
		char pad_0022[3]; //0x0022
		uint16_t m_complaints; //0x0026
		char pad_0027[17]; //0x0028
		class CNetGamePlayer* m_unk_net_player_list[10]; //0x0040
		uint32_t unk_0090; //0x0090
		uint64_t unk_0098; //0x0098
	}; //Size: 0x00A0
	static_assert(sizeof(netPlayer) == 0xA0);
#pragma pack(pop)
}