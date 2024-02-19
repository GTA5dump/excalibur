#include "pch.h"
#include "players.h"
#include "menu/submenus/main/network/network_players.h"
namespace menu::player {
	void PlayerManager::update() {
		for (int i = 0; i < 32; i++) {
			player_context& player = m_players[i];

			player.m_id = i;
			player.m_name = PLAYER::GET_PLAYER_NAME(i);

			if (i == PLAYER::PLAYER_ID()) {
				player.m_ped = PLAYER::PLAYER_PED_ID();
			}
			else {
				player.m_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
			}

			player.m_exists = ENTITY::DOES_ENTITY_EXIST(player.m_ped);
			player.m_is_script_host = NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0) == player.m_id;

			if (player.m_id == PLAYER::PLAYER_ID()) {
				if (!NETWORK::NETWORK_IS_IN_SESSION()) {
					player.m_connected = true;
				}
			}

			if (player.m_exists) {
				WEAPON::GET_CURRENT_PED_WEAPON(player.m_ped, &player.m_weapon_hash, false);
				Any handle[13];
				NETWORK::NETWORK_HANDLE_FROM_PLAYER(player.m_id, &handle[0], 13);

				if (NETWORK::NETWORK_IS_HANDLE_VALID(&handle[0], 13)) {
					player.m_is_friend = NETWORK::NETWORK_IS_FRIEND(&handle[0]);
				}

				player.m_model = ENTITY::GET_ENTITY_MODEL(player.m_ped);
				player.m_vehicle = PED::GET_VEHICLE_PED_IS_IN(player.m_ped, false);
				player.m_alive = !ENTITY::IS_ENTITY_DEAD(player.m_ped, 0);
				player.m_heading = ENTITY::GET_ENTITY_HEADING(player.m_ped);
				player.m_coords = ENTITY::GET_ENTITY_COORDS(player.m_ped, true);
				player.m_in_vehicle = PED::IS_PED_IN_ANY_VEHICLE(player.m_ped, true);
				player.m_has_weapon_in_hand = (player.m_weapon_hash && player.m_weapon_hash != 2725352035);
				player.m_rotation = ENTITY::GET_ENTITY_ROTATION(player.m_ped, 2);
				player.m_weapon_entity = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(player.m_ped, 0);

				if (player.m_in_vehicle) {
					player.m_entity = player.m_vehicle;
				}
				else {
					player.m_entity = player.m_ped;
				}
			}
			if (player.m_connected) {
			}
		}
	}

	void PlayerManager::for_each(std::function<void(player_context&)> callback, bool bypass_excludes, bool bypass_ghost) {
		for (player_context& player : m_players) {
			if (!bypass_ghost) {
				if (!player.m_exists) continue;
			}

			if (player.m_connected) {
				if (!bypass_excludes) {
					if (is_excluded(player.m_id)) continue;
				}

				callback(player);
			}
		}
	}

	player_context& PlayerManager::get_player(int index) {
		if (index < 0 || index> 32) {
			static player_context nigger;
			memset(&nigger, 0, sizeof(nigger));
			return nigger;
		}

		return m_players[index];
	}

	player_context& PlayerManager::get_local_player() {
		return m_players[PLAYER::PLAYER_ID()];
	}

	player_context& PlayerManager::get_selected_player() {
		return m_players[menu::players::vars::m_vars.m_selected_player];
	}

	bool PlayerManager::is_excluded(Player id) {
		return false;
	}

	player_context& PlayerManager::random(int ignore_index) {
	start:
		std::random_device r;
		std::seed_seq seed2{ r(), r(), r(), r(), r(), r(), r(), r() };
		std::mt19937 rng(seed2);
		std::uniform_int_distribution<int> val(0, 31);

		int index = val(rng);

		if (!m_players[index].m_connected || index == ignore_index) {
			goto start;
		}

		return m_players[index];
	}

	PlayerManager* getPlayerManager() {
		static PlayerManager instance;
		return &instance;
	}
}