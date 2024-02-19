#pragma once
#include "pch.h"
#include "rage/invoker/natives.h"
#include "util/math.h"
#include "rage/classes/CPed.h"
#include "rage/classes/CNetGamePlayer.h"
#include "rage/classes/GamerHandle.h"
namespace menu::player {
#pragma pack(push)
#pragma pack(1)
	struct player_context {
		std::string m_name = "";

		Player m_id = 0;
		Ped m_ped = 0;
		Entity m_entity = 0;
		Entity m_weapon_entity = 0;
		Vehicle m_vehicle = 0;

		CNetGamePlayer* m_net_player = nullptr;
		CPed* m_ped_ptr = nullptr;
		rage::rlGamerHandle m_gamer_handle;

		bool m_exists = false;
		bool m_connected = false;
		bool m_alive = false;
		bool m_in_vehicle = false;
		bool m_has_weapon_in_hand = false;
		bool m_is_aiming = false;
		bool m_is_modder = false;
		bool m_is_friend = false;
		bool m_is_script_host = false;
		bool m_rockstar_developer = false;

		Vector3 m_coords = {};
		Vector3 m_rotation = {};

		uint32_t m_weapon_hash = 0;
		uint32_t m_model = 0;
		float m_heading = 0.f;

		bool m_spectate = false;
	};
#pragma pack(pop)

	class PlayerManager {
	public:
		void update();
		void for_each(std::function<void(player_context&)> callback, bool bypass_excludes = false, bool bypass_ghost = false);
		player_context& random(int ignore_index = -1);

		player_context& get_player(int index);
		player_context& get_local_player();
		player_context& get_selected_player();
		bool is_excluded(Player id);
	private:
		player_context m_players[32];
	};

	PlayerManager* getPlayerManager();

	inline player_context& get_player(int index) {
		return getPlayerManager()->get_player(index);
	}

	inline player_context& get_local_player() {
		return getPlayerManager()->get_local_player();
	}

	inline player_context& get_selected_player() {
		return getPlayerManager()->get_selected_player();
	}

	inline player_context& random(int ignore_index = -1) {
		return getPlayerManager()->random(ignore_index);
	}

	inline void for_each(std::function<void(player_context&)> callback, bool bypass_excludes = false, bool bypass_ghost = false) {
		getPlayerManager()->for_each(callback, bypass_excludes, bypass_ghost);
	}

	inline void update() {
		getPlayerManager()->update();
	}

	inline bool is_excluded(Player id) {
		return getPlayerManager()->is_excluded(id);
	}
}