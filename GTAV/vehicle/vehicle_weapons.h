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

namespace menu {
	class vehicle_weapons_menu {
	public:
		void render();
		void update();
	};

	static vehicle_weapons_menu* getVehicleWeaponsMenu() {
		static vehicle_weapons_menu instance;
		return &instance;
	}


	namespace vehicle::weapons::vars {
		struct weapon_context {
			std::unordered_map<int, bool> m_toggles;
			int m_selected = 0; // Updated to store the selected particle index
			int m_count = 0;
			std::pair<const char*, const char*> m_sprite = { "", "" };

			weapon_context(const char* dict, const char* texture) {
				m_sprite = std::make_pair(dict, texture);
				m_selected = 0;
				m_count = 0;
			}

			void reset() {
				m_count = 0;

				for (auto& it : m_toggles) {
					it.second = false;
				}
			}
		};
		struct variables {
			bool m_toggle;
			bool m_aiming_lines;
			float m_bullet_spped = 2000;
			weapon_context m_context = { "textures", "toggle_on" };
		
		};

		extern variables m_vars;
	}
}