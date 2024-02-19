#include "pch.h"
#include "vehicle_multipliers.h"
#include "menu/util/globals.h"
#include "gui/options/option.h"
#include "gui/util/panels.h"
#include "rage/classes/CPed.h"
#include "rage/classes/CPlayerInfo.h"
#include "menu/util/control.h"
#include "menu/util/raycast.h"

using namespace base::gui;
using namespace menu::vehicle::multipliers::vars;

namespace menu::vehicle::multipliers::vars {
	variables m_vars;

	

}



namespace menu {

	void vehicle_multipliers_menu::render() {
		renderer::addSubmenu("Vehicle Multipliers", "Vehicle Multipliers", [](core* core) {
			const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

			core->addOption(numberOption<float>("Power")
				.addNumber(&m_vars.m_power)
				.addMin(0).addMax(100).setPrecision(0).addStep(1)
				.addClick([=] { VEHICLE::MODIFY_VEHICLE_TOP_SPEED(vehicle, m_vars.m_power); }));

			core->addOption(numberOption<float>("Torque")
				.addNumber(&m_vars.m_torque)
				.addMin(0).addMax(100).setPrecision(0).addStep(1));

			core->addOption(numberOption<float>("Headlight")
				.addNumber(&m_vars.m_headlight)
				.addMin(0).addMax(100).setPrecision(0).addStep(1));
		});
	}

	void vehicle_multipliers_menu::update() {
		render();

		const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
	}
}