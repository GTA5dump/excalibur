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
	class teleport_menu {
	public:
		void render();
		void update();
	};

	static teleport_menu* getTeleportMenu() {
		static teleport_menu instance;
		return &instance;
	}


	namespace teleport::vars {
		struct variables {
			bool m_transition = false;
			bool m_auto_waypoint;
			bool m_include_current_vehicle = true;
			bool m_has_teleported_flag;

			uint32_t m_waypoint_timer;
		};

		void teleportToCoords(Vector3 coords, bool only_player = false, std::function<void(Vector3)> callback = [](Vector3) {}, bool no_tp = false);
		extern variables m_vars;
	}
}