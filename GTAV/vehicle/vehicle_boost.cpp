#include "pch.h"
#include "vehicle_boost.h"
#include "menu/util/globals.h"
#include "gui/options/option.h"
#include "gui/util/panels.h"
#include "rage/classes/CPed.h"
#include "rage/classes/CPlayerInfo.h"
#include "menu/util/control.h"
#include "menu/util/raycast.h"
#include "movement/vehicle_acrobatics.h"
#include "movement/vehicle_parachute.h"
#include "../vehicle.h"

using namespace base::gui;
using namespace menu::vehicle::boost::vars;

namespace menu::vehicle::boost::vars {
	variables m_vars;

	void boost(Vehicle ve, bool Forwards, bool disable_fx) {
		vehicle::vars::run_task(ve, [=](Vehicle veh) {
			if (m_vars.m_boost_fx && !disable_fx) {
				AUDIO::SET_VEHICLE_BOOST_ACTIVE(veh, true);
				GRAPHICS::ANIMPOSTFX_PLAY("RaceTurbo", -1, false);
			}

			if (m_vars.m_boost_sound && !disable_fx) {
				AUDIO::REQUEST_SCRIPT_AUDIO_BANK("DLC_IMPORTEXPORT/STEAL_STUNT", false, -1);
				AUDIO::PLAY_SOUND_FROM_ENTITY(-1, "Speed_Boost", veh, "DLC_IE_Stunt_Man_Sounds", false, 0);
			}

			VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, Forwards ? m_vars.m_boost_forwards + ENTITY::GET_ENTITY_SPEED(veh) : -m_vars.m_boost_backwards);

			if (m_vars.m_boost_fx && !disable_fx) {
				GRAPHICS::ANIMPOSTFX_STOP("RaceTurbo");
				AUDIO::SET_VEHICLE_BOOST_ACTIVE(veh, false);
			}
		});
	}
}



namespace menu {

	void vehicle_boost_menu::render() {
		renderer::addSubmenu("Vehicle Boost", "Vehicle Boost", [](core* core) {
			const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			core->addOption(toggleOption("Toggle Horn")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_toggle_horn));

			core->addOption(toggleOption("Toggle FX")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_boost_fx));

			core->addOption(toggleOption("Toggle Sound")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_boost_sound));

			core->addOption(toggleOption("Unlimited Special Ability")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_unlimited_special_ability));

			core->addOption(numberOption<int>("Boost Forwards")
				.addNumber(&m_vars.m_boost_forwards).addMin(0).addMax(1000)
				.addClick([=] { boost(vehicle, false, !m_vars.m_boost_fx); }));
			
			core->addOption(numberOption<int>("Boost Backwards")
				.addNumber(&m_vars.m_boost_backwards).addMin(0).addMax(1000)
				.addClick([=] { boost(vehicle, false, !m_vars.m_boost_fx); }));
		});
	}

	void vehicle_boost_menu::update() {
		render();
		const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) {
			if (m_vars.m_unlimited_special_ability) {
				if (VEHICLE::GET_HAS_ROCKET_BOOST(vehicle)) {
					static std::pair<uint32_t, bool> yes = { 0, false };

					if (VEHICLE::IS_ROCKET_BOOST_ACTIVE(vehicle)) {
						if (!yes.second) {
							yes.second = true;
							yes.first = GetTickCount() + 3500;
						}

						VEHICLE::SET_SCRIPT_ROCKET_BOOST_RECHARGE_TIME(vehicle, 0.0f);
						VEHICLE::SET_ROCKET_BOOST_FILL(vehicle, 100.f);

						if (yes.second) {
							if (GetTickCount() > yes.first) {
								yes.second = false;
								VEHICLE::SET_ROCKET_BOOST_ACTIVE(vehicle, false);
							}
						}
					}
				}
			}

			static bool reset = false;
			if (m_vars.m_toggle_horn) {
				Vehicle veh = vehicle;
				if (AUDIO::IS_HORN_ACTIVE(veh)) {
					if (m_vars.m_boost_fx) {
						AUDIO::SET_VEHICLE_BOOST_ACTIVE(veh, true);
						GRAPHICS::ANIMPOSTFX_PLAY("RaceTurbo", -1, false);
					}

					VEHICLE::MODIFY_VEHICLE_TOP_SPEED(vehicle, 10.f);
					VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, 100);

					uint64_t address = rage::engine::get_entity_address(veh);
					if (address) {
						*(float*)(address + 0x1360) = 30.f;
					}

					if (m_vars.m_boost_fx) {
						GRAPHICS::ANIMPOSTFX_STOP("RaceTurbo");
						AUDIO::SET_VEHICLE_BOOST_ACTIVE(veh, false);
					}

					reset = true;
				}
				else {
					if (reset) {
						uint64_t address = rage::engine::get_entity_address(veh);
						if (address) {
							*(float*)(address + 0x1360) = 1.f;
						}

						reset = false;
					}
				}
			}
		}
	}
}