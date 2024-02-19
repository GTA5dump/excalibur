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
	class spawner_settings_menu {
	public:
		void render();
		void update();
	};

	static spawner_settings_menu* getSpawnerSettingsMenu() {
		static spawner_settings_menu instance;
		return &instance;
	}

	namespace spawner::settings::vars {

		struct variables {
			bool m_notification = true;
			bool m_blip;
			bool m_particle_fx;
			bool m_teleport_inside = true;
			bool m_godmode = true;
			bool m_fade;
			bool m_delete_current = true;
			bool m_air_vehicles_in_air = true;
			bool m_upgrades;
			bool m_session_gift;

			int m_upgrades_var;
			float m_spawn_height = 100.f;
		};

		extern variables m_vars;
	}
}