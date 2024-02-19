#include "pch.h"
#include "protections_misc.h"
using namespace base::gui;
using namespace menu::protections::misc::vars;

namespace menu::protections::misc::vars {
	variables m_vars;


}

namespace menu {

	void protections_misc_menu::render() {
		renderer::addSubmenu("Miscellaneous", "Protections Misc", [](core* core) {
			core->addOption(scrollOption<const char*, std::size_t>("Script Host Kicks")
				.addScroll(&m_vars.script_host_kicks)
				.setPosition(&m_vars.script_host_kicks_id));

			core->addOption(scrollOption<const char*, std::size_t>("Script Host Migration")
				.addScroll(&m_vars.script_host_migration)
				.setPosition(&m_vars.script_host_migration_id));

			core->addOption(scrollOption<const char*, std::size_t>("Pickup Processing")
				.addScroll(&m_vars.pickup_processing)
				.setPosition(&m_vars.pickup_processing_id));

			core->addOption(scrollOption<const char*, std::size_t>("Cloning")
				.addScroll(&m_vars.cloning)
				.setPosition(&m_vars.cloning_id));

			core->addOption(scrollOption<const char*, std::size_t>("Cages")
				.addScroll(&m_vars.cages)
				.setPosition(&m_vars.cages_id));

			core->addOption(scrollOption<const char*, std::size_t>("Attachments")
				.addScroll(&m_vars.attachments)
				.setPosition(&m_vars.attachments_id));

			core->addOption(scrollOption<const char*, std::size_t>("Join Timeout")
				.addScroll(&m_vars.join_timeout)
				.setPosition(&m_vars.join_timeout_id));

			core->addOption(scrollOption<const char*, std::size_t>("Ghost")
				.addScroll(&m_vars.ghost)
				.setPosition(&m_vars.ghost_id));

			core->addOption(scrollOption<const char*, std::size_t>("Spoofed Text Messages")
				.addScroll(&m_vars.spoofed_text_messages)
				.setPosition(&m_vars.spoofed_text_messages_id));

			core->addOption(scrollOption<const char*, std::size_t>("Spoofed Chat Messages")
				.addScroll(&m_vars.spoofed_chat_messages)
				.setPosition(&m_vars.spoofed_chat_messages_id));

			core->addOption(toggleOption("Disable Bullets")
				.addToggle(&m_vars.m_disable_bullets));

			core->addOption(toggleOption("Disable Projectiles")
				.addToggle(&m_vars.m_disable_projectiles));
		});

	}

	void protections_misc_menu::update() {
		render();
	}
}