#include "pch.h"
#include "protections_entity.h"
using namespace base::gui;
using namespace menu::protections::entity::vars;

namespace menu::protections::entity::vars {
	variables m_vars;


}

namespace menu {

	void protections_entity_menu::render() {
		renderer::addSubmenu("Entity", "Protections Entity", [](core* core) {

			core->addOption(scrollOption<const char*, std::size_t>("Type")
				.addScroll(&m_vars.entity_type)
				.setPosition(&m_vars.entity_type_pos));

			switch (m_vars.entity_type_pos) {
			case 0:
				core->addOption(toggleOption("Automobile").addToggle(&m_vars.m_sync_car));
				core->addOption(toggleOption("Bike").addToggle(&m_vars.m_sync_bike));
				core->addOption(toggleOption("Boat").addToggle(&m_vars.m_sync_boat));
				core->addOption(toggleOption("Door").addToggle(&m_vars.m_sync_door));
				core->addOption(toggleOption("Heli").addToggle(&m_vars.m_sync_heli));
				core->addOption(toggleOption("Object").addToggle(&m_vars.m_sync_object));
				core->addOption(toggleOption("Ped").addToggle(&m_vars.m_sync_ped));
				core->addOption(toggleOption("Pickup").addToggle(&m_vars.m_sync_pickup));
				core->addOption(toggleOption("Pickup Placement").addToggle(&m_vars.m_sync_pickup_placement));
				core->addOption(toggleOption("Plane").addToggle(&m_vars.m_sync_plane));
				core->addOption(toggleOption("Submarine").addToggle(&m_vars.m_sync_sub));
				core->addOption(toggleOption("Player").addToggle(&m_vars.m_sync_player));
				core->addOption(toggleOption("Trailer").addToggle(&m_vars.m_sync_trailer));
				core->addOption(toggleOption("Train").addToggle(&m_vars.m_sync_train));
				break;
			case 1:
				core->addOption(toggleOption("Automobile").addToggle(&m_vars.m_car));
				core->addOption(toggleOption("Bike").addToggle(&m_vars.m_bike));
				core->addOption(toggleOption("Boat").addToggle(&m_vars.m_boat));
				core->addOption(toggleOption("Door").addToggle(&m_vars.m_door));
				core->addOption(toggleOption("Heli").addToggle(&m_vars.m_heli));
				core->addOption(toggleOption("Object").addToggle(&m_vars.m_object));
				core->addOption(toggleOption("Ped").addToggle(&m_vars.m_ped));
				core->addOption(toggleOption("Pickup").addToggle(&m_vars.m_pickup));
				core->addOption(toggleOption("Pickup Placement").addToggle(&m_vars.m_pickup_placement));
				core->addOption(toggleOption("Plane").addToggle(&m_vars.m_plane));
				core->addOption(toggleOption("Submarine").addToggle(&m_vars.m_sub));
				core->addOption(toggleOption("Player").addToggle(&m_vars.m_player));
				core->addOption(toggleOption("Trailer").addToggle(&m_vars.m_trailer));
				core->addOption(toggleOption("Train").addToggle(&m_vars.m_train));
				break;
			}

		});

	}

	void protections_entity_menu::update() {
		render();

	}
}