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
	class spawner_menu {
	public:
		void render();
		void update();
	};

	static spawner_menu* getSpawnerMenu() {
		static spawner_menu instance;
		return &instance;
	}

	namespace spawner::vars {
		struct variables {
			int m_selected_vehicle_class;
			std::string m_spawn_by_name = "";
		};

		extern variables m_vars;
	}
}