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
	class protections_presence_menu {
	public:
		void render();
		void update();
	};

	static protections_presence_menu* getProtectionsPresenceMenu() {
		static protections_presence_menu instance;
		return &instance;
	}

	namespace protections::presence::vars {
		struct variables {
			const char* text_message[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t text_message_id = 0;
			const char* crew_message[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t crew_message_id = 0;
			const char* game_invite[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t game_invite_id = 0;
			const char* game_award[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t game_award_id = 0;
			const char* admin_invite[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t admin_invite_id = 0;
			const char* stat_update[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t stat_update_id = 0;
			const char* bounty[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t bounty_id = 0;
			const char* voice_invite[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t voice_invite_id = 0;
			const char* rockstar_message[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t rockstar_message_id = 0;
		};

		extern variables m_vars;
	}

}