#include "pch.h"
#include "entities.h"
#include "menu/util/control.h"

using namespace base::gui;
using namespace menu::world::entities::vars;

namespace menu::world::entities::vars {
	variables m_vars;


	const char* local_entity_type[2] = {
		"Vehicle", "Ped"
	}; inline std::size_t local_entity_type_id = 0;
}

namespace menu {

	void entities_menu::render() {
		renderer::addSubmenu("Entities", "local_entities", [](core* core) {
			core->addOption(scrollOption<const char*, std::size_t>("Entity Type")
				.addScroll(&local_entity_type).setPosition(&local_entity_type_id));

			if (local_entity_type_id == 0) {
				core->addOption(buttonOption("Enable Gravity")
					.addClick([] {
						for (auto vehicles : control::get_entities(true, false)) {
							VEHICLE::SET_VEHICLE_GRAVITY(vehicles, 1);
						}
						}));

				core->addOption(buttonOption("Disable Gravity")
					.addClick([] {
						for (auto vehicles : control::get_entities(true, false)) {
							Vector3 veh = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
							VEHICLE::SET_VEHICLE_GRAVITY(vehicles, 0);
						}
						}));

				core->addOption(buttonOption("Teleport to Me")
					.addClick([] {
						for (auto vehicles : control::get_entities(true, false)) {
							Vector3 veh = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
							ENTITY::SET_ENTITY_COORDS(vehicles, veh, 0, 0, 0, 0);
						}
						}));

				core->addOption(buttonOption("Drive to Me")
					.addClick([] {
						for (auto vehicles : control::get_entities(true, false)) {
							Ped ped = VEHICLE::GET_PED_IN_VEHICLE_SEAT(vehicles, -1, 0);
							Vector3 me = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
							if (ped) {
								TASK::TASK_VEHICLE_DRIVE_TO_COORD(ped, vehicles, me, 100, 1, ENTITY::GET_ENTITY_MODEL(vehicles), 16777216, 4, -1);
							}
						}
						}));

				core->addOption(buttonOption("Kick Driver")
					.addClick([] {
						for (auto vehicles : control::get_entities(true, false)) {
							Ped ped = VEHICLE::GET_PED_IN_VEHICLE_SEAT(vehicles, -1, 0);
							TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
						}
						}));

				core->addOption(buttonOption("Repair")
					.addClick([] {
						for (auto vehicles : control::get_entities(true, false)) {
							VEHICLE::SET_VEHICLE_FIXED(vehicles);
							VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(vehicles);
							VEHICLE::SET_VEHICLE_DIRT_LEVEL(vehicles, 0);

						}
						}));

				core->addOption(buttonOption("Boost")
					.addClick([] {
						for (auto vehicles : control::get_entities(true, false)) {
							VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicles, 100);
						}
						}));

				core->addOption(buttonOption("Explode")
					.addClick([] {
						for (auto vehicles : control::get_entities(true, false)) {
							VEHICLE::EXPLODE_VEHICLE(vehicles, true, false);
						}
						}));

				core->addOption(buttonOption("Delete")
					.addClick([] {
						for (auto vehicles : control::get_entities(true, false)) {
							ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehicles, true, true);
							ENTITY::DELETE_ENTITY(&vehicles);
						}
						}));

			}
			else if (local_entity_type_id == 1) {
				core->addOption(buttonOption("Teleport to Me")
					.addClick([] {
						for (auto peds : control::get_entities(false, true)) {
							Vector3 veh = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
							ENTITY::SET_ENTITY_COORDS(peds, veh, 0, 0, 0, 0);
						}
						}));

				core->addOption(buttonOption("Come to Me")
					.addClick([] {
						for (auto peds : control::get_entities(false, true)) {
							TASK::TASK_FOLLOW_TO_OFFSET_OF_ENTITY(peds, PLAYER::PLAYER_PED_ID(), { 0.0f, 0.0f, 0.0f }, 10, -1, 10.0f, 1);
						}
						}));

				core->addOption(buttonOption("Kill")
					.addClick([] {
						for (auto peds : control::get_entities(false, true)) {
							ENTITY::SET_ENTITY_HEALTH(peds, 0, 0);
						}
						}));

				core->addOption(buttonOption("Burn")
					.addClick([] {
						for (auto peds : control::get_entities(false, true)) {
							Vector3 pos = ENTITY::GET_ENTITY_COORDS(peds, 1);
							FIRE::ADD_EXPLOSION(pos, 12, 5, true, 0, 0, false);
						}
						}));

				core->addOption(buttonOption("Explode")
					.addClick([] {
						for (auto peds : control::get_entities(false, true)) {
							Vector3 pos = ENTITY::GET_ENTITY_COORDS(peds, 1);
							FIRE::ADD_EXPLOSION(pos, 0, 5, true, 0, 0, false);
						}
						}));

				core->addOption(buttonOption("Delete")
					.addClick([] {
						for (auto peds : control::get_entities(false, true)) {
							ENTITY::SET_ENTITY_COORDS_NO_OFFSET(peds, { 6400.f, 6400.f, 0.f }, false, false, false);
						}
						}));
			}
		});
	}

	void entities_menu::update() {
		render();

		
	}
}