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

namespace menu {
	class color_menu {
	public:
		void render();
		void update();
	};

	static color_menu* getColorMenu() {
		static color_menu instance;
		return &instance;
	}
}