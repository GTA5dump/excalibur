#pragma once
#include "gui/options/core.h"
#include "gui/options/submenu.h"
#include "gui/options/option.h"
#include "gui/options/button.h"
#include "gui/options/submenu_option.h"
#include "gui/options/number.h"
#include "gui/options/toggle.h"
#include "gui/options/scroll.h"
#include "gui/options/break.h"

#include "rage/classes/CWeaponInfo.h"
namespace menu {
	class gravity_gun_menu {
	public:
		void render();
		void update();
	};

	static gravity_gun_menu* getGravityGunMenu() {
		static gravity_gun_menu instance;
		return &instance;
	}


	namespace weapon::gravity_gun::vars {
		struct variables {
			bool m_toggle;
			bool m_attraction;
			bool m_peds;
			bool m_vehicles;
			bool m_objects;

			float m_attraction_distance = 10.f;
			float m_force = 10.f;
			float m_distance = 10.f;

			Entity m_entity;

			uint32_t m_weapon_hash = 0;
			bool m_has_weapon_in_hand;
		};

		extern variables m_vars;
	}
}