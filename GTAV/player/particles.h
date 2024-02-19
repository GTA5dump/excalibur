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
	class player_particles_menu {
	public:
		void render();
		void update();
	};

	static player_particles_menu* getPlayerParticlesMenu() {
		static player_particles_menu instance;
		return &instance;
	}


	namespace player::particles::vars {
		struct variables {

			float m_scale = 0.2f;
			std::map<std::string, bool> m_particleToggles; 

		};

		extern variables m_vars;
	}
}