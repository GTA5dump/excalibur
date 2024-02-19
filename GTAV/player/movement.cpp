#include "pch.h"
#include "movement.h"
#include "features/manager/manager.h"
#include "menu/util/globals.h"
#include "gui/options/option.h"
#include "gui/util/panels.h"
#include "rage/classes/CPed.h"

using namespace base::gui;
using namespace menu::player::movement::vars;

namespace menu::player::movement::vars {
	variables m_vars;

	Vector3 get_direction(Vector3 rotation) {
		Vector3 tmp;
		tmp.y = rotation.z * 0.0174532924f;
		tmp.x = rotation.x * 0.0174532924f;
		tmp.z = abs(cos(tmp.x));

		return Vector3((-sin(tmp.y)) * tmp.z, (cos(tmp.y)) * tmp.z, sin(tmp.x));
	}

}

namespace menu {

	void player_movement_menu::render() {
		renderer::addSubmenu("Movement", "Player Movement", [](core* core) {
			core->addOption(toggleNumberOption<float>("No Clip")
				.addToggle(&m_vars.m_no_clip).addNumber(&m_vars.m_no_clip_speed)
				.addMin(1.0f).addMax(100.f).addStep(0.1f).setPrecision(2));

			core->addOption(toggleNumberOption<float>("Run Speed")
				.addToggle(&m_vars.m_run_speed).addNumber(&m_vars.m_run_multiplier)
				.addMin(1.0f).addMax(100.f).addStep(0.01f).setPrecision(2));

			core->addOption(toggleNumberOption<float>("Swim Speed ")
				.addToggle(&m_vars.m_swim_speed).addNumber(&m_vars.m_swim_multiplier)
				.addMin(1.0f).addMax(100.f).addStep(0.1f).setPrecision(2));

			core->addOption(toggleOption("Slide Run")
				.addHotkey().addTranslate()
				.addToggle(&m_vars.m_slide_run));

			core->addOption(toggleOption("Super Jump")
				.addHotkey().addTranslate()
				.addToggle(&m_vars.m_beast_jump));

			core->addOption(toggleOption("Swim in Air")
				.addHotkey().addTranslate()
				.addToggle(&m_vars.m_swim_in_air));

			core->addOption(toggleOption("Walk on Air")
				.addHotkey().addTranslate()
				.addToggle(&m_vars.m_walk_on_air));

			core->addOption(toggleOption("Freeze")
				.addHotkey().addTranslate()
				.addToggle(&m_vars.m_freeze));
		});
	}

	void player_movement_menu::update() {
		render();


		if (m_vars.m_no_clip) {
			Vector3 camera_direction = get_direction(CAM::GET_GAMEPLAY_CAM_ROT(0));
			float speed = m_vars.m_no_clip_speed;

			Entity target = !PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false) ? PLAYER::PLAYER_PED_ID() : PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			Vector3 position = ENTITY::GET_ENTITY_COORDS(target, false);

			if (ENTITY::IS_ENTITY_A_PED(target))
				CAM::SET_FOLLOW_PED_CAM_VIEW_MODE(2);
			else
				CAM::SET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL(2);

			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xA2719263, 0, false, true);
			ENTITY::SET_ENTITY_COLLISION(target, false, false);
			ENTITY::FREEZE_ENTITY_POSITION(target, true);

			Vector3 rotation = CAM::GET_GAMEPLAY_CAM_ROT(0);
			ENTITY::SET_ENTITY_ROTATION(target, rotation.x, rotation.y, rotation.z, 2, true);

			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)eControllerInputs::INPUT_MOVE_UP_ONLY))
			{
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(target, { position.x + (camera_direction.x * speed), position.y + (camera_direction.y * speed), position.z + (camera_direction.z * speed) }, false, false, false);
			}
			else if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)eControllerInputs::INPUT_MOVE_DOWN_ONLY))
			{
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(target, { position.x - (camera_direction.x * speed), position.y - (camera_direction.y * speed), position.z - (camera_direction.z * speed) }, false, false, false);
			}
		}
		else {
			Entity target = !PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false) ? PLAYER::PLAYER_PED_ID() : PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

			ENTITY::SET_ENTITY_COLLISION(target, true, true);
			ENTITY::FREEZE_ENTITY_POSITION(target, false);
		}

		if (m_vars.m_beast_jump) {
			if (PAD::IS_CONTROL_JUST_PRESSED(0, 22) && !PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), NULL) && !ENTITY::IS_ENTITY_IN_AIR(PLAYER::PLAYER_PED_ID())) {
				TASK::TASK_JUMP(PLAYER::PLAYER_PED_ID(), true, true, true);
			}
		}

		if (m_vars.m_swim_in_air) {
			PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 65, true);
		}
		else {
			PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 65, false);
		}

		if (m_vars.m_slide_run) {
			if (TASK::IS_PED_RUNNING(PLAYER::PLAYER_PED_ID()) || TASK::IS_PED_SPRINTING(PLAYER::PLAYER_PED_ID())) {
				ENTITY::APPLY_FORCE_TO_ENTITY(PLAYER::PLAYER_PED_ID(), 1, { 0.f, 1.5f, 0.f }, { 0.f, 0.f, 0.f }, 1, true, true, true, false, true);
			}
		}

		if (m_vars.m_freeze) {
			ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), true);
		}
		else {
			ENTITY::FREEZE_ENTITY_POSITION(PLAYER::PLAYER_PED_ID(), false);
		}

		if (m_vars.m_run_speed)
			(*patterns::ped_factory)->m_local_ped->m_player_info->m_run_speed = m_vars.m_run_multiplier;
		else if (!m_vars.m_run_speed)
			(*patterns::ped_factory)->m_local_ped->m_player_info->m_run_speed = 1.0f;


		if (m_vars.m_swim_speed)
			(*patterns::ped_factory)->m_local_ped->m_player_info->m_swim_speed = m_vars.m_swim_multiplier;
		else if (!m_vars.m_swim_speed)
			(*patterns::ped_factory)->m_local_ped->m_player_info->m_swim_speed = 1.0f;
	}
}