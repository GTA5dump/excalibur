#include "pch.h"
#include "protection_syncs.h"
using namespace base::gui;
using namespace menu::protections::syncs::vars;

namespace menu::protections::syncs::vars {
	variables m_vars;


}

namespace menu {

	void protections_syncs_menu::render() {
		renderer::addSubmenu("Syncs", "Protections Syncs", [](core* core) {
			core->addOption(toggleOption("Block Incoming Syncs")
				.addToggle(&m_vars.block_incoming_syncs));

			core->addOption(toggleOption("Block Outgoing Syncs")
				.addToggle(&m_vars.block_outgoing_syncs));
		
		});

	}

	void protections_syncs_menu::update() {
		render();

	}
}