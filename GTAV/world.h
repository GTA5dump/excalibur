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
	class world_menu {
	public:
		void render();
		void update();
	};

	static world_menu* getWorldMenu() {
		static world_menu instance;
		return &instance;
	}

	namespace world::vars {

		struct sky_color {
			bool m_rainbow_toggle;
			float m_luminance = 1.f;
			color m_internal_color;
			math::vector3_<float> m_color;
			math::vector4<float>* m_memory_color;
			math::vector4<float> m_memory_color_cache;
			menu::rainbow m_rainbow;
			std::vector<uint8_t> m_cache;
		};

		struct variables {

			sky_color m_azimuth_east_color;
			sky_color m_azimuth_west_color;
			sky_color m_azimuth_transition_color;
			sky_color m_cloud_base_minus_mid_colour;
			sky_color m_cloud_mid_color;
			sky_color m_cloud_shadow_minus_base_colour_times_shadow_strength;
			sky_color m_moon_color;
			sky_color m_sky_plane_color;
			sky_color m_sun_color;
			sky_color m_zenith_color;
			sky_color m_zenith_transition_color;

			int m_selected;
			bool m_cached;

			bool world_glow;
			bool world_rainbow;
			float world_intensity = 25.f;
			int worldr = 255;
			int worldg;
			int worldb;
			bool sync_time;
			bool freeze_time;
			bool always_day;
			bool always_night;
			bool decrease_graphics;
			bool dominos;
		
			bool drive_train;
			bool render_as_derailed;
			bool angry_planes;
			bool angry_planes_rockets;
			float time_scale = 1.f;
			bool blackout;
			bool thermal_vision;
			bool night_vision;
			bool render_hd_only;
			float distance_scaling = 1.00f;
			bool part_water;
			bool ring_toggle;
			bool ring_rainbow;
			int ring_red;
			int ring_green;
			int ring_blue;
			float ring_distance = 1500;
			float ring_radius = 1000;
			float ring_hardness = 100;
			float ring_brightness = 100;
			bool decrease_ped_population;
			bool decrease_vehicle_population;


			bool m_ar_waypoint;
			bool m_waypoint_marker;
		};

		extern variables m_vars;
	}
}