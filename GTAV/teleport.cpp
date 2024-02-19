#include "pch.h"
#include "teleport.h"
#include "features/manager/manager.h"
#include "menu/util/globals.h"
#include "gui/options/option.h"
#include "gui/util/panels.h"
#include "rage/classes/CPed.h"
#include "menu/util/control.h"
#include "gui/util/notify.h"
#include "rage/classes/CBlipList.h"
using namespace base::gui;
using namespace menu::teleport::vars;

namespace menu::teleport::vars {
	variables m_vars;

	struct teleport_location { std::string str; float x; float y; float z; };
	std::vector<teleport_location> locations_underwater = {
	   { "Dead Sea Monster", -3373.726f, 504.714f, -24.656f },
	   { "Humane Labs Tunnel", 3619.749f, 2742.740f, 28.690f },
	   { "Sunken Body", -3161.078f, 3001.998f, -37.974f },
	   { "Sunken Cargo Ship", 3199.748f, -379.018f, -22.500f },
	   { "Sunken Plane", -942.350f, 6608.752f, -20.912f },
	   { "Underwater Hatch", 4273.950f, 2975.714f, -170.746f },
	   { "Underwater UFO", 762.426f, 7380.371f, -111.377f },
	   { "Underwater Tank", 4201.633f, 3643.821f, -39.016f }
	};

	std::vector<teleport_location> locations_inside = {
	   { "Strip Club DJ Booth", 126.135f, -1278.583f, 29.270f },
	   { "Blaine County Savings Bank", -109.299f, 6464.035f, 31.627f },
	   { "Police Station", 436.491f, -982.172f, 30.699f },
	   { "Humane Labs Entrance", 3619.749f, 2742.740f, 28.690f },
	   { "Humane Labs Tunnel", 3525.495f, 3705.301f, 20.992f },
	   { "Ammunation Office", 12.494f, -1110.130f, 29.797f },
	   { "Ammunation Gun Range", 22.153f, -1072.854f, 29.797f },
	   { "Meth Lab", 1391.773f, 3608.716f, 38.942f },
	   { "Pacific Standard Bank Vault", 255.851f, 217.030f, 101.683f },
	   { "FIB Building", 135.733f, -749.216f, 258.152f },
	   { "IAA Office", 117.220f, -620.938f, 206.047f },
	   { "Torture Room", 147.170f, -2201.804f, 4.688f },
	   { "Zancudo Control Tower", -2356.094f, 3248.645f, 101.451f },
	   { "Solomon's Office", -1003.96f, -477.95f, 50.03f }
	};

	std::vector<teleport_location> locations_outside = {
	   { "LS Customs", -365.425f, -131.809f, 37.873f },
	   { "IAA Roof", 134.085f, -637.859f, 262.851f },
	   { "FIB Roof", 150.126f, -754.591f, 262.865f },
	   { "Maze Bank Roof", -75.015f, -818.215f, 326.176 },
	   { "Mt Chilad", 450.718f, 5566.614f, 806.183f },
	   { "Hippy Camp", 2476.712f, 3789.645f, 41.226f },
	   { "Marlowe Vineyards", -1868.971f, 2095.674f, 139.115f },
	   { "Abandoned Mine", -595.342f, 3608.716f, 38.942f },
	   { "Merryweather Dock", 486.417f, -3339.692f, 6.070f },
	   { "Cargo Ship", 899.678f, -2882.191f, 19.013f },
	   { "Del Perro Pier", -1850.127f, -1231.751f, 13.017f },
	   { "Play Boy Mansion", -1475.234, 167.088f, 55.841f }
	};

	std::vector<teleport_location> locations_pop = {
	   { "Airport Airstrip", -1336.000f, -3044.000f, 13.900f },
	   { "Construction Crane", -119.860f, -976.439f, 306.339f },
	   { "Altruist Radio Tower", -1002.000f, 4842.000f, 280.000f },
	   { "Galileo Observatory Roof", -438.796f, 1075.821f, 353.000f },
	   { "Black UFO", -2052.662f, 3236.953f, 1466.315f },
	   { "Maza Bank Roof", -75.015f, -818.215f, 326.176f },
	   { "Mors Mutual Impound", -222.198f, -1185.850, 23.029f }
	};

	std::vector<teleport_location> locations_airstrips = {
	   { "Airport Runway", -1336.000f, -3044.000f, 13.900f },
	   { "Grapeseed Runway", 2136.51f, 4810.95f, 41.20f },
	   { "Sandy Shores Runway", 1707.08f, 3251.56f, 41.02f },
	   { "Fort Zancudo Runway", -2022.53f, 2867.f, 32.91f },
	   { "Airport Helipad", -1159.51f, -2889.13f, 13.95f },
	   { "Sandy Shores Helipad", 1781.56f, 3249.81f, 42.12f },
	   { "Fort Zancudo Helipad", -1859.f, 2816.f, 32.81f }
	};



	int getIdealSwitch(Vector3 from, Vector3 to) {
		return STREAMING::GET_IDEAL_PLAYER_SWITCH_TYPE(from, to);
	}

	void teleportToCoords(Vector3 coords, bool only_player, std::function<void(Vector3)> callback, bool no_tp) {
		if (m_vars.m_transition) {
			util::fiber::pool::add([=] {
				uint32_t hash = MISC::GET_HASH_KEY(*patterns::is_session_started ? "mp_m_freemode_01" : "player_zero");
				menu::control::requestModel(hash);
				auto model = hash;
					Ped ped = PED::CREATE_PED(13, model, coords, 0.f, true, false);
					if (ENTITY::DOES_ENTITY_EXIST(ped)) {
						STREAMING::START_PLAYER_SWITCH(PLAYER::PLAYER_PED_ID(), ped, 0, getIdealSwitch(ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true), coords));
						ENTITY::SET_ENTITY_AS_MISSION_ENTITY(ped, true, true);
						ENTITY::DELETE_ENTITY(&ped);

						if (STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS()) {
							while (STREAMING::GET_PLAYER_SWITCH_STATE() != 8) {
								util::fiber::sleep(100);

								if (STREAMING::GET_PLAYER_SWITCH_STATE() == 12) break;
							}

							if (m_vars.m_include_current_vehicle && !only_player) {
								if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) {
									Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), -1, 0);
									if (driver == PLAYER::PLAYER_PED_ID()) {
										if (!no_tp) ENTITY::SET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), coords, false, false, false, false);
										callback(coords);
									}
									else {
										// request control
										if (menu::control::request_control(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false))) {
											if (!no_tp) ENTITY::SET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), coords, false, false, false, false);
											callback(coords);
										}
									}
								}
								else {
									if (!no_tp) ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), coords, false, false, false, false);
									callback(coords);
								}
							}
							else {
								if (!no_tp) ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), coords, false, false, false, false);
								callback(coords);
							}
						}
					}
				});
		}
		else {
			if (m_vars.m_include_current_vehicle && !only_player) {
				if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) {
					Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), -1, 0);
					if (driver == PLAYER::PLAYER_PED_ID()) {
						if (!no_tp) ENTITY::SET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), coords, false, false, false, false);
						callback(coords);
					}
					else {
						// request control
						if (menu::control::request_control(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false))) {
							if (!no_tp) ENTITY::SET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), coords, false, false, false, false);
							callback(coords);
						}
					}
				}
				else {
					if (!no_tp) ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), coords, false, false, false, false);
					callback(coords);
				}
			}
			else {
				if (!no_tp) ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), coords, false, false, false, false);
				callback(coords);
			}
		}
	}

	void teleport_to_objective() {
		bool teleported = false;

		CBlipList* list = patterns::blip_list;
		if (list) {
			for (int i = 0; i < 1500; i++) {
				CBlip* blip = list->m_blips[i];
				if (blip) {
					int color = blip->m_color;
					int icon = blip->m_sprite;

					if ((icon == 306) || (color == 66 && icon == 1) || (color == 60 && icon == 1) ||
						(color == 5 && icon == 1) || (color == 0 && icon == 38) || (color == 2 && icon == 1) || (color == 3 && icon == 1)) {
						Vector3 coords = Vector3::to_padded({ blip->m_coords.x, blip->m_coords.y, blip->m_coords.z });
						if (coords.empty()) {
							menu::notify::stacked("Failed to teleport to objective");
						}
						else {
							teleported = true;
							teleportToCoords(coords);
							break;
						}
					}
				}
			}
		}

		if (!teleported) {
			menu::notify::stacked("Failed to find objective");
		}
	}

	void teleport_to_nearest_vehicle() {
		float closest_distance = std::numeric_limits<float>::max();
		Vehicle closest_vehicle = -1;
		int vehicle_seat = -2;

		for (const auto vehicle : menu::control::get_entities(true, false)) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false) && vehicle == PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false)) return;

				Vector3 coords = ENTITY::GET_ENTITY_COORDS(vehicle, true);

				float distance = MISC::GET_DISTANCE_BETWEEN_COORDS(ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true), coords, false);
				if (distance < closest_distance) {
					Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(vehicle, -1, 0);
						if (!ENTITY::DOES_ENTITY_EXIST(driver) || !PED::IS_PED_A_PLAYER(driver)) {
							closest_distance = distance;
								closest_vehicle = vehicle;
								vehicle_seat = -1;
								return;
						}

					for (int i = 0; i < VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(vehicle); i++) {
						Ped ped = VEHICLE::GET_PED_IN_VEHICLE_SEAT(vehicle, i, 0);
						if (!ENTITY::DOES_ENTITY_EXIST(ped)) {
							closest_distance = distance;
							closest_vehicle = vehicle;
							vehicle_seat = i;
							return;
						}
					}
				}
		}

		if (closest_vehicle != -1) {
			if (ENTITY::DOES_ENTITY_EXIST(closest_vehicle)) {
				Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(closest_vehicle, -1, 0);
				if (ENTITY::DOES_ENTITY_EXIST(driver)) {
					if (PED::IS_PED_A_PLAYER(driver)) {
						menu::control::request_control(closest_vehicle);
					}
					else {
						TASK::CLEAR_PED_TASKS_IMMEDIATELY(driver);
					}
				}

				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), closest_vehicle, vehicle_seat);
			}
		}
	}

	void teleport_to_personal_vehicle() {
		bool found = false;

		for (int i = 225; i < 227; i++) {
			int handle = HUD::GET_FIRST_BLIP_INFO_ID(i);
			if (HUD::DOES_BLIP_EXIST(handle)) {
				Vector3 coords = HUD::GET_BLIP_COORDS(handle);
				if (!coords.empty()) {
					found = true;

					Vehicle vehicle = VEHICLE::GET_CLOSEST_VEHICLE(coords, 5.f, 0, 70);
					Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(vehicle, -1, 0);
					if (ENTITY::DOES_ENTITY_EXIST(driver)) {
						if (PED::IS_PED_A_PLAYER(driver)) {
							menu::control::request_control(vehicle);
						}
						else {
							TASK::CLEAR_PED_TASKS_IMMEDIATELY(driver);
						}
					}

					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle, -1);
					break;
				}
			}
		}

		if (!found) {
			menu::notify::stacked("Failed to find personal vehicle");
		}
	}

	void teleport_to_last_vehicle() {
		Vehicle vehicle = PLAYER::GET_PLAYERS_LAST_VEHICLE();
		if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
			Ped driver = VEHICLE::GET_PED_IN_VEHICLE_SEAT(vehicle, -1, 0);
			if (ENTITY::DOES_ENTITY_EXIST(driver)) {
				if (PED::IS_PED_A_PLAYER(driver)) {
					menu::control::request_control(vehicle);
				}
				else {
					TASK::CLEAR_PED_TASKS_IMMEDIATELY(driver);
				}
			}

			PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle, -1);		
		}
		else {
			menu::notify::stacked("Failed to find last vehicle");
		}
	}

	void teleport_to_waypoint() {
		util::fiber::pool::add([=] {
			Vector3 coords = HUD::GET_BLIP_INFO_ID_COORD(HUD::GET_FIRST_BLIP_INFO_ID(8));
			if (coords.empty()) {
				menu::notify::stacked("Failed to find waypoint");
				return;
			}

			Entity entity = PLAYER::PLAYER_PED_ID();
			if (m_vars.m_include_current_vehicle && PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) {
				entity = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			}

			bool ground_found = false;
			float ground_check_height[] = { 100.0f, 150.0f, 50.0f, 0.0f, 200.0f, 250.0f, 300.0f, 350.0f, 400.0f, 450.0f, 500.0f, 550.0f, 600.0f, 650.0f, 700.0f, 750.0f, 800.0f };
			for (int i = 0; i < sizeof(ground_check_height) / sizeof(float); i++) {
				//ENTITY::SET_ENTITY_COORDS_NO_OFFSET(entity, { coords.x, coords.y, ground_check_height[i] }, 0, 0, 1);
				teleportToCoords(coords, false, [=](Vector3) { coords.x, coords.y, ground_check_height[i]; });
				util::fiber::sleep(100);
				if (MISC::GET_GROUND_Z_FOR_3D_COORD({ coords.x, coords.y, ground_check_height[i] }, &coords.z, 0, 0)) {
					ground_found = true;
					break;
				}
			}

			if (!ground_found) {
				coords.z = 1000.0f;
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 1, 0);
			}
			teleportToCoords(coords, false);
			//ENTITY::SET_ENTITY_COORDS(entity, coords, false, false, false, false);
		});
	}

	inline float m_directions[6] = { 5.f, 5.f, 5.f, 5.f, 5.f, 5.f };
	inline void teleport_direction(int direction) {
		Vector3 coords = { 0.f, 0.f, 0.f };

		switch (direction) {
		case 0:
			coords.y = m_directions[0] + 1.f;
			break;
		case 1:
			coords.y = (m_directions[1] * -1.f) + 1.f;
			break;
		case 2:
			coords.z = m_directions[2] + 1.f;
			break;
		case 3:
			coords.z = (m_directions[3] * -1.f) + 1.f;
			break;
		case 4:
			coords.x = (m_directions[4] * -1.f) + 1.f;
			break;
		case 5:
			coords.x = m_directions[5] + 1.f;
			break;
		}

		Vector3 world = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), coords);
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(PLAYER::PLAYER_PED_ID(),world, false, false, false);

	}

}

namespace menu {

	void teleport_menu::render() {
		renderer::addSubmenu("Teleport", "Teleport", [](core* core) {
			core->addOption(submenuOption("Settings")
				.addTranslate()
				.setTarget("Teleport Settings"));

			core->addOption(buttonOption("Teleport to Waypoint")
				.addClick(teleport_to_waypoint));

			core->addOption(buttonOption("Teleport to Objective")
				.addClick(teleport_to_objective));

			core->addOption(buttonOption("Teleport to Last Vehicle")
				.addClick(teleport_to_last_vehicle));

			core->addOption(buttonOption("Teleport to Nearest Vehicle")
				.addClick(teleport_to_nearest_vehicle));

			core->addOption(buttonOption("Teleport Forward")
				.addClick([] { teleport_direction(0); }));

			core->addOption(buttonOption("Teleport Backward")
				.addClick([] { teleport_direction(1); }));

			core->addOption(buttonOption("Teleport Up")
				.addClick([] { teleport_direction(2); }));

			core->addOption(buttonOption("Teleport Down")
				.addClick([] { teleport_direction(3); }));

			core->addOption(breakOption("Locations"));

			core->addOption(submenuOption("Popular")
				.setTarget("tp_pop"));

			core->addOption(submenuOption("Airstrips")
				.setTarget("tp_airstrips"));

			core->addOption(submenuOption("Indoors")
				.setTarget("tp_inddors"));

			core->addOption(submenuOption("Outdoors")
				.setTarget("tp_ooutdoors"));

			core->addOption(submenuOption("Underwater")
				.setTarget("tp_underwater"));
		});

		renderer::addSubmenu("Settings", "Teleport Settings", [](core* core) {
			core->addOption(toggleOption("Teleport Animation")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_transition)
				.addTooltip("Might break in online"));

			core->addOption(toggleOption("Auto Teleport to Waypoint")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_auto_waypoint));

			core->addOption(toggleOption("Include Vehicle")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_include_current_vehicle));
		});

		renderer::addSubmenu("Airstrips", "tp_airstrips", [](core* core) {
			for (int i = 0; i < locations_airstrips.size(); i++) {
				Vector3 coords;
				coords.x = locations_airstrips[i].x;
				coords.y = locations_airstrips[i].y;
				coords.z = locations_airstrips[i].z;

				core->addOption(buttonOption(locations_airstrips[i].str.c_str())
					.addClick([=] { teleportToCoords(coords); }));
			}
		});
		renderer::addSubmenu("Popular", "tp_pop", [](core* core) {
			for (int i = 0; i < locations_pop.size(); i++) {
				Vector3 coords;
				coords.x = locations_pop[i].x;
				coords.y = locations_pop[i].y;
				coords.z = locations_pop[i].z;

				core->addOption(buttonOption(locations_pop[i].str.c_str())
					.addClick([=] { teleportToCoords(coords); }));
			}
		});
		renderer::addSubmenu("Outdoors", "tp_ooutdoors", [](core* core) {
			for (int i = 0; i < locations_outside.size(); i++) {
				Vector3 coords;
				coords.x = locations_outside[i].x;
				coords.y = locations_outside[i].y;
				coords.z = locations_outside[i].z;

				core->addOption(buttonOption(locations_outside[i].str.c_str())
					.addClick([=] { teleportToCoords(coords); }));
			}
		});
		renderer::addSubmenu("Indoors", "tp_inddors", [](core* core) {
			for (int i = 0; i < locations_inside.size(); i++) {
				Vector3 coords;
				coords.x = locations_inside[i].x;
				coords.y = locations_inside[i].y;
				coords.z = locations_inside[i].z;

				core->addOption(buttonOption(locations_inside[i].str.c_str())
					.addClick([=] { teleportToCoords(coords); }));
			}
			});
		renderer::addSubmenu("Underwater", "tp_underwater", [](core* core) {
			for (int i = 0; i < locations_underwater.size(); i++) {
				Vector3 coords;
				coords.x = locations_underwater[i].x;
				coords.y = locations_underwater[i].y;
				coords.z = locations_underwater[i].z;

				core->addOption(buttonOption(locations_underwater[i].str.c_str())
					.addClick([=] { teleportToCoords(coords); }));
			}
		});
	}

	void teleport_menu::update() {
		render();
	

	}
}