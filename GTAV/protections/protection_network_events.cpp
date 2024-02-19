#include "pch.h"
#include "protection_network_events.h"
using namespace base::gui;
using namespace menu::protections::network_events::vars;

namespace menu::protections::network_events::vars {
	variables m_vars;

	void enable_all() {
		m_vars.block_network_crashes_id = 2;
		m_vars.block_network_kicks_id = 2;
		m_vars.block_desync_id = 2;
		m_vars.block_explosion_id = 2;
		m_vars.block_ptfx_id = 2;
		m_vars.block_kick_vote_id = 2;
		m_vars.block_clear_tasks_id = 2;
		m_vars.block_ragdoll_id = 2;
		m_vars.block_request_control_id = 2;
		m_vars.block_remove_weapons_id = 2;
		m_vars.block_give_weapons_id = 2;
		m_vars.block_sound_spam_id = 2;
	}

	void disable_all() {
		m_vars.block_network_crashes_id = 0;
		m_vars.block_network_kicks_id = 0;
		m_vars.block_desync_id = 0;
		m_vars.block_explosion_id = 0;
		m_vars.block_ptfx_id = 0;
		m_vars.block_kick_vote_id = 0;
		m_vars.block_clear_tasks_id = 0;
		m_vars.block_ragdoll_id = 0;
		m_vars.block_request_control_id = 0;
		m_vars.block_remove_weapons_id = 0;
		m_vars.block_give_weapons_id = 0;
		m_vars.block_sound_spam_id = 0;
	}

}

namespace menu {

	void protections_network_events_menu::render() {
		renderer::addSubmenu("Network Events", "Protections Network Events", [](core* core) {
			core->addOption(buttonOption("Enable All")
				.addClick([] { enable_all(); }));

			core->addOption(buttonOption("Disable All")
				.addClick([] { disable_all(); }));

			core->addOption(breakOption("Events"));

			core->addOption(scrollOption<const char*, std::size_t>("Crashes")
				.addScroll(&m_vars.block_network_crashes)
				.setPosition(&m_vars.block_network_crashes_id));

			core->addOption(scrollOption<const char*, std::size_t>("Kicks")
				.addScroll(&m_vars.block_network_kicks)
				.setPosition(&m_vars.block_network_kicks_id));

			core->addOption(scrollOption<const char*, std::size_t>("Desync Kicks")
				.addScroll(&m_vars.block_desync)
				.setPosition(&m_vars.block_desync_id));

			core->addOption(scrollOption<const char*, std::size_t>("Explosions")
				.addScroll(&m_vars.block_explosion)
				.setPosition(&m_vars.block_explosion_id));

			core->addOption(scrollOption<const char*, std::size_t>("Ptfx")
				.addScroll(&m_vars.block_ptfx)
				.setPosition(&m_vars.block_ptfx_id));

			core->addOption(scrollOption<const char*, std::size_t>("Kick Votes")
				.addScroll(&m_vars.block_kick_vote)
				.setPosition(&m_vars.block_kick_vote_id));

			core->addOption(scrollOption<const char*, std::size_t>("Clear Tasks")
				.addScroll(&m_vars.block_clear_tasks)
				.setPosition(&m_vars.block_clear_tasks_id));

			core->addOption(scrollOption<const char*, std::size_t>("Ragdoll")
				.addScroll(&m_vars.block_ragdoll)
				.setPosition(&m_vars.block_ragdoll_id));

			core->addOption(scrollOption<const char*, std::size_t>("Request Control")
				.addScroll(&m_vars.block_request_control)
				.setPosition(&m_vars.block_request_control_id));

			core->addOption(scrollOption<const char*, std::size_t>("Remove Weapons")
				.addScroll(&m_vars.block_remove_weapons)
				.setPosition(&m_vars.block_remove_weapons_id));

			core->addOption(scrollOption<const char*, std::size_t>("Give Weapons")
				.addScroll(&m_vars.block_give_weapons)
				.setPosition(&m_vars.block_give_weapons_id));

			core->addOption(scrollOption<const char*, std::size_t>("Sound Spam")
				.addScroll(&m_vars.block_sound_spam)
				.setPosition(&m_vars.block_sound_spam_id));
		});

	}

	void protections_network_events_menu::update() {
		render();

	}
}