#include "pch.h"
#include "vehicle_collision.h"
#include "menu/util/globals.h"
#include "gui/options/option.h"
#include "gui/util/panels.h"
#include "rage/classes/CPed.h"
#include "rage/classes/CPlayerInfo.h"
#include "menu/util/control.h"
#include "menu/util/raycast.h"
#include "menu/util/control.h"
using namespace base::gui;
using namespace menu::vehicle::collision::vars;

namespace menu::vehicle::collision::vars {
	variables m_vars;
}

namespace menu {

	void vehicle_collision_menu::render() {
		renderer::addSubmenu("Vehicle Collision", "Vehicle Collision", [](core* core) {
			const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			core->addOption(toggleOption("Disable Full Collision")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_disable_full_collision)
				.addClick([=] { if (!m_vars.m_disable_full_collision) if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) ENTITY::SET_ENTITY_COLLISION(vehicle, true, true);  }));

			core->addOption(toggleOption("Disable Vehicle Collision")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_disable_vehicle_collision));
		});
	}

	void vehicle_collision_menu::update() {
		render();

		const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) {
			if (m_vars.m_disable_full_collision) {
				ENTITY::SET_ENTITY_COLLISION(vehicle, !m_vars.m_disable_full_collision, true);
			}

			if (m_vars.m_disable_vehicle_collision) {
				std::vector<Entity> veh = menu::control::get_entities(true, false);
				for (auto i = 0; i < veh.size(); i++) {
					ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(i, vehicle, true);
				}
			}
		}
	}
}