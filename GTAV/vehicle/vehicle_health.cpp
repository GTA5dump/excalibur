#include "pch.h"
#include "vehicle_health.h"
#include "menu/util/globals.h"
#include "gui/options/option.h"
#include "gui/util/panels.h"
#include "rage/classes/CPed.h"
#include "rage/classes/CPlayerInfo.h"
#include "menu/util/control.h"
#include "menu/util/raycast.h"
#include "../vehicle.h"


using namespace base::gui;
using namespace menu::vehicle::health::vars;

namespace menu::vehicle::health::vars {
	variables m_vars;



}



namespace menu {

	void vehicle_health_menu::render() {
		renderer::addSubmenu("Vehicle Health", "Vehicle Health", [](core* core) {
			const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

			core->addOption(buttonOption("Repair Vehicle")
				.addClick([=] { vehicle::vars::run_task(vehicle, [=](Vehicle veh) { VEHICLE::SET_VEHICLE_FIXED(veh); }); }));

			core->addOption(buttonOption("Wash Vehicle")
				.addClick([=] { vehicle::vars::run_task(vehicle, [=](Vehicle veh) { VEHICLE::SET_VEHICLE_DIRT_LEVEL(vehicle, 0.f); }); }));

			core->addOption(buttonOption("Dirty Vehicle")		
				.addClick([=] { vehicle::vars::run_task(vehicle, [=](Vehicle veh) { VEHICLE::SET_VEHICLE_DIRT_LEVEL(vehicle, 15.f); }); }));

			core->addOption(toggleOption("Auto Repair")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_auto_repair));

			core->addOption(toggleOption("Auto Wash")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_auto_wash));
		});
	}

	void vehicle_health_menu::update() {
		render();
		const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) {
			if (m_vars.m_auto_repair) {
				if (VEHICLE::GET_DOES_VEHICLE_HAVE_DAMAGE_DECALS(vehicle)) {
					vehicle::vars::run_task(vehicle, [](Vehicle veh) {
						VEHICLE::SET_VEHICLE_FIXED(veh);
					});
				}
			}

			if (m_vars.m_auto_wash) {
				VEHICLE::SET_VEHICLE_DIRT_LEVEL(vehicle, 0.f);
			}
		}
	}
}