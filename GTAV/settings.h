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
	class settings_menu {
	public:
		void render();
		void update();
	};

	static settings_menu* getSettingsMenu() {
		static settings_menu instance;
		return &instance;
	}

	namespace settings::vars {
		struct variables {
			std::size_t m_selected_theme;
			bool m_auto_save;
			const char* theme_to_save = "";
		};


		extern variables m_vars;
	}
}