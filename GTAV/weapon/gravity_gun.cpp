#include "pch.h"
#include "gravity_gun.h"
#include "menu/util/globals.h"
#include "gui/options/option.h"
#include "gui/util/panels.h"
#include "rage/classes/CPed.h"
#include "rage/classes/CPlayerInfo.h"
#include "menu/util/control.h"
#include "menu/util/raycast.h"
#include "gui/util/timer.h"


using namespace base::gui;
using namespace menu::weapon::gravity_gun::vars;

namespace menu::weapon::gravity_gun::vars {
	variables m_vars;

	CWeaponInfo* get_weapon_info() {
		CPed* ped = (*patterns::ped_factory)->m_local_ped;
		if (ped) {
			CPedWeaponManager* weapon_manager = ped->m_weapon_manager;
			if (weapon_manager) {
				return weapon_manager->m_weapon_info;
			}
		}

		return nullptr;
	}

	Vector3 get_direction(Vector3 rotation) {
		Vector3 tmp;
		tmp.y = rotation.z * 0.0174532924f;
		tmp.x = rotation.x * 0.0174532924f;
		tmp.z = abs(cos(tmp.x));

		return Vector3((-sin(tmp.y)) * tmp.z, (cos(tmp.y)) * tmp.z, sin(tmp.x));
	}

	bool isPedShooting(Ped ped) {
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(ped, 1);
		return PED::IS_PED_SHOOTING_IN_AREA(ped, coords, coords, true, true);
	}

	void gravity_gun() {
		static int timer = 0;
		if (PLAYER::IS_PLAYER_FREE_AIMING(PLAYER::PLAYER_PED_ID())) {
			Vector3 position = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), { 0.4f, 0.0f, 0.8f });

			if (ENTITY::DOES_ENTITY_EXIST(m_vars.m_entity)) {
				PAD::SET_INPUT_EXCLUSIVE(0, ControlFrontendUp);
				PAD::SET_INPUT_EXCLUSIVE(0, ControlFrontendDown);

				if (PAD::IS_CONTROL_PRESSED(0, ControlFrontendUp)) {
					m_vars.m_distance++;
				}
				else if (PAD::IS_CONTROL_JUST_PRESSED(0, ControlFrontendDown) && m_vars.m_distance > 3.f) {
					m_vars.m_distance--;
				}

				menu::control::request_control(m_vars.m_entity);

				auto velocity = ((position + (get_direction(CAM::GET_GAMEPLAY_CAM_ROT(0)) * m_vars.m_distance)) - ENTITY::GET_ENTITY_COORDS(m_vars.m_entity, false)) * m_vars.m_force;
				ENTITY::SET_ENTITY_VELOCITY(m_vars.m_entity, velocity);

				if (isPedShooting(PLAYER::PLAYER_PED_ID())) {
					velocity = ((position + (get_direction(CAM::GET_GAMEPLAY_CAM_ROT(0)) * 5000.f)) - ENTITY::GET_ENTITY_COORDS(m_vars.m_entity, false)) * m_vars.m_force;
					ENTITY::SET_ENTITY_VELOCITY(m_vars.m_entity, velocity);
					m_vars.m_entity = 0;
					timer = MISC::GET_GAME_TIMER() + 750;
				}
			}
			else {
				m_vars.m_entity = 0;

				if (MISC::GET_GAME_TIMER() > timer) {
					auto bulletCoord = raycast::m_ShapeTestDestination;
					if (!raycast::IsEmpty(bulletCoord)) {
						m_vars.m_entity = raycast::m_ShapeTestEntity;

						if (ENTITY::IS_ENTITY_A_PED(m_vars.m_entity)) {
							if (PED::IS_PED_IN_ANY_VEHICLE(m_vars.m_entity, false)) {
								m_vars.m_entity = PED::GET_VEHICLE_PED_IS_IN(m_vars.m_entity, false);
							}
							else {
								if (PED::IS_PED_A_PLAYER(m_vars.m_entity)) {
									timer = 0;
									m_vars.m_entity = 0;
									return;
								}
							}
						}

						timer = 0;
					}
				}
			}

			return;
		}

		timer = 0;
		m_vars.m_entity = 0;
	}
}



namespace menu {

	void gravity_gun_menu::render() {
		renderer::addSubmenu("Gravity Gun", "Weapon Gravity Gun", [](core* core) {
			core->addOption(toggleOption("Toggle Gravity Gun")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_toggle));

			core->addOption(numberOption<float>("Force")
				.addNumber(&m_vars.m_force)
				.addStep(0.1f).setPrecision(1)
				.addMin(1.f).addMax(200.f));

			core->addOption(numberOption<float>("Distance")
				.addNumber(&m_vars.m_distance)
				.addStep(1.f).setPrecision(0)
				.addMin(1.f).addMax(200.f));
		});
	}

	void gravity_gun_menu::update() {
		render();

		WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &m_vars.m_weapon_hash, false);

		m_vars.m_has_weapon_in_hand = (m_vars.m_weapon_hash && m_vars.m_weapon_hash != 2725352035);

		if (m_vars.m_toggle) {
			gravity_gun();
		}
		
	}
}