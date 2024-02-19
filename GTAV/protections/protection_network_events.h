#pragma once
#include "gui/options/core.h"
#include "gui/options/submenu.h"
#include "gui/options/option.h"
#include "gui/options/button.h"
#include "gui/options/submenu_option.h"
#include "gui/options/number.h"
#include "gui/options/toggle.h"
#include "gui/options/scroll.h"
#include "gui/options/break.h"

namespace menu {
	class protections_network_events_menu {
	public:
		void render();
		void update();
	};

	static protections_network_events_menu* getProtectionsNetworkEventsMenu() {
		static protections_network_events_menu instance;
		return &instance;
	}

	namespace protections::network_events::vars {
		struct variables {
			const char* block_network_kicks[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_network_kicks_id = 2;
			const char* block_network_crashes[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_network_crashes_id = 2;
			const char* block_desync[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_desync_id = 2;
			const char* block_explosion[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_explosion_id = 0;
			const char* block_ptfx[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_ptfx_id = 0;
			const char* block_kick_vote[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_kick_vote_id = 0;
			const char* block_clear_tasks[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_clear_tasks_id = 0;
			const char* block_ragdoll[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_ragdoll_id = 0;
			const char* block_request_control[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_request_control_id = 0;
			const char* block_remove_weapons[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_remove_weapons_id = 0;
			const char* block_give_weapons[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_give_weapons_id = 0;
			const char* block_sound_spam[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_sound_spam_id = 0;
			const char* block_damage[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_damage_id = 0;
		};

		extern variables m_vars;
	}

}