#include "pch.h"
#include "explosions.h"
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
using namespace menu::weapon::explosions::vars;

namespace menu::weapon::explosions::vars {
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

	const char* explosion_gun_type[] = {
	"Grenade", "Grenade Launcher", "Sticky Bomb", "Molotov", "Tank Shell", "Octane", "Car", "Plane", "Petrol Pump", "Bike",
	"Steam", "Flame", "Water", "Gas", "Boat", "Ship", "Truck", "Bullet", "Smoke Launcher", "Smoke Grenade", "BZ Gas", "Flae",
	"Gas Can", "Extinguisher", "Programmable Ar", "Train", "Barrel", "Propane", "Blimp", "Flame Explosion", "Tanker", "Rocket",
	"Vehicle Bullet", "Gas Tank", "Bird Crap", "Snow Ball"
	};

	int explosion_gun_ids[39] = {
	   1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39
	}; int explosion_gun_id = 0;
}



namespace menu {

	void weapon_explosions_menu::render() {
		renderer::addSubmenu("Explosion Gun", "Weapon Explosions", [](core* core) {
			core->addOption(toggleOption("Toggle Explosion Gun")
				.addToggle(&m_vars.m_toggle));


			core->addOption(scrollOption<const char*, int>("Explosion")
				.addScroll(&explosion_gun_type).setPosition(&explosion_gun_id));

			core->addOption(toggleOption("Audible")
				.addToggle(&m_vars.m_audible));

			core->addOption(toggleOption("Invisible")
				.addToggle(&m_vars.m_invisible));


			core->addOption(numberOption<int>("Radus")
				.addNumber(&m_vars.m_radius).addMin(0).addMax(500)
				.addStep(1));

			core->addOption(numberOption<float>("Camera Shake")
				.addNumber(&m_vars.m_camera_shake).addMin(0).addMax(100)
				.addStep(1).setPrecision(0));
		});
	}

	void weapon_explosions_menu::update() {
		render();

		WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &m_vars.m_weapon_hash, false);
		m_vars.m_has_weapon_in_hand = (m_vars.m_weapon_hash && m_vars.m_weapon_hash != 2725352035);

		if (m_vars.m_toggle) {
			if (isPedShooting(PLAYER::PLAYER_PED_ID())) {
				auto c = raycast::m_ShapeTestDestination;
				if (!raycast::IsEmpty(c))
					FIRE::ADD_EXPLOSION(c, explosion_gun_ids[explosion_gun_id], 1000, m_vars.m_audible, m_vars.m_invisible, m_vars.m_camera_shake, false);

			}

		}

	}
}