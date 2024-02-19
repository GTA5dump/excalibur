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
	class protections_syncs_menu {
	public:
		void render();
		void update();
	};

	static protections_syncs_menu* getProtectionsSyncsMenu() {
		static protections_syncs_menu instance;
		return &instance;
	}

	namespace protections::syncs::vars {
		struct variables {
			bool block_outgoing_syncs;
			bool block_incoming_syncs;
		};

		extern variables m_vars;
	}

}