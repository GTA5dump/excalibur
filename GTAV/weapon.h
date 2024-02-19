#pragma once
#include "gui/options/core.h"
#include "gui/options/option.h"
#include "gui/options/button.h"
#include "gui/options/submenu_option.h"
#include "gui/options/number.h"
#include "gui/options/toggle.h"
#include "gui/options/scroll.h"
#include "gui/options/color.h"
#include "gui/options/break.h"

namespace menu {
	class weapon_menu {
	public:
		void render();
		void update();
	};

	static weapon_menu* getWeaponMenu() {
		static weapon_menu instance;
		return &instance;
	}
}