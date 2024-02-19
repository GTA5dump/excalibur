#include "pch.h"
#include "hooks/hooks.h"
#include "rage/classes/enums.h"
#include "rage/classes/netGameEvent.h"
namespace base::hooks {

	struct event_player_spawn {
		char _0x0000[0x18];
		char m_name[0x20];
	};


	void hooks::getNetworkEventDataHook(int64_t unk, rage::CEventNetwork* net_event) {
		switch (net_event->get_type()) {
		case rage::eEventNetworkType::CEventNetworkPlayerSpawn:
		{
			LOG("Someone just respawned frfr");
			break;
		}
		}
		return ogGetNetworkEventDataHook(unk, net_event);
	}
}