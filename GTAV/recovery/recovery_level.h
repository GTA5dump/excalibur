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
	class recovery_level_menu {
	public:
		void render();
		void update();
	};

	static recovery_level_menu* getRecoveryLevelMenu() {
		static recovery_level_menu instance;
		return &instance;
	}

	namespace recovery::level::vars {
		struct variables {
			int m_type;
		};

		extern variables m_vars;
	}

}