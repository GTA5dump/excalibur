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
	class weapon_disables_menu {
	public:
		void render();
		void update();
	};

	static weapon_disables_menu* getWeaponDisablesMenu() {
		static weapon_disables_menu instance;
		return &instance;
	}


	namespace weapon::disables::vars {
		struct variables {
			bool m_vehicle_block;
			bool m_passive_block;
			bool m_interior_block;
			bool m_spread;
			bool m_recoil;
			bool m_recharge;
			bool m_spin_delay;
			bool m_reload_animation;


			std::unordered_map<CWeaponInfo*, float> m_original_anim_reload_rate;
			std::unordered_map<CWeaponInfo*, std::pair<float, float>> m_original_spread;
			std::unordered_map<CWeaponInfo*, std::pair<float, float>> m_original_recoil;
			std::unordered_map<CWeaponInfo*, float> m_original_time_between_shots;
			std::unordered_map<CWeaponInfo*, std::pair<float, float>> m_original_instant_spin;
			
			bool m_has_weapon_in_hand;
		};

		extern variables m_vars;
	}
}