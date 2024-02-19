#include "pch.h"
#include "hooks/hooks.h"
#include "gui/util/notify.h"
#include "rage/engine.h"
#include "menu/util/scr_global.h"
#include "rage/classes/array_handler.h"

namespace base::hooks {

	bool hooks::receiveArrayBroadcastHook(rage::netArrayHandlerBase* array, CNetGamePlayer* sender, rage::datBitBuffer* buffer, int size, std::int16_t cycle) {
		
		int old_beast_index = -1;
		int participant_id = 0;
		auto beast = rage::engine::find_script_thread(RAGE_JOAAT("am_hunt_the_beast"));

		if (beast)
		{
			old_beast_index = *menu::script_local(beast->m_stack, menu::scr_locals::am_hunt_the_beast::broadcast_idx).at(1).at(6).as<int*>();
			if (beast->m_net_component) {
				//participant_id = beast->m_net_component->m_local_participant_index;
			}
			//	
		}

		bool result = ogReceiveArrayBroadcastHook(array, sender, buffer, size, cycle);

		if (beast && array->m_array == menu::script_local(beast->m_stack, menu::scr_locals::am_hunt_the_beast::broadcast_idx).as<void*>()
			&& old_beast_index
			!= *menu::script_local(beast->m_stack, menu::scr_locals::am_hunt_the_beast::broadcast_idx).at(1).at(6).as<int*>()
			&& *menu::script_local(beast->m_stack, menu::scr_locals::am_hunt_the_beast::broadcast_idx).at(1).at(6).as<int*>() == participant_id
			&& !rage::engine::has_bit_set(menu::script_local(beast->m_stack, menu::scr_locals::am_hunt_the_beast::player_broadcast_idx)
				.at(participant_id, 4)
				.at(3)
				.as<int*>(),
				1))
		{
			*menu::script_local(beast->m_stack, menu::scr_locals::am_hunt_the_beast::broadcast_idx).at(1).at(6).as<int*>() = -1;
			*menu::script_local(beast->m_stack, menu::scr_locals::am_hunt_the_beast::broadcast_idx).at(1).at(7).as<Player*>() = -1;
			
		}

		if ((array->m_array >= menu::scr_globals::globalplayer_bd.as<uint8_t*>()
			&& array->m_array <= menu::scr_globals::globalplayer_bd.at(31, sizeof(GlobalPlayerBDEntry) / 8).as<uint8_t*>())
			&& menu::scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[sender->m_player_id].RemoteWantedLevelPlayer != -1)
		{
			if (auto plyr = sender->m_player_id)
			{
				if (menu::scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[sender->m_player_id].RemoteWantedLevelPlayer == PLAYER::PLAYER_ID()) {

				}
			}

			menu::scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[sender->m_player_id].RemoteWantedLevelPlayer = -1;// reset locally
		}

		if (array->m_array == menu::scr_globals::gsbd.as<void*>() && *menu::scr_globals::gsbd.as<eFreemodeState*>() == eFreemodeState::CLOSING)
		{
			*menu::scr_globals::gsbd.as<eFreemodeState*>() = eFreemodeState::RUNNING;
		}

		return result;

	}
}