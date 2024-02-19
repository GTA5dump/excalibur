#include "pch.h"
#include "vehicle_mods.h"
#include "menu/util/globals.h"
#include "gui/options/option.h"
#include "gui/util/panels.h"
#include "rage/classes/CPed.h"
#include "rage/classes/CPlayerInfo.h"
#include "menu/util/control.h"
#include "menu/util/raycast.h"

#include "vehicle_health.h"
#include "vehicle_movement.h"
#include "vehicle_boost.h"
#include "vehicle_multipliers.h"
#include "vehicle_weapons.h"
#include "vehicle_particles.h"
#include "vehicle_collision.h"
#include "vehicle_gravity.h"
#include "vehicle_ramps.h"
#include "vehicle_tyre_tracks.h"
#include "vehicle_modifiers.h"

using namespace base::gui;
using namespace menu::vehicle::mods::vars;

namespace menu::vehicle::mods::vars {
	variables m_vars;
	int r = 255, g = 0, b = 0;
	void RGBFadee()
	{
		if (r > 0 && b == 0) {
			r--;
			g++;
		}
		if (g > 0 && r == 0) {
			g--;
			b++;
		}
		if (b > 0 && g == 0) {
			r++;
			b--;
		}
	}

	enum vehicle_mods {
		MOD_SPOILER,
		MOD_FRONTBUMPER,
		MOD_REARBUMPER,
		MOD_SIDESKIRT,
		MOD_EXHAUST,
		MOD_CHASSIS,
		MOD_GRILLE,
		MOD_HOOD,
		MOD_FENDER,
		MOD_RIGHTFENDER,
		MOD_ROOF,
		MOD_ENGINE,
		MOD_BRAKES,
		MOD_TRANSMISSION,
		MOD_HORN,
		MOD_SUSPENSION,
		MOD_ARMOR,
		MOD_UNK17 = 17,
		MOD_TURBO = 18,
		MOD_UNK19 = 19,
		MOD_TIRESMOKE = 20,
		MOD_UNK21 = 21,
		MOD_XENONLIGHTS = 22,
		MOD_FRONTWHEELS = 23,
		MOD_BACKWHEELS = 24, //Bikes only

		// Benny's
		MOD_PLATEHOLDER = 25,
		MOD_VANITY_PLATES = 26,
		MOD_TRIM = 27,
		MOD_ORNAMENTS = 28,
		MOD_DASHBOARD = 29,
		MOD_DIAL = 30,
		MOD_DOOR_SPEAKER = 31,
		MOD_SEATS = 32,
		MOD_STEERINGWHEEL = 33,
		MOD_SHIFTER_LEAVERS = 34,
		MOD_PLAQUES = 35,
		MOD_SPEAKERS = 36,
		MOD_TRUNK = 37,
		MOD_HYDRULICS = 38,
		MOD_ENGINE_BLOCK = 39,
		MOD_AIR_FILTER = 40,
		MOD_STRUTS = 41,
		MOD_ARCH_COVER = 42,
		MOD_AERIALS = 43,
		MOD_TRIM2 = 44,
		MOD_TANK = 45,
		MOD_WINDOWS = 46,
		MOD_UNK47 = 47,
		MOD_LIVERY = 48,
	};
}

namespace menu {

	void vehicle_mods_menu::render() {
		renderer::addSubmenu("Vehicle Mods", "Vehicle Mods", [](core* core) {
			core->addOption(submenuOption("Excalibur Customs")
				.setTarget("Excalibur Customs"));
			
			core->addOption(submenuOption("Health")
				.setTarget("Vehicle Health"));

			core->addOption(submenuOption("Movement")
				.setTarget("Vehicle Movement"));

			core->addOption(submenuOption("Boost")
				.setTarget("Vehicle Boost"));

			core->addOption(submenuOption("Multipliers")
				.setTarget("Vehicle Multipliers"));

			core->addOption(submenuOption("Modifiers")
				.setTarget("Vehicle Modifiers"));

			core->addOption(submenuOption("Weapons")
				.setTarget("Vehicle Weapons"));

			core->addOption(submenuOption("Particles")
				.setTarget("Vehicle Particles"));

			core->addOption(submenuOption("Collision")
				.setTarget("Vehicle Collision"));

			core->addOption(submenuOption("Gravity")
				.setTarget("Vehicle Gravity"));

			core->addOption(submenuOption("Ramps")
				.setTarget("Vehicle Ramps"));

			core->addOption(submenuOption("Doors")
				.setTarget("Vehicle Doors"));

			core->addOption(submenuOption("Proofs")
				.setTarget("Vehicle Proofs"));

			core->addOption(submenuOption("Tyre Tracks")
				.setTarget("Vehicle Tyre Tracks"));

			core->addOption(toggleOption("Rainbow Primary Paint")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_rainbow_prime));

			core->addOption(toggleOption("Rainbow Primary Paint")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_rainbow_second));

			core->addOption(toggleOption("Rainbow Tyre Smoke")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_rainbow_tyre));

			core->addOption(toggleOption("Instant Stop")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_instant_stop));

			core->addOption(toggleOption("Instant Enter")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_instant_enter));

			core->addOption(toggleOption("Toggle Flares")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_toggle_flares));

			core->addOption(toggleOption("Toggle Chaff")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_toggle_chaff));

			core->addOption(buttonOption("Kick Driver")
				.addClick([] {
					if (!VEHICLE::IS_VEHICLE_SEAT_FREE(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), -1, 0)) {
						TASK::CLEAR_PED_TASKS_IMMEDIATELY(VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0), -1, 0));
					}}));

			core->addOption(buttonOption("Delete")
				.addClick([] {
					if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) {
						Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
						ENTITY::DELETE_ENTITY(&veh);
					}
				}));
		});


		renderer::addSubmenu("Excalibur Customs", "Excalibur Customs", [](core* core) {
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());

			core->addOption(numberOption<std::int32_t>("Spoiler")
				.addNumber(&m_vars.Spoiler).addMin(0).addMax(VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SPOILER))
				.addClick([veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_SPOILER, m_vars.Spoiler, false); }));

			core->addOption(numberOption<std::int32_t>("Front Bumper")
				.addNumber(&m_vars.FBumper).addMin(0).addMax(VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_FRONTBUMPER))
				.addClick([veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_FRONTBUMPER, m_vars.FBumper, false); }));

			core->addOption(numberOption<std::int32_t>("Rear Bumper")
				.addNumber(&m_vars.RBumper).addMin(0).addMax(VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_REARBUMPER))
				.addClick([veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_REARBUMPER, m_vars.RBumper, false); }));

			core->addOption(numberOption<std::int32_t>("Skirt")
				.addNumber(&m_vars.SSkirt).addMin(0).addMax(VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SIDESKIRT))
				.addClick([veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_SIDESKIRT, m_vars.SSkirt, false); }));

			core->addOption(numberOption<std::int32_t>("Exhaust")
				.addNumber(&m_vars.Exhaust).addMin(0).addMax(VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_EXHAUST))
				.addClick([veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_EXHAUST, m_vars.Exhaust, false); }));

			core->addOption(numberOption<std::int32_t>("Grille")
				.addNumber(&m_vars.Grille).addMin(0).addMax(VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_GRILLE))
				.addClick([veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_GRILLE, m_vars.Grille, false); }));

			core->addOption(numberOption<std::int32_t>("Chassis")
				.addNumber(&m_vars.Chasis).addMin(0).addMax(VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_CHASSIS))
				.addClick([veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_CHASSIS, m_vars.Chasis, false); }));

			core->addOption(numberOption<std::int32_t>("Hood")
				.addNumber(&m_vars.Hood).addMin(0).addMax(VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_HOOD))
				.addClick([veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_HOOD, m_vars.Hood, false); }));

			core->addOption(numberOption<std::int32_t>("Fender")
				.addNumber(&m_vars.Fender).addMin(0).addMax(VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_FENDER))
				.addClick([veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_FENDER, m_vars.Fender, false); }));

			core->addOption(numberOption<std::int32_t>("Right Fender")
				.addNumber(&m_vars.RFender).addMin(0).addMax(VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_RIGHTFENDER))
				.addClick([veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_RIGHTFENDER, m_vars.RFender, false); }));

			core->addOption(numberOption<std::int32_t>("Roof")
				.addNumber(&m_vars.Roof).addMin(0).addMax(VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ROOF))
				.addClick([veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_ROOF, m_vars.Roof, false); }));

			core->addOption(numberOption<std::int32_t>("Engine")
				.addNumber(&m_vars.Engine).addMin(0).addMax(VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ENGINE))
				.addClick([veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_ENGINE, m_vars.Engine, false); }));

			core->addOption(numberOption<std::int32_t>("Brakes")
				.addNumber(&m_vars.Brakes).addMin(0).addMax(VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_BRAKES))
				.addClick([veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_BRAKES, m_vars.Brakes, false); }));

			core->addOption(numberOption<std::int32_t>("Transmission")
				.addNumber(&m_vars.Transmission).addMin(0).addMax(VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_TRANSMISSION))
				.addClick([veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_TRANSMISSION, m_vars.Transmission, false); }));

			core->addOption(numberOption<std::int32_t>("Horn")
				.addNumber(&m_vars.Horns).addMin(0).addMax(VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_HORNS))
				.addClick([veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_HORNS, m_vars.Horns, false); }));

			core->addOption(numberOption<std::int32_t>("Suspension")
				.addNumber(&m_vars.Suspension).addMin(0).addMax(VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_SUSPENSION))
				.addClick([veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_SUSPENSION, m_vars.Suspension, false); }));

			core->addOption(numberOption<std::int32_t>("Armor")
				.addNumber(&m_vars.Armor).addMin(0).addMax(VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ARMOR))
				.addClick([veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_ARMOR, m_vars.Armor, false); }));

			core->addOption(numberOption<std::int32_t>("Turbo")
				.addNumber(&m_vars.Turbo).addMin(0).addMax(VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_TURBO))
				.addClick([veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_TURBO, m_vars.Turbo, false); }));

			core->addOption(numberOption<std::int32_t>("Tire Smoke")
				.addNumber(&m_vars.TSmoke).addMin(0).addMax(VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_TIRESMOKE))
				.addClick([veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_TIRESMOKE, m_vars.TSmoke, false); }));

			core->addOption(numberOption<std::int32_t>("Xenon")
				.addNumber(&m_vars.Xenon).addMin(0).addMax(VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_XENONLIGHTS))
				.addClick([veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_XENONLIGHTS, m_vars.Xenon, false); }));

			core->addOption(numberOption<std::int32_t>("Wheels")
				.addNumber(&m_vars.Wheels).addMin(0).addMax(VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_FRONTWHEELS))
				.addClick([veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_FRONTWHEELS, m_vars.Wheels, false); }));

			core->addOption(numberOption<std::int32_t>("Windows")
				.addNumber(&m_vars.Windows).addMin(0).addMax(VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_WINDOWS))
				.addClick([veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_WINDOWS, m_vars.Windows, false); }));

			core->addOption(numberOption<std::int32_t>("Hydraulics")
				.addNumber(&m_vars.Hydraulics).addMin(0).addMax(VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_HYDRULICS))
				.addClick([veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_HYDRULICS, m_vars.Hydraulics, false); }));

			core->addOption(numberOption<std::int32_t>("Engine Block")
				.addNumber(&m_vars.EngineBlock).addMin(0).addMax(VEHICLE::GET_NUM_VEHICLE_MODS(veh, MOD_ENGINE_BLOCK))
				.addClick([veh] { VEHICLE::SET_VEHICLE_MOD(veh, MOD_ENGINE_BLOCK, m_vars.EngineBlock, false); }));
		});

		renderer::addSubmenu("Rear Bumper", "LSC_RBUMPER", [](core* core) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
				if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
					for (std::int32_t i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_REARBUMPER); i++) {
						const char* label = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(vehicle, MOD_REARBUMPER, i));
						core->addOption(buttonOption(!strcmp(label, "NULL") ? "Stock" : label)
							.addClick([=] { VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_REARBUMPER, i, FALSE); }));
					}
				}
				else {
					core->addOption(buttonOption("~c~Empty"));
				}
			}
			else {
				core->addOption(buttonOption("~c~Empty"));
			}
			});

		renderer::addSubmenu("Front Bumper", "LSC_FBUMPER", [](core* core) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
				if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
					for (std::int32_t i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_FRONTBUMPER); i++) {
						const char* label = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(vehicle, MOD_FRONTBUMPER, i));
						core->addOption(buttonOption(!strcmp(label, "NULL") ? "Stock" : label)
							.addClick([=] { VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_FRONTBUMPER, i, FALSE); }));
					}
				}
				else {
					core->addOption(buttonOption("~c~Empty"));
				}
			}
			else {
				core->addOption(buttonOption("~c~Empty"));
			}
		});

		renderer::addSubmenu("Spoiler", "LSC_SPOILER", [](core* core) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
				if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
					for (std::int32_t i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_SPOILER); i++) {
						const char* label = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(vehicle, MOD_SPOILER, i));
						core->addOption(buttonOption(!strcmp(label, "NULL") ? "Stock" : label)
							.addClick([=] { VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_SPOILER, i, FALSE); }));
					}
				}
				else {
					core->addOption(buttonOption("~c~Empty"));
				}
			}
			else {
				core->addOption(buttonOption("~c~Empty"));
			}
		});

		renderer::addSubmenu("Exhaust", "LSC_EXHAUST", [](core* core) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
				if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
					for (std::int32_t i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_EXHAUST); i++) {
						const char* label = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(vehicle, MOD_EXHAUST, i));
						core->addOption(buttonOption(!strcmp(label, "NULL") ? "Stock" : label)
							.addClick([=] { VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_ARMOR, i, FALSE); }));
					}
				}
				else {
					core->addOption(buttonOption("~c~Empty"));
				}
			}
			else {
				core->addOption(buttonOption("~c~Empty"));
			}
		});

		renderer::addSubmenu("Armour", "LSC_ARMOUR", [](core* core) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
				if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
					for (std::int32_t i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_ARMOR); i++) {
						std::stringstream ss; ss << "CMOD_ARM_" << i + 1;
						core->addOption(buttonOption(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(ss.str().c_str()))
							.addClick([=] { VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_ARMOR, i, FALSE); }));
					}
				}
				else {
					core->addOption(buttonOption("~c~Empty"));
				}
			}
			else {
				core->addOption(buttonOption("~c~Empty"));
			}
		});

		renderer::addSubmenu("Suspension", "LSC_SUSPENSION", [](core* core) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
				if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
					for (std::int32_t i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_SUSPENSION); i++) {
						std::stringstream ss; ss << "CMOD_SUS_" << i + 1;
						core->addOption(buttonOption(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(ss.str().c_str()))
							.addClick([=] { VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_SUSPENSION, i, FALSE); }));
					}
				}
				else {
					core->addOption(buttonOption("~c~Empty"));
				}
			}
			else {
				core->addOption(buttonOption("~c~Empty"));
			}
		});

		renderer::addSubmenu("Brakes", "LSC_BRAKES", [](core* core) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
				if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
					for (std::int32_t i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_BRAKES); i++) {
						std::stringstream ss; ss << "CMOD_BRA_" << i + 1;
						core->addOption(buttonOption(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(ss.str().c_str()))
							.addClick([=] { VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_BRAKES, i, FALSE); }));
					}
				}
				else {
					core->addOption(buttonOption("~c~Empty"));
				}
			}
			else {
				core->addOption(buttonOption("~c~Empty"));
			}
		});

		renderer::addSubmenu("Transmission", "LSC_TRANSMISSION", [](core* core) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
				if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
					for (std::int32_t i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_TRANSMISSION); i++) {
						std::stringstream ss; ss << "CMOD_GBX_" << i + 1;
						core->addOption(buttonOption(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(ss.str().c_str()))
							.addClick([=] { VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_TRANSMISSION, i, FALSE); }));
					}
				}
				else {
					core->addOption(buttonOption("~c~Empty"));
				}
			}
			else {
				core->addOption(buttonOption("~c~Empty"));
			}
		});

		renderer::addSubmenu("Engine", "LSC_ENGINE", [](core* core) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE)) {
				std::int32_t vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
				if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
					for (std::int32_t i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_ENGINE); i++) {
						std::stringstream ss; ss << "CMOD_ENG_" << i + 2;
						core->addOption(buttonOption(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(ss.str().c_str()))
							.addClick([=] { VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_ENGINE, i, FALSE); }));
					}
				}
				else {
					core->addOption(buttonOption("~c~Empty"));
				}
			}
			else {
				core->addOption(buttonOption("~c~Empty"));
			}
		});

		renderer::addSubmenu("Vehicle Proofs", "Vehicle Proofs", [](core* core) {
			core->addOption(toggleOption("Bullet Proof")
				.addToggle(&m_vars.bullet_proof));

			core->addOption(toggleOption("Fire Proof")
				.addToggle(&m_vars.fire_proof));

			core->addOption(toggleOption("Explosion Proof")
				.addToggle(&m_vars.explosion_proof));

			core->addOption(toggleOption("Collision Proof")
				.addToggle(&m_vars.collision_proof));

			core->addOption(toggleOption("Melee Proof")
				.addToggle(&m_vars.melee_proof));

			core->addOption(toggleOption("Drown Proof")
				.addToggle(&m_vars.drown_proof));
				
		});

		renderer::addSubmenu("Vehicle Doors", "Vehicle Doors", [](core* core) {
			core->addOption(buttonOption("Open All Doors")
				.addClick([] {
					VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0, true, false);
					VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 1, true, false);
					VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 2, true, false);
					VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 3, true, false);
					VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 4, true, false);
					VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 5, true, false);
					VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 6, true, false);
					VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 7, true, false);
					}));

			core->addOption(buttonOption("Close All Doors")
				.addClick([] { VEHICLE::SET_VEHICLE_DOORS_SHUT(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), true); }));

			core->addOption(buttonOption("Open Front Left Door")
				.addClick([] { VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 0, true, false); }));

			core->addOption(buttonOption("Open Front Right Door")
				.addClick([] { VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 1, true, false); }));

			core->addOption(buttonOption("Open Back Left Door")
				.addClick([] { VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 2, true, false); }));

			core->addOption(buttonOption("Open Back Right Door")
				.addClick([] { VEHICLE::SET_VEHICLE_DOOR_OPEN(PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()), 3, true, false); }));
		});
	}

	void vehicle_mods_menu::update() {
		render();
		getVehicleHealthMenu()->update();
		getVehicleMovementMenu()->update();
		getVehicleBoostMenu()->update();
		getVehicleMultipliersMenu()->update();
		getVehicleWeaponsMenu()->update();
		getVehicleParticlesMenu()->update();
		getVehicleCollisionMenu()->update();
		getVehicleGravityMenu()->update();
		getVehicleRampsMenu()->update();
		getVehicleTyreTracksMenu()->update();
		getVehicleModifiersMenu()->update();

		ENTITY::SET_ENTITY_PROOFS(PLAYER::PLAYER_PED_ID(), m_vars.bullet_proof, m_vars.fire_proof, m_vars.explosion_proof, m_vars.collision_proof, m_vars.melee_proof, 0, 0, m_vars.drown_proof);

		if (m_vars.m_scorched) {
			ENTITY::SET_ENTITY_RENDER_SCORCHED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), true);
		}
		else {
			ENTITY::SET_ENTITY_RENDER_SCORCHED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), false);
		}

		Ped playerPed = PLAYER::PLAYER_PED_ID();
		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
		DWORD model = ENTITY::GET_ENTITY_MODEL(veh);


		if (m_vars.m_rainbow_prime) {
			if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
				RGBFadee();
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(veh, r, g, b);

			}
		}
		if (m_vars.m_rainbow_second) {
			if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
				RGBFadee();
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(veh, r, g, b);

			}
		}
		if (m_vars.m_rainbow_tyre) {
			if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
				RGBFadee();
				VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(veh, r, g, b);

			}
		}

		if (m_vars.m_instant_stop) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) {
				ENTITY::FREEZE_ENTITY_POSITION(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), Util::is_key_pressed(VK_SPACE) ? true : false);
			}
		}

		if (m_vars.m_instant_enter) {
			PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), PED::GET_VEHICLE_PED_IS_ENTERING(PLAYER::PLAYER_PED_ID()), -1);
			PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), PED::GET_VEHICLE_PED_IS_TRYING_TO_ENTER(PLAYER::PLAYER_PED_ID()), -1);
		}
	}
}