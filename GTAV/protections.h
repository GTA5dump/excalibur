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
	class protections_menu {
	public:
		void render();
		void update();
	};

	static protections_menu* getProtectionsMenu() {
		static protections_menu instance;
		return &instance;
	}

	namespace protections::vars {
		struct variables {
			bool m_fake_lag;
			bool m_force_entities_visible;
			bool m_block_all_script_events;
		};

		extern variables m_vars;
	}

}