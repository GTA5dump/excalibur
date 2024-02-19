#pragma once
#include "gui/options/core.h"
#include "gui/options/submenu.h"
#include "gui/options/option.h"
#include "gui/options/button.h"
#include "gui/options/submenu_option.h"
#include "gui/options/number.h"
#include "gui/options/toggle.h"
#include "gui/options/scroll.h"

#include "rage/classes/vfx.h"
namespace menu {
	class vehicle_modifiers_menu {
	public:
		void render();
		void update();
	};

	static vehicle_modifiers_menu* getVehicleModifiersMenu() {
		static vehicle_modifiers_menu instance;
		return &instance;
	}


	namespace vehicle::modifiers::vars {
		struct variables {
			bool m_toggle;
			float m_height = 0.7f;
			float m_width = 0.7f;
			float m_scale = 1.f;
		};

		extern variables m_vars;
	}
}