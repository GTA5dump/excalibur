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
	class vehicle_movement_menu {
	public:
		void render();
		void update();
	};

	static vehicle_movement_menu* getVehicleMovementMenu() {
		static vehicle_movement_menu instance;
		return &instance;
	}


	namespace vehicle::movement::vars {
		struct variables {
			bool m_flying_vehicle;
			bool m_flying_vehicle_pause;
			bool m_flying_vehicle_mouse = true;
			bool m_disable_max_speed;

			float m_flying_vehicle_speed = 10.f;
		};

		extern variables m_vars;
	}
}