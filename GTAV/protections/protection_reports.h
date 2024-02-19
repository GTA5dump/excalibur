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
	class protections_reports_menu {
	public:
		void render();
		void update();
	};

	static protections_reports_menu* getProtectionsReportsMenu() {
		static protections_reports_menu instance;
		return &instance;
	}

	namespace protections::reports::vars {
		struct variables {
			const char* block_reports[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_reports_id = 2;
			const char* block_arxan_reports[3] = { "Nothing", "Block", "Block & Notify" }; std::size_t block_arxan_reports_id = 2;
		};

		extern variables m_vars;
	}

}