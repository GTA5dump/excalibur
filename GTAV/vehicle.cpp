#include "pch.h"
#include "vehicle.h"
#include "menu/util/control.h"
#include "vehicle/vehicle_mods.h"

using namespace base::gui;
using namespace menu::vehicle::vars;

namespace menu::vehicle::vars {
	variables m_vars;

	void run_task(Vehicle veh, std::function<void(Vehicle)> callback) {
		if (veh) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) {
				if (PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false) == veh) {
					if (VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1, 0) == PLAYER::PLAYER_PED_ID() && !NETWORK::NETWORK_IS_IN_SESSION()) {
						callback(veh);
						return;
					}
					else {
						if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(veh)) {
							callback(veh);
							return;
						}
						menu::control::request_control(veh);
						return;
					}
				}
			}
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(driver)) {
				if (PED::IS_PED_A_PLAYER(driver)) {
					if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(veh)) {
						callback(veh);
						return;
					}
					menu::control::request_control(veh);
					return;
				}
			}
			callback(veh);
		}
	}

}

namespace menu {

	void vehicle_menu::render() {
		renderer::addSubmenu("Vehicle", "Vehicle", [](core* core) {
			core->addOption(submenuOption("Vehicle Mods")
				.setTarget("Vehicle Mods"));

			core->addOption(breakOption("Quick Access"));

			core->addOption(toggleOption("Godmode")
				.addHotkey().addTranslate()
				.addToggle(&m_vars.m_godmode)
				.addClick([] { if (!m_vars.m_godmode) ENTITY::SET_ENTITY_INVINCIBLE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), false); }));

			core->addOption(toggleOption("Invisibility")
				.addHotkey().addTranslate()
				.addToggle(&m_vars.m_invisibility)
				.addClick([] { if (!m_vars.m_invisibility) ENTITY::SET_ENTITY_VISIBLE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), true, true); }));

			core->addOption(toggleOption("Seatbelt")
				.addHotkey().addTranslate()
				.addToggle(&m_vars.m_seatbelt)
				.addClick([] {
					if (!m_vars.m_seatbelt) {
						PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), 0);
						PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 32, true);
					}
				}));

			core->addOption(buttonOption("Upgrade")
				.addClick([] { Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false); VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0); for (int i = 0; i < 50; i++) { VEHICLE::SET_VEHICLE_MOD(veh, i, VEHICLE::GET_NUM_VEHICLE_MODS(veh, i) - 1, false); }}));

			core->addOption(buttonOption("Downgrade")
				.addClick([] { Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);  for (int i = 0; i < 50; i++) { VEHICLE::REMOVE_VEHICLE_MOD(veh, VEHICLE::GET_NUM_VEHICLE_MODS(veh, i) - 1); }}));
		});
	}

	void vehicle_menu::update() {
		render();
		getVehicleModsMenu()->update();

		const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) {
			if (m_vars.m_godmode) {
				ENTITY::SET_ENTITY_INVINCIBLE(vehicle, true);
			}

			if (m_vars.m_invisibility) {
				ENTITY::SET_ENTITY_VISIBLE(vehicle, false, true);
			}

			if (m_vars.m_seatbelt) {
				PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), 1);
				PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 32, false);
			}

		}
	}
}