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
	class protections_entity_menu {
	public:
		void render();
		void update();
	};

	static protections_entity_menu* getProtectionsEntityMenu() {
		static protections_entity_menu instance;
		return &instance;
	}

	namespace protections::entity::vars {
		struct variables {

			bool m_car{ false };
			bool m_bike{ false };
			bool m_boat{ false };
			bool m_door{ false };
			bool m_heli{ false };
			bool m_object{ false };
			bool m_ped{ false };
			bool m_pickup{ false };
			bool m_pickup_placement{ false };
			bool m_plane{ false };
			bool m_sub{ false };
			bool m_player{ false };
			bool m_train{ false };
			bool m_trailer{ false };

			bool m_sync_car{ false };
			bool m_sync_bike{ false };
			bool m_sync_boat{ false };
			bool m_sync_door{ false };
			bool m_sync_heli{ false };
			bool m_sync_object{ false };
			bool m_sync_ped{ false };
			bool m_sync_pickup{ false };
			bool m_sync_pickup_placement{ false };
			bool m_sync_plane{ false };
			bool m_sync_sub{ false };
			bool m_sync_player{ false };
			bool m_sync_train{ false };
			bool m_sync_trailer{ false };

			const char* entity_type[2] = {
				"Sync", "Create"
			};  std::size_t entity_type_pos = 0;

		};

		extern variables m_vars;
	}

}