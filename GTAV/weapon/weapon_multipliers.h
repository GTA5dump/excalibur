#pragma once
#include "gui/options/core.h"
#include "gui/options/submenu.h"
#include "gui/options/option.h"
#include "gui/options/button.h"
#include "gui/options/submenu_option.h"
#include "gui/options/number.h"
#include "gui/options/toggle.h"
#include "gui/options/scroll.h"


#include "rage/classes/CWeaponInfo.h"
namespace menu {
	class weapon_multipliers_menu {
	public:
		void render();
		void update();
	};

	static weapon_multipliers_menu* getWeaponMultipliersMenu() {
		static weapon_multipliers_menu instance;
		return &instance;
	}


	namespace weapon::multipliers::vars {
		struct variables {
			bool m_weapon_damage_multiplier;
			bool m_melee_damage_multiplier;
			bool m_defense_damage_multiplier;

			float m_weapon_damage_multiplier_val = 1.f;
			float m_melee_damage_multiplier_val = 1.f;
			float m_defense_damage_multiplier_val = 1.f;

			uint32_t m_weapon_hash = 0;
			bool m_has_weapon_in_hand;
		};

		extern variables m_vars;
	}
}