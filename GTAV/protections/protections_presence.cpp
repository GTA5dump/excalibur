#include "pch.h"
#include "protections_presence.h"
using namespace base::gui;
using namespace menu::protections::presence::vars;

namespace menu::protections::presence::vars {
	variables m_vars;


}

namespace menu {

	void protections_presence_menu::render() {
		renderer::addSubmenu("Presence Events", "Protections Presence Events", [](core* core) {
			core->addOption(scrollOption<const char*, std::size_t>("Text Message")
				.addScroll(&m_vars.text_message)
				.setPosition(&m_vars.text_message_id));

			core->addOption(scrollOption<const char*, std::size_t>("Crew Message")
				.addScroll(&m_vars.crew_message)
				.setPosition(&m_vars.crew_message_id));

			core->addOption(scrollOption<const char*, std::size_t>("Game Invite")
				.addScroll(&m_vars.game_invite)
				.setPosition(&m_vars.game_invite_id));

			core->addOption(scrollOption<const char*, std::size_t>("Bounty")
				.addScroll(&m_vars.bounty)
				.setPosition(&m_vars.bounty_id));

			core->addOption(scrollOption<const char*, std::size_t>("Voice Session Invite")
				.addScroll(&m_vars.voice_invite)
				.setPosition(&m_vars.voice_invite_id));

			core->addOption(scrollOption<const char*, std::size_t>("Game Server Rewards")
				.addScroll(&m_vars.game_award)
				.setPosition(&m_vars.game_award_id));

			core->addOption(scrollOption<const char*, std::size_t>("Admin Invite")
				.addScroll(&m_vars.admin_invite)
				.setPosition(&m_vars.admin_invite_id));

			core->addOption(scrollOption<const char*, std::size_t>("Admin Message")
				.addScroll(&m_vars.rockstar_message)
				.setPosition(&m_vars.rockstar_message_id));

			core->addOption(scrollOption<const char*, std::size_t>("Stat Update")
				.addScroll(&m_vars.stat_update)
				.setPosition(&m_vars.stat_update_id));
		});

	}

	void protections_presence_menu::update() {
		render();

	}
}