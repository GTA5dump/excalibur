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
	class protections_detection_menu {
	public:
		void render();
		void update();
	};

	static protections_detection_menu* getProtectionsDetectionMenu() {
		static protections_detection_menu instance;
		return &instance;
	}

	namespace protections::detection::vars {
		struct variables {
			bool m_godmode = true;
			bool m_superjump = true;
			bool m_spectate = true;
			bool m_frame_flags = true;
			bool m_health = true;
			bool m_armor = true;

		};

		extern variables m_vars;
	}

}