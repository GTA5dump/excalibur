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
	class vehicle_collision_menu {
	public:
		void render();
		void update();
	};

	static vehicle_collision_menu* getVehicleCollisionMenu() {
		static vehicle_collision_menu instance;
		return &instance;
	}


	namespace vehicle::collision::vars {
		struct variables {
			bool m_disable_full_collision;
			bool m_disable_vehicle_collision;
		};

		extern variables m_vars;
	}
}