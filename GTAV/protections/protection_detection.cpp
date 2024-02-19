#include "pch.h"
#include "protection_detection.h"
using namespace base::gui;
using namespace menu::protections::detection::vars;

namespace menu::protections::detection::vars {
	variables m_vars;


}

namespace menu {

	void protections_detection_menu::render() {
		renderer::addSubmenu("Anti Detection", "Protections Anti Detection", [](core* core) {
			core->addOption(toggleOption("Godmode")
				.addToggle(&m_vars.m_godmode));

			core->addOption(toggleOption("Super Jump")
				.addToggle(&m_vars.m_superjump));

			core->addOption(toggleOption("Frame Flags")
				.addToggle(&m_vars.m_frame_flags));

			core->addOption(toggleOption("Health")
				.addToggle(&m_vars.m_health));

			core->addOption(toggleOption("Armor")
				.addToggle(&m_vars.m_armor));

			core->addOption(toggleOption("Spectate")
				.addToggle(&m_vars.m_spectate));		
		});

	}

	void protections_detection_menu::update() {
		render();

	}
}