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
	class rendering_menu {
	public:
		void render();
		void update();
	};

	static rendering_menu* getRenderingMenu() {
		static rendering_menu instance;
		return &instance;
	}

	namespace world::rendering::vars {
		struct sky_color {
			bool m_toggle_color = false;
			bool m_rainbow_toggle;
			float m_luminance = 1.f;
			float m_internal_color[4] = { 255, 0, 0, 0 };
			float m_color[3] = { 255, 0, 0 };
			menu::rainbow m_rainbow;
			std::vector<uint8_t> m_cache;
		};
		struct variables {
			bool m_see_through_walls;
			bool decrease_graphics;
			bool blackout;
			bool thermal_vision;
			bool night_vision;
			bool render_hd_only;
			float distance_scaling = 1.00f;

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

			float m_starfield_intensity = 1.f;

		};

		extern variables m_vars;
	}
}