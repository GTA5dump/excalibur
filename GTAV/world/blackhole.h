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
#include "gui/util/rainbow.h"
namespace menu {
	class blackhole_menu {
	public:
		void render();
		void update();
	};

	static blackhole_menu* getBlackholeMenu() {
		static blackhole_menu instance;
		return &instance;
	}

	namespace world::blackhole::vars {

		struct variables {
			bool black_hole;
			bool include_vehicles = true;
			bool include_peds = true;
			math::vector3<float> m_blackhole_pos;
			
		};

		extern variables m_vars;
	}
}