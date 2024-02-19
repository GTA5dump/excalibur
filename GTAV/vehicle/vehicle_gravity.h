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
	class vehicle_gravity_menu {
	public:
		void render();
		void update();
	};

	static vehicle_gravity_menu* getVehicleGravityMenu() {
		static vehicle_gravity_menu instance;
		return &instance;
	}


	namespace vehicle::gravity::vars {
		
		struct variables {
			int m_gravity = 0;
			bool m_stick_to_ground;
			bool m_auto_flip;

		};

		extern variables m_vars;
	}
}