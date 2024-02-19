#include "pch.h"
#include "vehicle_parachute.h"
#include "menu/util/globals.h"
#include "gui/options/option.h"
#include "gui/util/panels.h"
#include "rage/classes/CPed.h"
#include "rage/classes/CPlayerInfo.h"
#include "menu/util/control.h"
#include "menu/util/raycast.h"
#include "../../vehicle.h"
#include "rage/classes/CVehicleModelInfo.h"
using namespace base::gui;
using namespace menu::vehicle::parachute::vars;

namespace menu::vehicle::parachute::vars {
	variables m_vars;

	void deploy() {
		Entity vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) {
			if (ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(vehicle) > 5.f) {
				if (VEHICLE::IS_THIS_MODEL_A_HELI(ENTITY::GET_ENTITY_MODEL(vehicle))) return;

				vehicle::vars::run_task(vehicle, [=](Vehicle veh) {
					uint64_t address = rage::engine::get_entity_address(veh);
					if (address) {
						uint64_t model_info = *(uint64_t*)(address + 0x20);
						if (model_info) {
							*(uint8_t*)(model_info + 0x58C) |= 1;
						}

						*(bool*)(address + 0x1A5D) = true;
						VEHICLE::VEHICLE_START_PARACHUTING(veh, true);
					}
					});
			}
		}
	}


	const char* type[] = {
		"Rocket Boost", "Parachute"
	}; inline std::size_t type_id = 0;
}



namespace menu {

	void vehicle_parachute_menu::render() {
		renderer::addSubmenu("Vehicle Abilities", "Vehicle Parachute", [](core* core) {
			const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			
			core->addOption(scrollOption<const char*, std::size_t>("Type")
				.addScroll(&type).setPosition(&type_id));

			core->addOption(toggleOption("Toggle")
				.addToggle(&m_vars.ability_toggle));
		});
	}

	void vehicle_parachute_menu::update() {
		render();

		uint16_t og_ability = 0;
		int byte0;
		int byte1;
		bool edited = false;

		if (m_vars.ability_toggle && (*patterns::ped_factory)->m_local_ped && (*patterns::ped_factory)->m_local_ped->m_vehicle && PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) {
			CVehicleModelInfo* modelinfo = (CVehicleModelInfo*)(*patterns::ped_factory)->m_local_ped->m_vehicle->m_model_info;

			if (!edited)
				og_ability = modelinfo->m_ability_flag;

			if (PED::IS_PED_DEAD_OR_DYING(PLAYER::PLAYER_PED_ID(), 0) || PAD::IS_CONTROL_JUST_PRESSED(0, (int)eControllerInputs::INPUT_VEH_EXIT)) {
				m_vars.boost = false;
				m_vars.parachute = false;
				modelinfo->m_ability_flag = og_ability;
				edited = false;
			}

			if (!m_vars.boost && m_vars.parachute) {
				modelinfo->m_ability_flag = og_ability;
				edited = false;
			}

			if (m_vars.boost) { edited = true; byte0 = 96; }
			if (m_vars.parachute) { edited = true; byte1 = 1; }

			uint16_t value = modelinfo->m_ability_flag;
			uint8_t* bytes = reinterpret_cast<uint8_t*>(&value);
			bytes[0] = byte0;
			bytes[1] = byte1;
			modelinfo->m_ability_flag = value;

			switch (type_id) {
			case 0:
				m_vars.boost = true;
				break;
			case 1:
				m_vars.parachute = true;
				break;
			}
		}

		if (m_vars.m_auto_deploy) {
			deploy();
		}
	}
}