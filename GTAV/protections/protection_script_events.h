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
	class protections_script_events_menu {
	public:
		void render();
		void update();
	};

	static protections_script_events_menu* getProtectionsScriptEventsMenu() {
		static protections_script_events_menu instance;
		return &instance;
	}

	namespace protections::script_events::vars {
		struct variables {
			const char* block_script_kicks[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_script_kicks_id = 2;
			const char* block_script_crashes[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_script_crashes_id = 2;
			const char* block_bounty[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_bounty_id = 0;
			const char* block_ceo_kick[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_ceo_kick_id = 0;
			const char* block_ceo_ban[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_ceo_ban_id = 0;
			const char* block_ceo_money[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_ceo_money_id = 0;
			const char* block_clear_wanted_level[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_clear_wanted_level_id = 0;
			const char* block_force_to_mission[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_force_to_mission_id = 0;
			const char* block_give_collectible[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_give_collectible_id = 0;
			const char* block_gta_banner[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_gta_banner_id = 0;
			const char* block_network_bail[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_network_bail_id = 0;
			const char* block_insurance_message[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_insurance_message_id = 0;
			const char* block_remote_off_radar[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_remote_off_radar_id = 0;
			const char* block_force_to_cutscene[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_force_to_cutscene_id = 0;
			const char* block_force_to_cayo[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_force_to_cayo_id = 0;
			const char* block_force_teleport[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_force_teleport_id = 0;
			const char* block_script_sound_spam[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_script_sound_spam_id = 0;
			const char* block_spectate_message[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_spectate_message_id = 0;
			const char* block_transaction_error[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_transaction_error_id = 0;
			const char* block_vehicle_kick[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_vehicle_kick_id = 0;
			const char* block_force_to_activity[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_force_to_activity_id = 0;
			const char* block_kick_from_interior[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_kick_from_interior_id = 0;
			const char* block_notifications[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_notifications_id = 0;
			const char* block_business_raids[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_business_raids_id = 0;
			const char* block_rotate_cam[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_rotate_cam_id = 0;
		};

		extern variables m_vars;
	}

}