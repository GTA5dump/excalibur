#include "pch.h"
#include "vehicle_acrobatics.h"
#include "menu/util/globals.h"
#include "gui/options/option.h"
#include "gui/util/panels.h"
#include "rage/classes/CPed.h"
#include "rage/classes/CPlayerInfo.h"
#include "menu/util/control.h"
#include "menu/util/raycast.h"
#include "../../vehicle.h"

using namespace base::gui;
using namespace menu::vehicle::acrobatics::vars;

namespace menu::vehicle::acrobatics::vars {
	variables m_vars;

	void run_acrobatic(Vehicle vehicle, std::pair<Vector3, Vector3> data) {
		if (vehicle) {
			vehicle::vars::run_task(vehicle, [=](Vehicle veh) {
				ENTITY::APPLY_FORCE_TO_ENTITY(veh, 1, data.first, data.second, 0, true, true, true, false, true);
				});
		}
	}

	struct acrobatics_context {
		std::string name;
		std::pair<Vector3, Vector3> values;
	};

	std::vector<acrobatics_context> acrobatics = {
		{ "Wheelie", { { 0.f, 0.f, 1.f }, { 0.f, 5.0f, 0.f } } },
		{ "Kickflip", { { 0.f, 0.0f, 11.5f }, { 5.f, 0.f, 0.f } } },
		{ "Double Kickflip", { { 0.f, 0.0f, 21.f }, { 10.f, 0.f, 0.f } } },
		{ "Quadruple Kickflip", { { 0.f, 0.0f, 33.f }, { 15.f, 0.f, 0.f } } },
		{ "Leap", { { 0.f, 0.f, 20.f }, { 0.f, 0.f, 0.f } } },
		{ "Slingshot", { { 0.f, 0.f, 200.f }, { 0.f, 0.f, 0.f } } },
		{ "Backflip", { { 0.f, 0.f, 15.5f }, { 0.f, 1.3f, 0.f } } },
		{ "Frontflip", { { 0.f, 0.f, 15.5f }, { 0.f, -1.f, 0.f } } },
		{ "Right Jump", { { 0.f, 0.f, 2.8f }, { -3.f, 0.f, 0.f } } },
		{ "Left Jump", { { 0.f, 0.f, 2.8f }, { 3.f, 0.f, 0.f } } }
	};
}



namespace menu {

	void vehicle_acrobatics_menu::render() {
		renderer::addSubmenu("Vehicle Acrobatics", "Vehicle Acrobatics", [](core* core) {
			const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

			for (acrobatics_context& acrobat : acrobatics) {
				core->addOption(buttonOption(acrobat.name.c_str())
					.addClick([=] { run_acrobatic(vehicle, acrobat.values); }));
			}
		});
	}

	void vehicle_acrobatics_menu::update() {
		render();
	}
}