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
	class player_menu {
	public:
		void render();
		void update();
	};

	static player_menu* getPlayerMenu() {
		static player_menu instance;
		return &instance;
	}


	namespace player::vars {
		struct variables {
			bool m_godmode;
			bool m_disable_police;
			bool m_cops_turn_blind_eye;
			bool m_off_the_radar;
			bool m_reveal_hidden_players;

			bool m_auto_heal;
			bool m_fast_respawn;
			bool m_disable_ragdoll;

			bool m_reduced_collision;
			bool m_no_collision;

			bool m_invisible;
			bool m_superman;
			bool m_karma;

			bool m_forcefield;
			bool m_shrink;
			bool m_vegetable_mode;
		};

		extern variables m_vars;
	}
}