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
	class player_appearance_menu {
	public:
		void render();
		void update();
	};

	static player_appearance_menu* getPlayerAppearanceMenu() {
		static player_appearance_menu instance;
		return &instance;
	}


	namespace player::appearance::vars {
		struct variables {
			int m_clothing;
			int m_clothing_model;
			int m_clothing_variation;
			int m_accessory;
			int m_accessory_model;
			int m_accessory_variation;
			int m_accessory_clear;
		};

		extern variables m_vars;
	}
}