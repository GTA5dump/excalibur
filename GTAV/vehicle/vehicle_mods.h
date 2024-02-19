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
	class vehicle_mods_menu {
	public:
		void render();
		void update();
	};

	static vehicle_mods_menu* getVehicleModsMenu() {
		static vehicle_mods_menu instance;
		return &instance;
	}

	enum eVehicleModTypes {
		MOD_SPOILER,
		MOD_FRONTBUMPER,
		MOD_REARBUMPER,
		MOD_SIDESKIRT,
		MOD_EXHAUST,
		MOD_CHASSIS, //Or roll cage
		MOD_GRILLE,
		MOD_HOOD,
		MOD_FENDER,
		MOD_RIGHTFENDER,
		MOD_ROOF,
		MOD_ENGINE,
		MOD_BRAKES,
		MOD_TRANSMISSION,
		MOD_HORNS,
		MOD_SUSPENSION,
		MOD_ARMOR,
		MOD_UNK17 = 17,
		MOD_TURBO = 18,
		MOD_UNK19 = 19,
		MOD_TIRESMOKE = 20,
		MOD_UNK21 = 21,
		MOD_XENONLIGHTS = 22,
		MOD_FRONTWHEELS = 23,
		MOD_BACKWHEELS = 24, //Bikes only

		// Benny's
		MOD_PLATEHOLDER = 25,
		MOD_VANITY_PLATES = 26,
		MOD_TRIM_DESIGN = 27,
		MOD_ORNAMENTS = 28,
		MOD_DASHBOARD = 29,
		MOD_DIAL = 30,
		MOD_DOOR_SPEAKER = 31,
		MOD_SEATS = 32,
		MOD_STEERINGWHEEL = 33,
		MOD_SHIFTER_LEAVERS = 34,
		MOD_PLAQUES = 35,
		MOD_SPEAKERS = 36, // might be 36
		MOD_TRUNK = 37,
		MOD_HYDRULICS = 38,
		MOD_ENGINE_BLOCK = 39,
		MOD_AIR_FILTER = 40,
		MOD_STRUTS = 41,
		MOD_ARCH_COVER = 42,
		MOD_AERIALS = 43,
		MOD_TRIM = 44,
		MOD_TANK = 45,
		MOD_WINDOWS = 46,
		MOD_UNK47 = 47,
		MOD_LIVERY = 48,

		MOD_SPECIAL_FRONT_RIMS = 62,
		MOD_SPECIAL_REAR_RIMS = 63,

		// custom
		MOD_NEON,
		MOD_HORN_STANDARD,
		MOD_HORN_MUSICAL,
		MOD_HORN_LOOP,
		MOD_WINDOWS_CUSTOM,
		MOD_PLATES
	};
	namespace vehicle::mods::vars {
		struct variables {
			bool m_instant_stop;
			bool m_instant_enter;
			bool bullet_proof;
			bool fire_proof;
			bool explosion_proof;
			bool collision_proof;
			bool melee_proof;
			bool drown_proof;
			bool m_toggle_chaff;
			bool m_toggle_flares;

			bool m_rainbow_prime;
			bool m_rainbow_second;
			bool m_scorched;
			bool m_rainbow_tyre;

			eVehicleModTypes m_mod_type;
			int32_t Spoiler{}, FBumper{}, RBumper{}, SSkirt{}, Exhaust{}, Grille{}, Chasis{}, Hood{}, Fender{}, RFender{}, Roof{}, Engine{}, Brakes{}, Transmission{}, Horns{}, Suspension{}, Armor{}, Turbo{}, TSmoke{}, Xenon{}, Wheels{}, Windows{}, Plateholder{}, Vanity{}, Trims{}, Ornaments{}, Dashboard{}, Dial{}, DoorSpeaker{}, Seats{}, SteeringWheel{}, Shifter{}, Plaques{}, Speakers{}, Trunk{}, Hydraulics{}, EngineBlock{}, Filter{}, Struts{}, Arch{}, Aerials{}, TrimTwo{}, Tank{}, Livery{};
		};

		extern variables m_vars;
	}
}