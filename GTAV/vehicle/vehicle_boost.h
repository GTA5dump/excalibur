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
	class vehicle_boost_menu {
	public:
		void render();
		void update();
	};

	static vehicle_boost_menu* getVehicleBoostMenu() {
		static vehicle_boost_menu instance;
		return &instance;
	}


	namespace vehicle::boost::vars {
		struct variables {
			bool m_boost_fx;
			bool m_boost_sound;
			bool m_toggle_horn;
			bool m_unlimited_special_ability;

			int m_boost_forwards = 0;
			int m_boost_backwards = 0;
		};

		extern variables m_vars;
	}
}