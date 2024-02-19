#include "pch.h"
#include "protections_join_blocking.h"
using namespace base::gui;
using namespace menu::protections::join_blocking::vars;

namespace menu::protections::join_blocking::vars {
	variables m_vars;


}

namespace menu {

	void protections_join_blocking_menu::render() {
		renderer::addSubmenu("Join Blocking", "Protections Join Blocking", [](core* core) {
			core->addOption(toggleOption("Block Resolves")
				.addToggle(&m_vars.m_block));

			core->addOption(toggleOption("Spoof Resolves")
				.addToggle(&m_vars.m_spoof));

			});

	}

	void protections_join_blocking_menu::update() {
		render();

	}
}