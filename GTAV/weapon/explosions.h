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
	class weapon_explosions_menu {
	public:
		void render();
		void update();
	};

	static weapon_explosions_menu* getWeaponExplosionsMenu() {
		static weapon_explosions_menu instance;
		return &instance;
	}


	namespace weapon::explosions::vars {
		struct variables {

			uint32_t m_weapon_hash = 0;
			bool m_has_weapon_in_hand;

			bool m_toggle;
			bool m_audible = true;
			int m_radius = 25;
			float m_camera_shake = 0.f;
			bool m_invisible = false;
		};

		extern variables m_vars;
	}
}