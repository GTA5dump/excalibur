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
	class position_menu {
	public:
		void render();
		void update();
	};

	static position_menu* getPositionMenu() {
		static position_menu instance;
		return &instance;	
	}
}