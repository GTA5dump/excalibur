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
	class time_menu {
	public:
		void render();
		void update();
	};

	static time_menu* getTimeMenu() {
		static time_menu instance;
		return &instance;
	}

	namespace world::time::vars {

		struct variables {
			bool sync_time;
			bool freeze_time;
			bool always_day;
			bool always_night;

		};

		extern variables m_vars;
	}
}