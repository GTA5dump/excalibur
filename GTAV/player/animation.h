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
	class player_animation_menu {
	public:
		void render();
		void update();
	};

	static player_animation_menu* getPlayerAnimationMenu() {
		static player_animation_menu instance;
		return &instance;
	}


	namespace player::animation::vars {
		struct variables {
			bool m_controllable;
		};

		extern variables m_vars;
	}
}