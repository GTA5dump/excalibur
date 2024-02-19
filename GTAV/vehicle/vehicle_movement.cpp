#include "pch.h"
#include "vehicle_movement.h"
#include "menu/util/globals.h"
#include "gui/options/option.h"
#include "gui/util/panels.h"
#include "rage/classes/CPed.h"
#include "rage/classes/CPlayerInfo.h"
#include "menu/util/control.h"
#include "menu/util/raycast.h"
#include "movement/vehicle_acrobatics.h"
#include "movement/vehicle_parachute.h"

using namespace base::gui;
using namespace menu::vehicle::movement::vars;

namespace menu::vehicle::movement::vars {
	variables m_vars;

	void bypass_max_speed() {
		ENTITY::SET_ENTITY_MAX_SPEED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 9999999.f);
	}

}



namespace menu {

	void vehicle_movement_menu::render() {
		renderer::addSubmenu("Vehicle Movement", "Vehicle Movement", [](core* core) {
			const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

			core->addOption(submenuOption("Acrobatics")
				.setTarget("Vehicle Acrobatics"));

			core->addOption(submenuOption("Abilities")
				.setTarget("Vehicle Parachute"));

			core->addOption(toggleOption("Bypass Max Speed")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_disable_max_speed));

			core->addOption(toggleNumberOption<float>("Flying Vehicle")
				.addToggle(&m_vars.m_flying_vehicle)
				.addNumber(&m_vars.m_flying_vehicle_speed).addStep(0.1f).setPrecision(1).addMin(0.5f).addMax(1000.f)
				.addClick([=] { if (!m_vars.m_flying_vehicle) if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) ENTITY::SET_ENTITY_COLLISION(vehicle, true, true); }));

			if (m_vars.m_flying_vehicle) {

				core->addOption(toggleOption("Flying Vehicle Pause")
					.addTranslate().addHotkey()
					.addToggle(&m_vars.m_flying_vehicle_pause));
			}
		});
	}

	void vehicle_movement_menu::update() {
		render();
		getVehicleAcrobaticsMenu()->update();
		getVehicleParachuteMenu()->update();

		const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) {
			if (m_vars.m_flying_vehicle) {
				if (VEHICLE::GET_PED_IN_VEHICLE_SEAT(vehicle, -1, 0) == PLAYER::PLAYER_PED_ID()) {
					auto apply_force_relative = [](std::uint32_t handle, Vector3 direction) {
						ENTITY::APPLY_FORCE_TO_ENTITY(handle, true, direction, { 0.f, 0.f, 0.f }, true, true, true, true, false, true);
					};

					int left_right = PAD::GET_CONTROL_VALUE(2, 188);
					int up_down = PAD::GET_CONTROL_VALUE(2, 189);

					auto w_down = GetKeyState('W') & 0x8000 || up_down == 0;
					auto s_down = GetKeyState('S') & 0x8000 || up_down == 254;
					auto d_down = GetKeyState('D') & 0x8000 || left_right == 254;
					auto a_down = GetKeyState('A') & 0x8000 || left_right == 0;

					auto veh = vehicle;

					if (w_down || s_down || d_down || a_down) {
						if (w_down)
							apply_force_relative(veh, Vector3(0, 1.0f * m_vars.m_flying_vehicle_speed, 0));

						if (s_down)
							apply_force_relative(veh, Vector3(0, -1.0f * m_vars.m_flying_vehicle_speed, 0));

						if (d_down)
							apply_force_relative(veh, Vector3(1.0f * m_vars.m_flying_vehicle_speed, 0, 0));

						if (a_down)
							apply_force_relative(veh, Vector3(-1.0f * m_vars.m_flying_vehicle_speed, 0, 0));
					}
					else {
						if (m_vars.m_flying_vehicle_pause)
							ENTITY::SET_ENTITY_VELOCITY(veh, { 0, 0, 0 });
					}

					auto cam_rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
					ENTITY::SET_ENTITY_ROTATION(veh, cam_rot.x, cam_rot.y, cam_rot.z, 0, true);
				}
			}
			if (m_vars.m_disable_max_speed) {
				bypass_max_speed();
			}
		}
	}
}