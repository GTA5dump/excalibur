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
	class vehicle_ramps_menu {
	public:
		void render();
		void update();
	};

	static vehicle_ramps_menu* getVehicleRampsMenu() {
		static vehicle_ramps_menu instance;
		return &instance;
	}


	namespace vehicle::ramps::vars {

		struct variables {
			bool m_transparency;
			bool m_front_ramp;
			bool m_rear_ramp;
			bool m_left_ramp;
			bool m_right_ramp;

			int m_ramp_type = 1;
		};

		extern variables m_vars;
	}
}