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
#include "gui/util/rainbow.h"
namespace menu {
	class world_glow_menu {
	public:
		void render();
		void update();
	};

	static world_glow_menu* getWorldGlowMenu() {
		static world_glow_menu instance;
		return &instance;
	}

	namespace world::glow::vars {

		struct variables {
			bool world_glow;
			bool world_rainbow;
			float world_intensity = 25.f;
			int worldr = 255;
			int worldg;
			int worldb;
		};

		extern variables m_vars;
	}
}