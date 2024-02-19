#pragma once
#include "gui/options/core.h"
#include "gui/options/submenu.h"
#include "gui/options/option.h"
#include "gui/options/button.h"
#include "gui/options/submenu_option.h"
#include "gui/options/number.h"
#include "gui/options/toggle.h"
#include "gui/options/scroll.h"
#include "gui/options/color.h"
#include "gui/options/break.h"

namespace menu {
	class aimbot_menu {
	public:
		void render();
		void update();
	};

	static aimbot_menu* getAimBotMenu() {
		static aimbot_menu instance;
		return &instance;
	}


	namespace weapon::aimbot::vars {
		struct variables {
			bool m_toggle;
			bool m_smoothing;
			float m_smooth_speed = 2.f;
			bool on_player = true;
			bool on_ped = true;
			bool on_enemy = true;
			bool on_police = true;
			float fov = 120.f;
			float distance = 200.f;
			uint32_t selected_bone = 0x796E;
			
			int shoot_delay = 20;
		};

		extern variables m_vars;
	}
}