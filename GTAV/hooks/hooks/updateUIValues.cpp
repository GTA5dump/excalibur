#include "pch.h"
#include "hooks/hooks.h"
#include "menu/submenus/main/world/rendering.h"

namespace base::hooks {

	inline rage::vector4 float_to_vector(const float color[4])
	{
		return rage::vector4(color[0], color[1], color[2], color[3]);
	}


	uint64_t hooks::updateUIValuesHook(int64_t _this, rage::TimecycleKeyframeData* data) {
		auto _return = ogUpdateUIValuesHook(_this, data);

		auto& var = menu::world::rendering::vars::m_vars;

		//data->m_plane.x = 100;

		if (var.m_azimuth_east_color.m_toggle_color) {
			if (var.m_azimuth_east_color.m_rainbow_toggle) {
				var.m_azimuth_east_color.m_rainbow.run();
				data->m_azimuth_east.x = (var.m_azimuth_east_color.m_color[0] / 255) * var.m_azimuth_east_color.m_luminance;
				data->m_azimuth_east.y = (var.m_azimuth_east_color.m_color[1] / 255) * var.m_azimuth_east_color.m_luminance;
				data->m_azimuth_east.z = (var.m_azimuth_east_color.m_color[2] / 255) * var.m_azimuth_east_color.m_luminance;
			}
			data->m_azimuth_east.x = (var.m_azimuth_east_color.m_color[0] / 255) * var.m_azimuth_east_color.m_luminance;
			data->m_azimuth_east.y = (var.m_azimuth_east_color.m_color[1] / 255) * var.m_azimuth_east_color.m_luminance;
			data->m_azimuth_east.z = (var.m_azimuth_east_color.m_color[2] / 255) * var.m_azimuth_east_color.m_luminance;
			//data->m_azimuth_east_intensity = var.m_azimuth_east_color.m_luminance / 255;
		}

		if (var.m_azimuth_west_color.m_toggle_color) {
			data->m_azimuth_west.x = (var.m_azimuth_west_color.m_color[0] / 255) * var.m_azimuth_west_color.m_luminance;
			data->m_azimuth_west.y = (var.m_azimuth_west_color.m_color[1] / 255) * var.m_azimuth_west_color.m_luminance;
			data->m_azimuth_west.z = (var.m_azimuth_west_color.m_color[2] / 255) * var.m_azimuth_west_color.m_luminance;
			//data->m_azimuth_west_intensity = var.m_azimuth_west_color.m_luminance / 255;
		}

		if (var.m_azimuth_transition_color.m_toggle_color) {
			data->m_azimuth_transition.x = (var.m_azimuth_transition_color.m_color[0] / 255) * var.m_azimuth_transition_color.m_luminance;
			data->m_azimuth_transition.y = (var.m_azimuth_transition_color.m_color[1] / 255) * var.m_azimuth_transition_color.m_luminance;
			data->m_azimuth_transition.z = (var.m_azimuth_transition_color.m_color[2] / 255) * var.m_azimuth_transition_color.m_luminance;
			//data->m_azimuth_transition_intensity = var.m_azimuth_transition_color.m_luminance / 255;
		}

		if (var.m_zenith_color.m_toggle_color) {
			data->m_zenith.x = (var.m_zenith_color.m_color[0] / 255) * var.m_zenith_color.m_luminance;
			data->m_zenith.y = (var.m_zenith_color.m_color[1] / 255) * var.m_zenith_color.m_luminance;
			data->m_zenith.z = (var.m_zenith_color.m_color[2] / 255) * var.m_zenith_color.m_luminance;
			//data->m_zenith_intensity = var.m_azimuth_transition_color.m_luminance / 255;
		}

		if (var.m_zenith_transition_color.m_toggle_color) {
			data->m_zenith_transition.x = (var.m_zenith_transition_color.m_color[0] / 255) * var.m_zenith_transition_color.m_luminance;
			data->m_zenith_transition.y = (var.m_zenith_transition_color.m_color[1] / 255) * var.m_zenith_transition_color.m_luminance;
			data->m_zenith_transition.z = (var.m_zenith_transition_color.m_color[2] / 255) * var.m_zenith_transition_color.m_luminance;
			//data->m_zenith_transition_intensity = var.m_zenith_transition_color.m_luminance / 255;
		}

		if (var.m_cloud_mid_color.m_toggle_color) {
			data->m_cloud_mid.x = (var.m_zenith_transition_color.m_color[0] / 255) * var.m_zenith_transition_color.m_luminance;
			data->m_cloud_mid.y = (var.m_zenith_transition_color.m_color[1] / 255) * var.m_zenith_transition_color.m_luminance;
			data->m_cloud_mid.z = (var.m_zenith_transition_color.m_color[2] / 255) * var.m_zenith_transition_color.m_luminance;
			//data->m_zenith_transition_intensity = var.m_zenith_transition_color.m_luminance / 255;
		}

		if (var.m_cloud_base_minus_mid_colour.m_toggle_color) {
			data->m_cloud_1.x = (var.m_cloud_base_minus_mid_colour.m_color[0] / 255) * var.m_cloud_base_minus_mid_colour.m_luminance;
			data->m_cloud_1.y = (var.m_cloud_base_minus_mid_colour.m_color[1] / 255) * var.m_cloud_base_minus_mid_colour.m_luminance;
			data->m_cloud_1.z = (var.m_cloud_base_minus_mid_colour.m_color[2] / 255) * var.m_cloud_base_minus_mid_colour.m_luminance;
			//data->m_zenith_transition_intensity = var.m_zenith_transition_color.m_luminance / 255;
		}

		if (var.m_cloud_shadow_minus_base_colour_times_shadow_strength.m_toggle_color) {
			data->m_small_cloud.x = (var.m_cloud_shadow_minus_base_colour_times_shadow_strength.m_color[0] / 255) * var.m_cloud_shadow_minus_base_colour_times_shadow_strength.m_luminance;
			data->m_small_cloud.y = (var.m_cloud_shadow_minus_base_colour_times_shadow_strength.m_color[1] / 255) * var.m_cloud_shadow_minus_base_colour_times_shadow_strength.m_luminance;
			data->m_small_cloud.z = (var.m_cloud_shadow_minus_base_colour_times_shadow_strength.m_color[2] / 255) * var.m_cloud_shadow_minus_base_colour_times_shadow_strength.m_luminance;
			//data->m_zenith_transition_intensity = var.m_zenith_transition_color.m_luminance / 255;
		}

		if (var.m_sun_color.m_toggle_color) {
			data->m_sun.x = (var.m_sun_color.m_color[0] / 255) * var.m_sun_color.m_luminance;
			data->m_sun.y = (var.m_sun_color.m_color[1] / 255) * var.m_sun_color.m_luminance;
			data->m_sun.z = (var.m_sun_color.m_color[2] / 255) * var.m_sun_color.m_luminance;
			//data->m_zenith_transition_intensity = var.m_zenith_transition_color.m_luminance / 255;
		}

		if (var.m_moon_color.m_toggle_color) {
			data->m_moon.x = (var.m_moon_color.m_color[0] / 255) * var.m_moon_color.m_luminance;
			data->m_moon.y = (var.m_moon_color.m_color[1] / 255) * var.m_moon_color.m_luminance;
			data->m_moon.z = (var.m_moon_color.m_color[2] / 255) * var.m_moon_color.m_luminance;
			//data->m_zenith_transition_intensity = var.m_zenith_transition_color.m_luminance / 255;
		}

		data->m_stars_iten = var.m_starfield_intensity;

		return _return;
	}

}