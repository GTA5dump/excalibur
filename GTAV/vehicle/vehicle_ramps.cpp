#include "pch.h"
#include "vehicle_ramps.h"
#include "menu/util/globals.h"
#include "gui/options/option.h"
#include "gui/util/panels.h"
#include "rage/classes/CPed.h"
#include "rage/classes/CPlayerInfo.h"
#include "menu/util/control.h"
#include "menu/util/raycast.h"

using namespace base::gui;
using namespace menu::vehicle::ramps::vars;

namespace menu::vehicle::ramps::vars {
	variables m_vars;

	Object create_attached_ramp(Entity attach_to, uint32_t model, int pos = 0, bool opacitated = true) {
		menu::control::requestModel(model);

		Vector3 min, max;
		MISC::GET_MODEL_DIMENSIONS(model, &min, &max);

		Vector3 dim = { max.x - min.x, max.y - min.y, max.z - min.z };

		Vector3 coords = ENTITY::GET_ENTITY_COORDS(attach_to, true);
		
		*(unsigned short*)patterns::set_this_thread_networked = 0x9090;
		Object ramp = OBJECT::CREATE_OBJECT(model, coords, true, true, false);
		*(unsigned short*)patterns::set_this_thread_networked = 0x0574;

		switch (pos) {
		case 0:
			ENTITY::ATTACH_ENTITY_TO_ENTITY(ramp, attach_to, 0, /**/{ 0, dim.y, -0.5 }, /**/{ 0, 0, 180 }, true, true, true, false, 2, true, 0);
			break;

		case 1:ENTITY::ATTACH_ENTITY_TO_ENTITY(ramp, attach_to, 0, /**/{ 0, (-1) * dim.y, -0.5 }, /**/{ 0, 0, 0 }, true, true, true, false, 2, true, 0);
			break;

		case 2:ENTITY::ATTACH_ENTITY_TO_ENTITY(ramp, attach_to, 0, /**/{ (-1) * dim.x, 0, -0.5 }, /**/{ 0, 0, 270 }, true, true, true, false, 2, true, 0);
			break;

		case 3:ENTITY::ATTACH_ENTITY_TO_ENTITY(ramp, attach_to, 0, /**/{ dim.x, 0, -0.5 }, /**/{ 0, 0, 90 }, true, true, true, false, 2, true, 0);
			break;
		}

		if (opacitated) {
			ENTITY::SET_ENTITY_ALPHA(ramp, 100, true);
		}

		return ramp;
	}

	void attach() {
		const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) return;

		char buffer[50];
		sprintf_s(buffer, "PROP_MP_RAMP_0%i", m_vars.m_ramp_type);

		uint32_t model = MISC::GET_HASH_KEY(buffer);

		if (m_vars.m_front_ramp) {
			create_attached_ramp(vehicle, model, 0, m_vars.m_transparency);
		}

		if (m_vars.m_rear_ramp) {
			create_attached_ramp(vehicle, model, 1, m_vars.m_transparency);
		}

		if (m_vars.m_left_ramp) {
			create_attached_ramp(vehicle, model, 2, m_vars.m_transparency);
		}

		if (m_vars.m_right_ramp) {
			create_attached_ramp(vehicle, model, 3, m_vars.m_transparency);
		}
	}

	void detach() {
		if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) return;
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);

		const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

		uint32_t ramps[] = { 0xB157C9E4, 0xF4F1511E, 0x93948E5E };
		for (int i = 0; i < 3; i++) {
			int counter = 0;
		search:
			Object ramp = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(coords, 20.f, ramps[i], false, false, false);
			if (ramp) {
				if (ENTITY::DOES_ENTITY_EXIST(ramp) && ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(ramp, vehicle)) {
					menu::control::requestModel(ramp);

					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(ramp, true, true);
					ENTITY::DELETE_ENTITY(&ramp);

					counter++;

					if (counter < 20) {
						goto search;
					}
				}
			}
		}
	}
}

namespace menu {

	void vehicle_ramps_menu::render() {
		renderer::addSubmenu("Vehicle Ramps", "Vehicle Ramps", [](core* core) {
			const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

			core->addOption(numberOption<int>("Type")
				.addNumber(&m_vars.m_ramp_type)
				.addStep(1).addMin(1).addMax(3));

			core->addOption(toggleOption("Ramp Transparency")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_transparency));

			core->addOption(toggleOption("Front Ramp")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_front_ramp));

			core->addOption(toggleOption("Rear Ramp")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_rear_ramp));

			core->addOption(toggleOption("Left Ramp")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_left_ramp));

			core->addOption(toggleOption("Right Ramp")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_right_ramp));

			core->addOption(buttonOption("Apply Ramps")
				.addTranslate().addHotkey()
				.addClick(attach));

			core->addOption(buttonOption("Delete Attached Ramps")
				.addTranslate().addHotkey()
				.addClick(detach));
		});
	}

	void vehicle_ramps_menu::update() {
		render();

		const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
	}
}