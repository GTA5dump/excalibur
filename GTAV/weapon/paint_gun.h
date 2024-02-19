#pragma once
#include "gui/options/core.h"
#include "gui/options/submenu.h"
#include "gui/options/option.h"
#include "gui/options/button.h"
#include "gui/options/submenu_option.h"
#include "gui/options/number.h"
#include "gui/options/toggle.h"
#include "gui/options/scroll.h"
#include "gui/options/color.h"
#include "gui/options/break.h"

namespace menu {
	class paint_gun_menu {
	public:
		void render();
		void update();
	};

	static paint_gun_menu* getPaintGunMenu() {
		static paint_gun_menu instance;
		return &instance;
	}


	namespace weapon::paint_gun::vars {
		struct variables {
			bool m_toggle;
			color m_color = color(255, 255, 255, 255);
			float m_range = 0.25;
			float m_intensity = 100;
		};

		extern variables m_vars;
	}
}