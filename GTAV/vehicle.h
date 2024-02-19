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
	class vehicle_menu {
	public:
		void render();
		void update();
	};

	static vehicle_menu* getVehicleMenu() {
		static vehicle_menu instance;
		return &instance;
	}


	namespace vehicle::vars {
		struct variables {
			bool m_godmode;
			bool m_invisibility;
			bool m_seatbelt;
		};

		void run_task(Vehicle veh, std::function<void(Vehicle)> callback);

		extern variables m_vars;
	}
}