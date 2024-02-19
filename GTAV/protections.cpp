#include "pch.h"
#include "protections.h"
#include "protections/protection_network_events.h"
#include "protections/protection_script_events.h"
#include "protections/protection_reports.h"
#include "protections/protection_detection.h"
#include "protections/protections_misc.h"
#include "protections/protections_presence.h"
#include "protections/protections_entity.h"
#include "protections/protection_syncs.h"
#include "protections/protections_join_blocking.h"
using namespace base::gui;
using namespace menu::protections::vars;

namespace menu::protections::vars {
	variables m_vars;
	
	void enable_all() {
		m_vars.m_fake_lag = true;
		m_vars.m_force_entities_visible = true;
		network_events::vars::m_vars.block_network_crashes_id = 2;
		network_events::vars::m_vars.block_network_kicks_id = 2;
		network_events::vars::m_vars.block_desync_id = 2;
		network_events::vars::m_vars.block_explosion_id = 2;
		network_events::vars::m_vars.block_ptfx_id = 2;
		network_events::vars::m_vars.block_kick_vote_id = 2;
		network_events::vars::m_vars.block_clear_tasks_id = 2;
		network_events::vars::m_vars.block_ragdoll_id = 2;
		network_events::vars::m_vars.block_request_control_id = 2;
		network_events::vars::m_vars.block_remove_weapons_id = 2;
		network_events::vars::m_vars.block_give_weapons_id = 2;
		network_events::vars::m_vars.block_sound_spam_id = 2;
		script_events::vars::m_vars.block_script_kicks_id = 2;
		script_events::vars::m_vars.block_script_crashes_id = 2;
		script_events::vars::m_vars.block_bounty_id = 2;
		script_events::vars::m_vars.block_ceo_kick_id = 2;
		script_events::vars::m_vars.block_ceo_ban_id = 2;
		script_events::vars::m_vars.block_ceo_money_id = 2;
		script_events::vars::m_vars.block_clear_wanted_level_id = 2;
		script_events::vars::m_vars.block_force_to_mission_id = 2;
		script_events::vars::m_vars.block_give_collectible_id = 2;
		script_events::vars::m_vars.block_gta_banner_id = 2;
		script_events::vars::m_vars.block_network_bail_id = 2;
		script_events::vars::m_vars.block_insurance_message_id = 2;
		script_events::vars::m_vars.block_remote_off_radar_id = 2;
		script_events::vars::m_vars.block_force_to_cutscene_id = 2;
		script_events::vars::m_vars.block_force_to_cayo_id = 2;
		script_events::vars::m_vars.block_force_teleport_id = 2;
		script_events::vars::m_vars.block_script_sound_spam_id = 2;
		script_events::vars::m_vars.block_spectate_message_id = 2;
		script_events::vars::m_vars.block_transaction_error_id = 2;
		script_events::vars::m_vars.block_vehicle_kick_id = 2;
		script_events::vars::m_vars.block_force_to_activity_id = 2;
		script_events::vars::m_vars.block_kick_from_interior_id = 2;
		script_events::vars::m_vars.block_notifications_id = 2;
		script_events::vars::m_vars.block_business_raids_id = 2;
		script_events::vars::m_vars.block_rotate_cam_id = 2;
		reports::vars::m_vars.block_arxan_reports_id = 2;
		reports::vars::m_vars.block_reports_id = 2;
	}

	void disable_all() {
		m_vars.m_fake_lag = false;
		m_vars.m_force_entities_visible = false;
		network_events::vars::m_vars.block_network_crashes_id = 0;
		network_events::vars::m_vars.block_network_kicks_id = 0;
		network_events::vars::m_vars.block_desync_id = 0;
		network_events::vars::m_vars.block_explosion_id = 0;
		network_events::vars::m_vars.block_ptfx_id = 0;
		network_events::vars::m_vars.block_kick_vote_id = 0;
		network_events::vars::m_vars.block_clear_tasks_id = 0;
		network_events::vars::m_vars.block_ragdoll_id = 0;
		network_events::vars::m_vars.block_request_control_id = 0;
		network_events::vars::m_vars.block_remove_weapons_id = 0;
		network_events::vars::m_vars.block_give_weapons_id = 0;
		network_events::vars::m_vars.block_sound_spam_id = 0;
		script_events::vars::m_vars.block_script_kicks_id = 0;
		script_events::vars::m_vars.block_script_crashes_id = 0;
		script_events::vars::m_vars.block_bounty_id = 0;
		script_events::vars::m_vars.block_ceo_kick_id = 0;
		script_events::vars::m_vars.block_ceo_ban_id = 0;
		script_events::vars::m_vars.block_ceo_money_id = 0;
		script_events::vars::m_vars.block_clear_wanted_level_id = 0;
		script_events::vars::m_vars.block_force_to_mission_id = 0;
		script_events::vars::m_vars.block_give_collectible_id = 0;
		script_events::vars::m_vars.block_gta_banner_id = 0;
		script_events::vars::m_vars.block_network_bail_id = 0;
		script_events::vars::m_vars.block_insurance_message_id = 0;
		script_events::vars::m_vars.block_remote_off_radar_id = 0;
		script_events::vars::m_vars.block_force_to_cutscene_id = 0;
		script_events::vars::m_vars.block_force_to_cayo_id = 0;
		script_events::vars::m_vars.block_force_teleport_id = 0;
		script_events::vars::m_vars.block_script_sound_spam_id = 0;
		script_events::vars::m_vars.block_spectate_message_id = 0;
		script_events::vars::m_vars.block_transaction_error_id = 0;
		script_events::vars::m_vars.block_vehicle_kick_id = 0;
		script_events::vars::m_vars.block_force_to_activity_id = 0;
		script_events::vars::m_vars.block_kick_from_interior_id = 0;
		script_events::vars::m_vars.block_notifications_id = 0;
		script_events::vars::m_vars.block_business_raids_id = 0;
		script_events::vars::m_vars.block_rotate_cam_id = 0;
		reports::vars::m_vars.block_arxan_reports_id = 0;
		reports::vars::m_vars.block_reports_id = 0;
	}

	const char* reaction_type[] = {
		"Death",						//
		"Aim",							//
		"Report",						//
		"Explode Loop",			//
		"Fire Loop",			//
		"Attachments",			//
		"RAC",					//
		"Arxan",						//
		"Crash Attempt",				//
		"Spectating You",				//
		"Money Drop",					//
		"Script Event Kick",					//
		"Script Migration",				//
		"Super Jump",					//
		"Join Timeout",					//
		"Invalid Model",				//
		"Info Change"					//
	}; inline std::size_t reaction_id = 0;

	const char* reaction_action[] = {
		"Explode", "Crash", "Kick", "Cage", "Kick From Vehicle", "Set on Fire", "Ragdoll", "Glitch Physics", "Black Screen", "Blame", "Remove Weapons", "Network Bail", "Force to Island", "Force to Apartment"
	}; inline std::size_t reaction_action_id = 0;

	const char* reaction_action1[] = {
		"Explode", "Crash", "Kick", "Cage", "Kick From Vehicle", "Set on Fire", "Ragdoll", "Glitch Physics", "Black Screen", "Blame", "Remove Weapons", "Network Bail", "Force to Island", "Force to Apartment"
	}; inline std::size_t reaction_action_id1 = 0;


	const char* reaction_action2[] = {
		"Explode", "Crash", "Kick", "Cage", "Kick From Vehicle", "Set on Fire", "Ragdoll", "Glitch Physics", "Black Screen", "Blame", "Remove Weapons", "Network Bail", "Force to Island", "Force to Apartment"
	}; inline std::size_t reaction_action_id2 = 0;

	const char* reaction_action3[] = {
		"Explode", "Crash", "Kick", "Cage", "Kick From Vehicle", "Set on Fire", "Ragdoll", "Glitch Physics", "Black Screen", "Blame", "Remove Weapons", "Network Bail", "Force to Island", "Force to Apartment"
	}; inline std::size_t reaction_action_id3 = 0;


	const char* reaction_action4[] = {
		"Explode", "Crash", "Kick", "Cage", "Kick From Vehicle", "Set on Fire", "Ragdoll", "Glitch Physics", "Black Screen", "Blame", "Remove Weapons", "Network Bail", "Force to Island", "Force to Apartment"
	}; inline std::size_t reaction_action_id4 = 0;

	const char* reaction_action5[] = {
		"Explode", "Crash", "Kick", "Cage", "Kick From Vehicle", "Set on Fire", "Ragdoll", "Glitch Physics", "Black Screen", "Blame", "Remove Weapons", "Network Bail", "Force to Island", "Force to Apartment"
	}; inline std::size_t reaction_action_id5 = 0;

	const char* reaction_action6[] = {
		"Explode", "Crash", "Kick", "Cage", "Kick From Vehicle", "Set on Fire", "Ragdoll", "Glitch Physics", "Black Screen", "Blame", "Remove Weapons", "Network Bail", "Force to Island", "Force to Apartment"
	}; inline std::size_t reaction_action_id6 = 0;

	const char* reaction_action7[] = {
		"Explode", "Crash", "Kick", "Cage", "Kick From Vehicle", "Set on Fire", "Ragdoll", "Glitch Physics", "Black Screen", "Blame", "Remove Weapons", "Network Bail", "Force to Island", "Force to Apartment"
	}; inline std::size_t reaction_action_id7 = 0;

	const char* reaction_action8[] = {
		"Explode", "Crash", "Kick", "Cage", "Kick From Vehicle", "Set on Fire", "Ragdoll", "Glitch Physics", "Black Screen", "Blame", "Remove Weapons", "Network Bail", "Force to Island", "Force to Apartment"
	}; inline std::size_t reaction_action_id8 = 0;

	const char* reaction_action9[] = {
		"Explode", "Crash", "Kick", "Cage", "Kick From Vehicle", "Set on Fire", "Ragdoll", "Glitch Physics", "Black Screen", "Blame", "Remove Weapons", "Network Bail", "Force to Island", "Force to Apartment"
	}; inline std::size_t reaction_action_id9 = 0;

	const char* reaction_action10[] = {
		"Explode", "Crash", "Kick", "Cage", "Kick From Vehicle", "Set on Fire", "Ragdoll", "Glitch Physics", "Black Screen", "Blame", "Remove Weapons", "Network Bail", "Force to Island", "Force to Apartment"
	}; inline std::size_t reaction_action_id10 = 0;

	const char* reaction_action11[] = {
		"Explode", "Crash", "Kick", "Cage", "Kick From Vehicle", "Set on Fire", "Ragdoll", "Glitch Physics", "Black Screen", "Blame", "Remove Weapons", "Network Bail", "Force to Island", "Force to Apartment"
	}; inline std::size_t reaction_action_id11 = 0;

	const char* reaction_action12[] = {
		"Explode", "Crash", "Kick", "Cage", "Kick From Vehicle", "Set on Fire", "Ragdoll", "Glitch Physics", "Black Screen", "Blame", "Remove Weapons", "Network Bail", "Force to Island", "Force to Apartment"
	}; inline std::size_t reaction_action_id12 = 0;

	const char* reaction_action13[] = {
		"Explode", "Crash", "Kick", "Cage", "Kick From Vehicle", "Set on Fire", "Ragdoll", "Glitch Physics", "Black Screen", "Blame", "Remove Weapons", "Network Bail", "Force to Island", "Force to Apartment"
	}; inline std::size_t reaction_action_id13 = 0;

	const char* reaction_action14[] = {
		"Explode", "Crash", "Kick", "Cage", "Kick From Vehicle", "Set on Fire", "Ragdoll", "Glitch Physics", "Black Screen", "Blame", "Remove Weapons", "Network Bail", "Force to Island", "Force to Apartment"
	}; inline std::size_t reaction_action_id14 = 0;

	const char* reaction_action15[] = {
		"Explode", "Crash", "Kick", "Cage", "Kick From Vehicle", "Set on Fire", "Ragdoll", "Glitch Physics", "Black Screen", "Blame", "Remove Weapons", "Network Bail", "Force to Island", "Force to Apartment"
	}; inline std::size_t reaction_action_id15 = 0;

	const char* reaction_action16[] = {
		"Explode", "Crash", "Kick", "Cage", "Kick From Vehicle", "Set on Fire", "Ragdoll", "Glitch Physics", "Black Screen", "Blame", "Remove Weapons", "Network Bail", "Force to Island", "Force to Apartment"
	}; inline std::size_t reaction_action_id16 = 0;

	const char* reaction_action17[] = {
		"Explode", "Crash", "Kick", "Cage", "Kick From Vehicle", "Set on Fire", "Ragdoll", "Glitch Physics", "Black Screen", "Blame", "Remove Weapons", "Network Bail", "Force to Island", "Force to Apartment"
	}; inline std::size_t reaction_action_id17 = 0;

}

namespace menu {

	void protections_menu::render() {
		renderer::addSubmenu("Protections", "Protections", [](core* core) {
			core->addOption(submenuOption("Network Events")
				.setTarget("Protections Network Events"));

			core->addOption(submenuOption("Script Events")
				.setTarget("Protections Script Events"));

			core->addOption(submenuOption("Presence Events")
				.setTarget("Protections Presence Events"));

			core->addOption(submenuOption("Anti Detection")
				.setTarget("Protections Anti Detection"));

			core->addOption(submenuOption("Join Blocking")
				.setTarget("Protections Join Blocking"));

			core->addOption(submenuOption("Reports")
				.setTarget("Protections Reports"));

			core->addOption(submenuOption("Reactions")
				.setTarget("Protections Reactions"));

			core->addOption(submenuOption("Entity")
				.setTarget("Protections Entity"));

			core->addOption(submenuOption("Syncs")
				.setTarget("Protections Syncs"));

			core->addOption(submenuOption("Miscellaneous")
				.setTarget("Protections Misc"));

			core->addOption(toggleOption("Fake Lag")
				.addToggle(&m_vars.m_fake_lag));

			core->addOption(toggleOption("Block all Script Events")
				.addToggle(&m_vars.m_block_all_script_events));

			core->addOption(toggleOption("Force Entities Visible")
				.addToggle(&m_vars.m_force_entities_visible));

			core->addOption(buttonOption("Enable All")
				.addClick([] { enable_all(); }));

			core->addOption(buttonOption("Disable All")
				.addClick([] { disable_all(); }));
		});	

		renderer::addSubmenu("Reactions", "Protections Reactions", [](core* core) {

			core->addOption(scrollOption<const char*, std::size_t>("Death")
				.addScroll(&reaction_action).setPosition(&reaction_action_id));
			
			core->addOption(scrollOption<const char*, std::size_t>("Aim")
				.addScroll(&reaction_action1).setPosition(&reaction_action_id1));

			core->addOption(scrollOption<const char*, std::size_t>("Report")
				.addScroll(&reaction_action2).setPosition(&reaction_action_id2));

			core->addOption(scrollOption<const char*, std::size_t>("Explode Loop")
				.addScroll(&reaction_action3).setPosition(&reaction_action_id3));

			core->addOption(scrollOption<const char*, std::size_t>("Fire Loop")
				.addScroll(&reaction_action4).setPosition(&reaction_action_id4));

			core->addOption(scrollOption<const char*, std::size_t>("Attachments")
				.addScroll(&reaction_action5).setPosition(&reaction_action_id5));

			core->addOption(scrollOption<const char*, std::size_t>("RAC")
				.addScroll(&reaction_action6).setPosition(&reaction_action_id6));

			core->addOption(scrollOption<const char*, std::size_t>("Arxan")
				.addScroll(&reaction_action7).setPosition(&reaction_action_id7));

			core->addOption(scrollOption<const char*, std::size_t>("Crash Attempt")
				.addScroll(&reaction_action8).setPosition(&reaction_action_id8));

			core->addOption(scrollOption<const char*, std::size_t>("Spectating You")
				.addScroll(&reaction_action9).setPosition(&reaction_action_id9));

			core->addOption(scrollOption<const char*, std::size_t>("Money Drop")
				.addScroll(&reaction_action10).setPosition(&reaction_action_id10));

			core->addOption(scrollOption<const char*, std::size_t>("Script Event Kick")
				.addScroll(&reaction_action11).setPosition(&reaction_action_id11));

			core->addOption(scrollOption<const char*, std::size_t>("Script Migration")
				.addScroll(&reaction_action12).setPosition(&reaction_action_id12));

			core->addOption(scrollOption<const char*, std::size_t>("Super Jump")
				.addScroll(&reaction_action13).setPosition(&reaction_action_id13));

			core->addOption(scrollOption<const char*, std::size_t>("Join Timeout")
				.addScroll(&reaction_action14).setPosition(&reaction_action_id14));

			core->addOption(scrollOption<const char*, std::size_t>("Invalid Model")
				.addScroll(&reaction_action15).setPosition(&reaction_action_id15));

			core->addOption(scrollOption<const char*, std::size_t>("Info Change")
				.addScroll(&reaction_action16).setPosition(&reaction_action_id16));
		});
	}

	void protections_menu::update() {
		render();
		getProtectionsNetworkEventsMenu()->update();
		getProtectionsScriptEventsMenu()->update();
		getProtectionsReportsMenu()->update();
		getProtectionsDetectionMenu()->update();
		getProtectionsMiscMenu()->update();
		getProtectionsPresenceMenu()->update();
		getProtectionsEntityMenu()->update();
		getProtectionsSyncsMenu()->update();
		getProtectionsJoinBlockingMenu()->update();
	}
}