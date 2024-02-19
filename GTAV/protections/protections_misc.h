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
	class protections_misc_menu {
	public:
		void render();
		void update();
	};

	static protections_misc_menu* getProtectionsMiscMenu() {
		static protections_misc_menu instance;
		return &instance;
	}

	namespace protections::misc::vars {
		struct variables {
			const char* script_host_kicks[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t script_host_kicks_id = 2;
			const char* script_host_migration[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t script_host_migration_id = 2;
			const char* pickup_processing[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t pickup_processing_id = 0;
			const char* cloning[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t cloning_id = 2;
			const char* cages[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t cages_id = 2;
			const char* attachments[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t attachments_id = 2;
			const char* join_timeout[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t join_timeout_id = 2;
			const char* ghost[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t ghost_id = 2;

			const char* spoofed_text_messages[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t spoofed_text_messages_id = 2;
			const char* spoofed_chat_messages[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t spoofed_chat_messages_id = 2;


			bool m_disable_bullets;
			bool m_disable_projectiles;

		};

		extern variables m_vars;
	}

}