#include "pch.h"
#include "weapon_tracers.h"
#include "menu/util/globals.h"
#include "gui/options/option.h"
#include "gui/util/panels.h"
#include "rage/classes/CPed.h"
#include "rage/classes/CPlayerInfo.h"
#include "menu/util/control.h"
#include "menu/util/raycast.h"

#include "paint_gun.h"
#include "aimbot.h"
using namespace base::gui;
using namespace menu::weapon::tracers::vars;

namespace menu::weapon::tracers::vars {
	variables m_vars;

	float deg_to_rad(float deg) {
		double radian = (3.14159265359 / 180) * deg;
		return (float)radian;
	}

	Vector3 rotation_to_direction(Vector3 rotation) {
		float x = deg_to_rad(rotation.x);
		float z = deg_to_rad(rotation.z);

		float num = abs(cos(x));

		return Vector3 {
			-sin(z) * num,
			cos(z) * num,
			sin(x)
		};
	}

	Vector3 addVector(Vector3 vector, Vector3 vector2) {
		vector.x += vector2.x;
		vector.y += vector2.y;
		vector.z += vector2.z;
		vector.x += vector2.x;
		vector.y += vector2.y;
		vector.z += vector2.z;
		return vector;
	}

	Vector3 multiplyVector(Vector3 vector, float inc) {
		vector.x *= inc;
		vector.y *= inc;
		vector.z *= inc;
		vector.x *= inc;
		vector.y *= inc;
		vector.z *= inc;
		return vector;
	}

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
}



namespace menu {

	void weapon_tracers_menu::render() {
		renderer::addSubmenu("Tracers", "Weapon Tracers", [](core* core) {
			core->addOption(toggleOption("Toggle Tracers")
				.addToggle(&m_vars.m_toggle));

			core->addOption(numberOption<int>("Duration")
				.addNumber(&m_vars.m_duration)
				.addMin(0).addMax(10000));
		});
	}

	void weapon_tracers_menu::update() {
		render();

		WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &m_vars.m_weapon_hash, false);

		m_vars.m_has_weapon_in_hand = (m_vars.m_weapon_hash && m_vars.m_weapon_hash != 2725352035);

		if (m_vars.m_toggle) {
			if (isPedShooting(PLAYER::PLAYER_PED_ID())) {
				auto start = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(PLAYER::PLAYER_PED_ID(), PED::GET_PED_BONE_INDEX(PLAYER::PLAYER_PED_ID(), 0x6F06));
				auto dir = rotation_to_direction(CAM::GET_GAMEPLAY_CAM_ROT(0));
				auto end = addVector(CAM::GET_FINAL_RENDERED_CAM_COORD(), (multiplyVector(dir, 50.f)));
				color Color = { 255, 0, 0 };
				bulletTracers.push_back({ start, end, Color, GetTickCount() });
			}
			for (const auto& Tracer : bulletTracers) {
				if (GetTickCount() - Tracer.m_Time < m_vars.m_duration) {
					GRAPHICS::DRAW_LINE(Tracer.m_Start, Tracer.m_End, Tracer.m_Color.r, Tracer.m_Color.g, Tracer.m_Color.b, 255);
				}
				if (GetTickCount() - Tracer.m_Time > m_vars.m_duration) {
					bulletTracers.erase(bulletTracers.begin());
				}
			}
		}
		
	}
}