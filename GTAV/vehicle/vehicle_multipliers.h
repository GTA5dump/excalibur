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
	class vehicle_multipliers_menu {
	public:
		void render();
		void update();
	};

	static vehicle_multipliers_menu* getVehicleMultipliersMenu() {
		static vehicle_multipliers_menu instance;
		return &instance;
	}


	namespace vehicle::multipliers::vars {
		struct variables {
			float m_power = 1.f;
			float m_torque = 1.f;
			float m_headlight = 1.f;
		};

		extern variables m_vars;
	}
}