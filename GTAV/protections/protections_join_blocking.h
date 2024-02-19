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
	class protections_join_blocking_menu {
	public:
		void render();
		void update();
	};

	static protections_join_blocking_menu* getProtectionsJoinBlockingMenu() {
		static protections_join_blocking_menu instance;
		return &instance;
	}

	namespace protections::join_blocking::vars {
		struct variables {
			bool m_block;
			bool m_spoof;

		};

		extern variables m_vars;
	}

}