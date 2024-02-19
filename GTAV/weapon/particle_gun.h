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
	class particle_gun_menu {
	public:
		void render();
		void update();
	};

	static particle_gun_menu* getParticleGunMenu() {
		static particle_gun_menu instance;
		return &instance;
	}


	namespace weapon::particle_gun::vars {
		struct particle_context {
			std::unordered_map<int, bool> m_toggles;
			int m_selected = 0; // Updated to store the selected particle index
			int m_count = 0;
			std::pair<const char*, const char*> m_sprite = { "", "" };

			particle_context(const char* dict, const char* texture) {
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
			float m_scale = 1.f;

			particle_context m_context = { "textures", "toggle_on" };

			uint32_t m_weapon_hash = 0;
			bool m_has_weapon_in_hand;
		};

		extern variables m_vars;
	}
}