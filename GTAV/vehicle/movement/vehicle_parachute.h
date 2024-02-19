#pragma once
#include "gui/options/core.h"
#include "gui/options/submenu.h"
#include "gui/options/option.h"
#include "gui/options/button.h"
#include "gui/options/submenu_option.h"
#include "gui/options/number.h"
#include "gui/options/toggle.h"
#include "gui/options/scroll.h"

namespace menu {
	class vehicle_parachute_menu {
	public:
		void render();
		void update();
	};

	static vehicle_parachute_menu* getVehicleParachuteMenu() {
		static vehicle_parachute_menu instance;
		return &instance;
	}

	enum class VehicleAbility
	{
		NONE,
		BOOST,                       //64
		JUMP,                        // 32
		PARACHUTE,                   //256
		RAMPBUGGY,                   //512
		BOOSTPARACHUTE,              //320
		JUMPPARACHUTE,               //288
		BOOSTJUMP,                   //96
		BOOSTJUMPPARACHUTE,          // 352
		BOOSTPARACHUTERAMPBUGGY,     //832
		BOOSTJUMPRRAMPBUGGYPARACHUTE, //864
		CUSTOM
	};
	namespace vehicle::parachute::vars {
		struct variables {
			bool m_auto_deploy;
			VehicleAbility ability_chosen = VehicleAbility::NONE;
			bool ability_toggle = false;
			uint16_t customvalue = 0;
			bool boost = false;
			bool parachute = false;

		};

		extern variables m_vars;
	}
}