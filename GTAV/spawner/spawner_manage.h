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
	class spawner_manage_menu {
	public:
		void render();
		void update();
	};

	static spawner_manage_menu* getSpawnerManageMenu() {
		static spawner_manage_menu instance;
		return &instance;
	}

	namespace spawner::manage::vars {
		struct spawned_vehicle {
			Vehicle m_handle = 0;
			uint32_t m_model_hash = 0;
			int m_creation_time = 0;
		};
		struct variables {
			std::vector<spawned_vehicle> m_vehicles;
		};

		extern variables m_vars;
	}
}