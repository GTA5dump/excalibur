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
#include "gui/options/color.h"

#include "gui/util/rainbow.h"
namespace menu {
	class vehicle_tyre_tracks_menu {
	public:
		void render();
		void update();
	};

	static vehicle_tyre_tracks_menu* getVehicleTyreTracksMenu() {
		static vehicle_tyre_tracks_menu instance;
		return &instance;
	}


	namespace vehicle::tyre_tracks::vars {

		struct variables {
			bool m_toggle;
			CWheelVfx* m_cache;
			color m_color = color(255, 0, 0, 255);
			bool m_randomize;
			menu::rainbow m_rainbow;

			uint8_t m_tyre_r;
			uint8_t m_tyre_g;
			uint8_t m_tyre_b;
			uint8_t m_tyre_a = 255;
		};

		extern variables m_vars;
	}
}