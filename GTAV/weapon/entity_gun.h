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
	class entity_gun_menu {
	public:
		void render();
		void update();
	};

	static entity_gun_menu* getEntityGunMenu() {
		static entity_gun_menu instance;
		return &instance;
	}


	namespace weapon::entity_gun::vars {
		struct variables {
			int m_type = 0;
			int m_wait = 0;
			int m_object = 0;
			int m_vehicle = 0;
			int m_ped = 0;
			float m_speed = 900.f;

			bool m_toggle = false;

			uint32_t m_weapon_hash = 0;
			bool m_has_weapon_in_hand;
		};

		extern variables m_vars;
	}
}