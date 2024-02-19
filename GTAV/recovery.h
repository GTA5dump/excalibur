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
	class recovery_menu {
	public:
		void render();
		void update();
	};

	static recovery_menu* getRecoveryMenu() {
		static recovery_menu instance;
		return &instance;
	}

	namespace recovery::vars {
		struct variables {
			bool m_loop;
			int m_selected_character;

			int m_kills;
			int m_deaths;
			float m_calculated;

			bool m_loop2;
		};

		extern variables m_vars;
	}

}