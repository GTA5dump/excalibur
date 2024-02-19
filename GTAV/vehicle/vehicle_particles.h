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
	class vehicle_particles_menu {
	public:
		void render();
		void update();
	};

	static vehicle_particles_menu* getVehicleParticlesMenu() {
		static vehicle_particles_menu instance;
		return &instance;
	}


	namespace vehicle::particles::vars {
		struct variables {
			bool m_toggle;
			float m_scale = 0.2f;
			bool m_bones[10];

		};

		extern variables m_vars;
	}
}