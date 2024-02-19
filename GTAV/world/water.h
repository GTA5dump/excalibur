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
	class water_menu {
	public:
		void render();
		void update();
	};

	static water_menu* getWaterMenu() {
		static water_menu instance;
		return &instance;
	}

	namespace world::water::vars {
		enum eOceanTasks {
			OCEAN_DISABLE,
			OCEAN_CLEAR,
			OCEAN_FIERCE
		};

		enum eOceanTypes {
			OCEAN_TYPE_OCEAN,
			OCEAN_TYPE_WAVE,
			OCEAN_TYPE_CALMING
		};

		struct variables {
			float m_wave_intensity;
			bool part_water;
			bool m_disable_ocean;
			bool m_clear_ocean;
			bool m_fierce_ocean;
			bool m_part_water;


		};
		void ocean_loop(eOceanTypes type, std::function<void(uint64_t)> callback);
		void ocean_task(eOceanTypes type, eOceanTasks task);
		extern variables m_vars;
	}
}