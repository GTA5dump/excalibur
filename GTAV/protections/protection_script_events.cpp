#include "pch.h"
#include "protection_script_events.h"
using namespace base::gui;
using namespace menu::protections::script_events::vars;

namespace menu::protections::script_events::vars {
	variables m_vars;

	void enable_all() {
		m_vars.block_script_kicks_id = 2;
		m_vars.block_script_crashes_id = 2;
		m_vars.block_bounty_id = 2;
		m_vars.block_ceo_kick_id = 2;
		m_vars.block_ceo_ban_id = 2;
		m_vars.block_ceo_money_id = 2;
		m_vars.block_clear_wanted_level_id = 2;
		m_vars.block_force_to_mission_id = 2;
		m_vars.block_give_collectible_id = 2;
		m_vars.block_gta_banner_id = 2;
		m_vars.block_network_bail_id = 2;
		m_vars.block_insurance_message_id = 2;
		m_vars.block_remote_off_radar_id = 2;
		m_vars.block_force_to_cutscene_id = 2;
		m_vars.block_force_to_cayo_id = 2;
		m_vars.block_force_teleport_id = 2;
		m_vars.block_script_sound_spam_id = 2;
		m_vars.block_spectate_message_id = 2;
		m_vars.block_transaction_error_id = 2;
		m_vars.block_vehicle_kick_id = 2;
		m_vars.block_force_to_activity_id = 2;
		m_vars.block_kick_from_interior_id = 2;
		m_vars.block_notifications_id = 2;
		m_vars.block_business_raids_id = 2;
		m_vars.block_rotate_cam_id = 2;
	}

	void disable_all() {
		m_vars.block_script_kicks_id = 0;
		m_vars.block_script_crashes_id = 0;
		m_vars.block_bounty_id = 0;
		m_vars.block_ceo_kick_id = 0;
		m_vars.block_ceo_ban_id = 0;
		m_vars.block_ceo_money_id = 0;
		m_vars.block_clear_wanted_level_id = 0;
		m_vars.block_force_to_mission_id = 0;
		m_vars.block_give_collectible_id = 0;
		m_vars.block_gta_banner_id = 0;
		m_vars.block_network_bail_id = 0;
		m_vars.block_insurance_message_id = 0;
		m_vars.block_remote_off_radar_id = 0;
		m_vars.block_force_to_cutscene_id = 0;
		m_vars.block_force_to_cayo_id = 0;
		m_vars.block_force_teleport_id = 0;
		m_vars.block_script_sound_spam_id = 0;
		m_vars.block_spectate_message_id = 0;
		m_vars.block_transaction_error_id = 0;
		m_vars.block_vehicle_kick_id = 0;
		m_vars.block_force_to_activity_id = 0;
		m_vars.block_kick_from_interior_id = 0;
		m_vars.block_notifications_id = 0;
		m_vars.block_business_raids_id = 0;
		m_vars.block_rotate_cam_id = 0;
	}

}

namespace menu {

	void protections_script_events_menu::render() {
		renderer::addSubmenu("Script Events", "Protections Script Events", [](core* core) {
			core->addOption(buttonOption("Enable All")
				.addClick([] { enable_all(); }));

			core->addOption(buttonOption("Disable All")
				.addClick([] { disable_all(); }));

			core->addOption(breakOption("Events"));

			core->addOption(scrollOption<const char*, std::size_t>("Crashes")
				.addScroll(&m_vars.block_script_crashes)
				.setPosition(&m_vars.block_script_crashes_id));

			core->addOption(scrollOption<const char*, std::size_t>("Kicks")
				.addScroll(&m_vars.block_script_kicks)
				.setPosition(&m_vars.block_script_kicks_id));

			core->addOption(scrollOption<const char*, std::size_t>("Bounty")
				.addScroll(&m_vars.block_bounty)
				.setPosition(&m_vars.block_bounty_id));

			core->addOption(scrollOption<const char*, std::size_t>("Ceo Kick")
				.addScroll(&m_vars.block_ceo_kick)
				.setPosition(&m_vars.block_ceo_kick_id));

			core->addOption(scrollOption<const char*, std::size_t>("Ceo Ban")
				.addScroll(&m_vars.block_ceo_ban)
				.setPosition(&m_vars.block_ceo_ban_id));

			core->addOption(scrollOption<const char*, std::size_t>("Ceo Money")
				.addScroll(&m_vars.block_ceo_money)
				.setPosition(&m_vars.block_ceo_money_id));

			core->addOption(scrollOption<const char*, std::size_t>("Clear Wanted Level")
				.addScroll(&m_vars.block_clear_wanted_level)
				.setPosition(&m_vars.block_clear_wanted_level_id));

			core->addOption(scrollOption<const char*, std::size_t>("Force to Mission")
				.addScroll(&m_vars.block_force_to_mission)
				.setPosition(&m_vars.block_force_to_mission_id));

			core->addOption(scrollOption<const char*, std::size_t>("Give Collectible")
				.addScroll(&m_vars.block_give_collectible)
				.setPosition(&m_vars.block_give_collectible_id));

			core->addOption(scrollOption<const char*, std::size_t>("Gta Banner")
				.addScroll(&m_vars.block_gta_banner)
				.setPosition(&m_vars.block_gta_banner_id));

			core->addOption(scrollOption<const char*, std::size_t>("Network Bail")
				.addScroll(&m_vars.block_network_bail)
				.setPosition(&m_vars.block_network_bail_id));

			core->addOption(scrollOption<const char*, std::size_t>("Insurance Message")
				.addScroll(&m_vars.block_insurance_message)
				.setPosition(&m_vars.block_insurance_message_id));

			core->addOption(scrollOption<const char*, std::size_t>("Remote off Radar")
				.addScroll(&m_vars.block_remote_off_radar)
				.setPosition(&m_vars.block_remote_off_radar_id));

			core->addOption(scrollOption<const char*, std::size_t>("Force to Cutscene")
				.addScroll(&m_vars.block_force_to_cutscene)
				.setPosition(&m_vars.block_force_to_cutscene_id));

			core->addOption(scrollOption<const char*, std::size_t>("Force to Cayo Perico")
				.addScroll(&m_vars.block_force_to_cayo)
				.setPosition(&m_vars.block_force_to_cayo_id));

			core->addOption(scrollOption<const char*, std::size_t>("Force Teleport")
				.addScroll(&m_vars.block_force_teleport)
				.setPosition(&m_vars.block_force_teleport_id));

			core->addOption(scrollOption<const char*, std::size_t>("Sound Spam")
				.addScroll(&m_vars.block_script_sound_spam)
				.setPosition(&m_vars.block_script_sound_spam_id));

			core->addOption(scrollOption<const char*, std::size_t>("Spectate Message")
				.addScroll(&m_vars.block_spectate_message)
				.setPosition(&m_vars.block_spectate_message_id));

			core->addOption(scrollOption<const char*, std::size_t>("Transaction Error")
				.addScroll(&m_vars.block_transaction_error)
				.setPosition(&m_vars.block_transaction_error_id));

			core->addOption(scrollOption<const char*, std::size_t>("Vehicle Kick")
				.addScroll(&m_vars.block_vehicle_kick)
				.setPosition(&m_vars.block_vehicle_kick_id));

			core->addOption(scrollOption<const char*, std::size_t>("Force to Activity")
				.addScroll(&m_vars.block_force_to_activity)
				.setPosition(&m_vars.block_force_to_activity_id));

			core->addOption(scrollOption<const char*, std::size_t>("Kick from Interior")
				.addScroll(&m_vars.block_kick_from_interior)
				.setPosition(&m_vars.block_kick_from_interior_id));

			core->addOption(scrollOption<const char*, std::size_t>("Notifications")
				.addScroll(&m_vars.block_notifications)
				.setPosition(&m_vars.block_notifications_id));

			core->addOption(scrollOption<const char*, std::size_t>("Business Raids")
				.addScroll(&m_vars.block_business_raids)
				.setPosition(&m_vars.block_business_raids_id));

			core->addOption(scrollOption<const char*, std::size_t>("Rotate Cam")
				.addScroll(&m_vars.block_rotate_cam)
				.setPosition(&m_vars.block_rotate_cam_id));
		});

	}

	void protections_script_events_menu::update() {
		render();

	}
}