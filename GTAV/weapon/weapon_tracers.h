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
#include "gui/options/color.h"

#include "rage/classes/CWeaponInfo.h"
namespace menu {
	class weapon_tracers_menu {
	public:
		void render();
		void update();
	};

	static weapon_tracers_menu* getWeaponTracersMenu() {
		static weapon_tracers_menu instance;
		return &instance;
	}


	namespace weapon::tracers::vars {
		struct Tracer
		{
			Vector3 m_Start{};
			Vector3 m_End{};
			color m_Color{};
			DWORD m_Time{};
		};

		struct variables {
			uint32_t m_weapon_hash = 0;
			bool m_has_weapon_in_hand;
			bool m_toggle;
			int m_duration = 3000;
		};
		inline std::vector<Tracer> bulletTracers;

		extern variables m_vars;
	}
}