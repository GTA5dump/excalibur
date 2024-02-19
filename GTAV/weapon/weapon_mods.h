#pragma once
#include "gui/options/core.h"
#include "gui/options/submenu.h"
#include "gui/options/option.h"
#include "gui/options/button.h"
#include "gui/options/submenu_option.h"
#include "gui/options/number.h"
#include "gui/options/toggle.h"
#include "gui/options/scroll.h"

namespace menu {
	class weapon_mods_menu {
	public:
		void render();
		void update();
	};

	static weapon_mods_menu* getWeaponModsMenu() {
		static weapon_mods_menu instance;
		return &instance;
	}


	namespace weapon::mods::vars {
		struct variables {
			bool m_unlimited_ammo;
			bool m_instant_kill;
			bool m_rapid_fire;
			bool m_explosive_bullets;
			bool m_incendiary_bullets;
			bool m_teleport;
			bool m_airstrike;
			bool m_delete_entity;
			bool m_shrink_entity;
			bool m_apply_force;
			bool m_dead_eye;
			bool m_vehicle_hijack;
			bool m_clown_vfx;
			bool m_laser_sight;
			bool m_defibrillator;
			bool m_spawn_money;
			bool m_toggle_crosshair;
			bool m_triggerbot;
		};

		extern variables m_vars;
	}
}