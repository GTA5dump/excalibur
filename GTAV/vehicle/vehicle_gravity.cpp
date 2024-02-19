#include "pch.h"
#include "vehicle_gravity.h"
#include "menu/util/globals.h"
#include "gui/options/option.h"
#include "gui/util/panels.h"
#include "rage/classes/CPed.h"
#include "rage/classes/CPlayerInfo.h"
#include "menu/util/control.h"
#include "menu/util/raycast.h"
#include "../vehicle.h"
using namespace base::gui;
using namespace menu::vehicle::gravity::vars;

namespace menu::vehicle::gravity::vars {
	variables m_vars;

	struct GravityData {
		const char* name;
		float value;
	};

	std::vector<GravityData> gravity = {
		{ "Earth", 9.807f },
		{ "Moon", 1.62f },
		{ "Mercury", 3.7f },
		{ "Jupiter", 24.79f },
		{ "Mars", 3.711f },
		{ "Saturn", 10.44f },
		{ "Uranus/Venus", 8.87f },
		{ "Neptune", 11.15f },
		{ "Sun", 274.0f }
	};

	const char* gravityNames[] = {
	"Earth",
	"Moon",
	"Mercury",
	"Jupiter",
	"Mars",
	"Saturn",
	"Uranus/Venus",
	"Neptune",
	"Sun"
	};

	void set_gravity() {
		const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) {
			if (rage::engine::get_entity_address(vehicle) == 0) return;
			vehicle::vars::run_task(vehicle, [](Vehicle veh) {
				rage::engine::set_vehicle_gravity(rage::engine::get_entity_address(veh), gravity[m_vars.m_gravity].value);
			});
		}
	}
}

namespace menu {

	void vehicle_gravity_menu::render() {
		renderer::addSubmenu("Vehicle Gravity", "Vehicle Gravity", [](core* core) {
			const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

			core->addOption(scrollOption<const char*, int>("Gravity")
				.addScroll(&gravityNames).setPosition(&m_vars.m_gravity)
				.addClick([=] { if (Util::is_key_pressed(VK_RETURN)) { set_gravity(); } }));

			core->addOption(toggleOption("Stick to Ground")	
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_stick_to_ground));

			core->addOption(toggleOption("Auto Flip")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_auto_flip));

			core->addOption(buttonOption("Place on Ground")
				.addTranslate().addHotkey()
				.addClick([=] { if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) vehicle::vars::run_task(vehicle, [](Vehicle veh) { VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh, 0); }); }));
		});
	}

	void vehicle_gravity_menu::update() {
		render();

		const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) {
			if (m_vars.m_stick_to_ground) {
				VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(vehicle, 0);
			}

			if (m_vars.m_auto_flip) {
				if (!ENTITY::IS_ENTITY_UPRIGHT(vehicle, 120.f)) {
					Vector3 rotation = ENTITY::GET_ENTITY_ROTATION(vehicle, 0);
					ENTITY::SET_ENTITY_ROTATION(vehicle, 0.f, rotation.y, rotation.z, 0, true);
				}
			}
		}
	}
}