#include "pch.h"
#include "clearing.h"
#include "menu/util/control.h"

using namespace base::gui;

namespace menu {

	void clearing_menu::render() {
		renderer::addSubmenu("Clearing", "clearing", [](core* core) {
			auto coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 0);
			float range = 150;
			GRAPHICS::DRAW_MARKER(28, coords, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f }, { range, range, range }, 0, 0, 255, 160, false, false, 0, false, NULL, NULL, false);

			core->addOption(buttonOption("Clear Everything")
				.addClick([=] { MISC::CLEAR_AREA_LEAVE_VEHICLE_HEALTH(coords, range, 0, 0, 0, 0); }));

			core->addOption(buttonOption("Clear Cops")
				.addClick([=] { MISC::CLEAR_AREA_OF_COPS(coords, range, 0); }));

			core->addOption(buttonOption("Clear Objects")
				.addClick([=] { MISC::CLEAR_AREA_OF_OBJECTS(coords, range, 0); }));

			core->addOption(buttonOption("Clear Peds")
				.addClick([=] { MISC::CLEAR_AREA_OF_PEDS(coords, range, 0); }));

			core->addOption(buttonOption("Clear Projectiles")
				.addClick([=] { MISC::CLEAR_AREA_OF_PROJECTILES(coords, range, 0); }));

			core->addOption(buttonOption("Clear Vehicles")
				.addClick([=] { MISC::CLEAR_AREA_OF_VEHICLES(coords, range, 0, 0, 0, 0, 0, 0, 0); }));
		});
	}

	void clearing_menu::update() {
		render();

	
	}
}