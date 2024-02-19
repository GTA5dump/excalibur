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
	class entities_menu {
	public:
		void render();
		void update();
	};

	static entities_menu* getEntitiesMenu() {
		static entities_menu instance;
		return &instance;
	}

	namespace world::entities::vars {

		struct variables {
			

		};

		extern variables m_vars;
	}
}