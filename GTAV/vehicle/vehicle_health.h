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
	class vehicle_health_menu {
	public:
		void render();
		void update();
	};

	static vehicle_health_menu* getVehicleHealthMenu() {
		static vehicle_health_menu instance;
		return &instance;
	}


	namespace vehicle::health::vars {
		struct variables {
			bool m_auto_repair;
			bool m_auto_wash;
		};

		extern variables m_vars;
	}
}