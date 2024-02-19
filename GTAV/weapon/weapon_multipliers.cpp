#include "pch.h"
#include "weapon_multipliers.h"
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
using namespace menu::weapon::multipliers::vars;

namespace menu::weapon::multipliers::vars {
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
}



namespace menu {

	void weapon_multipliers_menu::render() {
		renderer::addSubmenu("Multipliers", "Weapon Multipliers", [](core* core) {
			core->addOption(toggleNumberOption<float>("Bullet Damage")
				.addToggle(&m_vars.m_weapon_damage_multiplier)
				.addNumber(&m_vars.m_weapon_damage_multiplier_val).addMin(1.f).addMax(1000.f).setPrecision(0)
				.addClick([] { if (m_vars.m_weapon_hash) PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_ID(), 1.f); }));

			core->addOption(toggleNumberOption<float>("Melee Damage")
				.addToggle(&m_vars.m_melee_damage_multiplier)
				.addNumber(&m_vars.m_melee_damage_multiplier_val).addMin(1.f).addMax(1000.f).setPrecision(0)
				.addClick([] { if (m_vars.m_weapon_hash) PLAYER::SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_ID(), 1.f, 1); }));

			core->addOption(toggleNumberOption<float>("Defense Damage")
				.addToggle(&m_vars.m_defense_damage_multiplier)
				.addNumber(&m_vars.m_defense_damage_multiplier_val).addMin(1.f).addMax(1000.f).setPrecision(0)
				.addClick([] { if (m_vars.m_weapon_hash) PLAYER::SET_PLAYER_WEAPON_DEFENSE_MODIFIER(PLAYER::PLAYER_ID(), 1.f); }));
		});
	}

	void weapon_multipliers_menu::update() {
		render();

		WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &m_vars.m_weapon_hash, false);

		m_vars.m_has_weapon_in_hand = (m_vars.m_weapon_hash && m_vars.m_weapon_hash != 2725352035);

		
		if (m_vars.m_has_weapon_in_hand) {
			if (m_vars.m_weapon_damage_multiplier) {
				PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_ID(), m_vars.m_weapon_damage_multiplier_val);
			}

			if (m_vars.m_melee_damage_multiplier) {
				PLAYER::SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_ID(), m_vars.m_melee_damage_multiplier_val, 1);
			}

			if (m_vars.m_defense_damage_multiplier) {
				PLAYER::SET_PLAYER_WEAPON_DEFENSE_MODIFIER(PLAYER::PLAYER_ID(), m_vars.m_defense_damage_multiplier_val);
			}
		}
	}
}