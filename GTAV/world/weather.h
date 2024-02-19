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
	class weather_menu {
	public:
		void render();
		void update();
	};

	static weather_menu* getWeatherMenu() {
		static weather_menu instance;
		return &instance;
	}

	namespace world::weather::vars {

		struct shader {
			rage::CWeatherVfx* m_drop;
			float red;
			float green;
			float blue;
			float m_luminance = 1.f;
		};

		struct variables {
			std::vector<shader> m_shaders;
			std::vector<rage::CWeatherVfx> m_originals;
			int m_scroll = 0;

			float m_drop_red;
			float m_drop_green;
			float m_drop_blue;

		};

		extern variables m_vars;
	}
}