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
	class player_movement_menu {
	public:
		void render();
		void update();
	};

	static player_movement_menu* getPlayerMovementMenu() {
		static player_movement_menu instance;
		return &instance;
	}


	namespace player::movement::vars {
		struct variables {
			bool m_run_speed; float m_run_multiplier = 1.f;
			bool m_swim_speed; float m_swim_multiplier = 1.f;

			bool m_slide_run;
			bool m_beast_jump;
			bool m_super_jump;
			bool m_graceful_landing;
			bool m_swim_in_air;
			bool m_no_clip;
			float m_no_clip_speed = 1.f;
			bool m_walk_on_air;
			bool m_freeze;
			
		};

		extern variables m_vars;
	}
}