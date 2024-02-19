#include "pch.h"
#include "rendering.h"
#include "menu/util/control.h"

using namespace base::gui;
using namespace menu::world::rendering::vars;

namespace menu::world::rendering::vars {
	variables m_vars;

	inline const char* sky_color_names[] = {
	"Azimuth East", "Azimuth West", "Azimuth Transition", "Zenith", "Zenith Transition", "Cloud Base Minus Mid Color", "Cloud Mid", "Cloud Shadow Base Color", "Moon Color", "Sun Color"
	}; inline std::size_t selected_sky_color = 0;

	const float epsilon = 1e-5;

	bool isApproximatelyEqual(float a, float b, float epsilon) {
		return std::abs(a - b) < epsilon;
	}

}

namespace menu {

	void rendering_menu::render() {
		renderer::addSubmenu("Rendering", "game_rendering", [](core* core) {
			core->addOption(submenuOption("Visual Settings")
				.setTarget("visual_settings"));

			core->addOption(submenuOption("Sky Color")
				.setTarget("sky_color"));

			core->addOption(toggleOption("Night Vision")
				.addToggle(&m_vars.night_vision));

			core->addOption(toggleOption("Thermal Vision")
				.addToggle(&m_vars.thermal_vision));

			core->addOption(toggleOption("See Through Walls")
				.addToggle(&m_vars.m_see_through_walls).addTooltip("See through walls when aiming"));

			core->addOption(numberOption<float>("Starfield Intensity")
				.addNumber(&m_vars.m_starfield_intensity).addMin(1.00f).addMax(10000.0f).addStep(1.f).setPrecision(2));

			core->addOption(numberOption<float>("Distance Scaling")
				.addNumber(&m_vars.distance_scaling).addMin(1.00f).addMax(200.0f).addStep(0.01f).setPrecision(2));

			core->addOption(numberOption<float>("Fog on Map")
				.addNumber(&patterns::game_visuals->m_fog_level).addMin(0).addMax(10).addStep(0.0001).setPrecision(4));

			core->addOption(toggleOption("Render HD Only")
				.addToggle(&m_vars.render_hd_only));

			core->addOption(toggleOption("Potato Mode")
				.addToggle(&m_vars.decrease_graphics));
		});

		renderer::addSubmenu("Sky Color", "sky_color", [](core* core) {
			core->addOption(scrollOption<const char*, std::size_t>("Element")
				.addScroll(&sky_color_names).setPosition(&selected_sky_color));

			switch (selected_sky_color) {
			case 0:
				core->addOption(toggleOption("Toggle")
					.addToggle(&m_vars.m_azimuth_east_color.m_toggle_color));

				if (m_vars.m_azimuth_east_color.m_toggle_color) {
					core->addOption(numberOption<float>("[R]ed")
						.addNumber(&m_vars.m_azimuth_east_color.m_color[0]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("[G]reen")
						.addNumber(&m_vars.m_azimuth_east_color.m_color[1]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("[B]lue")
						.addNumber(&m_vars.m_azimuth_east_color.m_color[2]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("Luminance")
						.addNumber(&m_vars.m_azimuth_east_color.m_luminance).addMin(0).addMax(10).addStep(0.1f).setPrecision(2));

					core->addOption(toggleOption("Rainbow")
						.addToggle(&m_vars.m_azimuth_east_color.m_rainbow_toggle));
				}
				break;
			case 1:
				core->addOption(toggleOption("Toggle")
					.addToggle(&m_vars.m_azimuth_west_color.m_toggle_color));

				if (m_vars.m_azimuth_west_color.m_toggle_color) {
					core->addOption(numberOption<float>("[R]ed")
						.addNumber(&m_vars.m_azimuth_west_color.m_color[0]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("[G]reen")
						.addNumber(&m_vars.m_azimuth_west_color.m_color[1]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("[B]lue")
						.addNumber(&m_vars.m_azimuth_west_color.m_color[2]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("Luminance")
						.addNumber(&m_vars.m_azimuth_west_color.m_luminance).addMin(0).addMax(10).addStep(0.1f).setPrecision(2));

					core->addOption(toggleOption("Rainbow")
						.addToggle(&m_vars.m_azimuth_west_color.m_rainbow_toggle));
				}
				break;
			case 2:
				core->addOption(toggleOption("Toggle")
					.addToggle(&m_vars.m_azimuth_transition_color.m_toggle_color));

				if (m_vars.m_azimuth_transition_color.m_toggle_color) {
					core->addOption(numberOption<float>("[R]ed")
						.addNumber(&m_vars.m_azimuth_transition_color.m_color[0]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("[G]reen")
						.addNumber(&m_vars.m_azimuth_transition_color.m_color[1]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("[B]lue")
						.addNumber(&m_vars.m_azimuth_transition_color.m_color[2]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("Luminance")
						.addNumber(&m_vars.m_azimuth_transition_color.m_luminance).addMin(0).addMax(10).addStep(0.1f).setPrecision(2));

					core->addOption(toggleOption("Rainbow")
						.addToggle(&m_vars.m_azimuth_transition_color.m_rainbow_toggle));
				}
				break;
			case 3:
				core->addOption(toggleOption("Toggle")
					.addToggle(&m_vars.m_zenith_color.m_toggle_color));

				if (m_vars.m_zenith_color.m_toggle_color) {
					core->addOption(numberOption<float>("[R]ed")
						.addNumber(&m_vars.m_zenith_color.m_color[0]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("[G]reen")
						.addNumber(&m_vars.m_zenith_color.m_color[1]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("[B]lue")
						.addNumber(&m_vars.m_zenith_color.m_color[2]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("Luminance")
						.addNumber(&m_vars.m_zenith_color.m_luminance).addMin(0).addMax(10).addStep(0.1f).setPrecision(2));

					core->addOption(toggleOption("Rainbow")
						.addToggle(&m_vars.m_zenith_color.m_rainbow_toggle));
				}
				break;
			case 4:
				core->addOption(toggleOption("Toggle")
					.addToggle(&m_vars.m_zenith_transition_color.m_toggle_color));

				if (m_vars.m_zenith_transition_color.m_toggle_color) {
					core->addOption(numberOption<float>("[R]ed")
						.addNumber(&m_vars.m_zenith_transition_color.m_color[0]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("[G]reen")
						.addNumber(&m_vars.m_zenith_transition_color.m_color[1]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("[B]lue")
						.addNumber(&m_vars.m_zenith_transition_color.m_color[2]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("Luminance")
						.addNumber(&m_vars.m_zenith_transition_color.m_luminance).addMin(0).addMax(10).addStep(0.1f).setPrecision(2));

					core->addOption(toggleOption("Rainbow")
						.addToggle(&m_vars.m_zenith_transition_color.m_rainbow_toggle));
				}
				break;
			case 5:
				core->addOption(toggleOption("Toggle")
					.addToggle(&m_vars.m_cloud_base_minus_mid_colour.m_toggle_color));

				if (m_vars.m_cloud_base_minus_mid_colour.m_toggle_color) {
					core->addOption(numberOption<float>("[R]ed")
						.addNumber(&m_vars.m_cloud_base_minus_mid_colour.m_color[0]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("[G]reen")
						.addNumber(&m_vars.m_cloud_base_minus_mid_colour.m_color[1]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("[B]lue")
						.addNumber(&m_vars.m_cloud_base_minus_mid_colour.m_color[2]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("Luminance")
						.addNumber(&m_vars.m_cloud_base_minus_mid_colour.m_luminance).addMin(0).addMax(10).addStep(0.1f).setPrecision(2));

					core->addOption(toggleOption("Rainbow")
						.addToggle(&m_vars.m_cloud_base_minus_mid_colour.m_rainbow_toggle));
				}
				break;
			case 6:
				core->addOption(toggleOption("Toggle")
					.addToggle(&m_vars.m_cloud_mid_color.m_toggle_color));

				if (m_vars.m_cloud_mid_color.m_toggle_color) {
					core->addOption(numberOption<float>("[R]ed")
						.addNumber(&m_vars.m_cloud_mid_color.m_color[0]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("[G]reen")
						.addNumber(&m_vars.m_cloud_mid_color.m_color[1]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("[B]lue")
						.addNumber(&m_vars.m_cloud_mid_color.m_color[2]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("Luminance")
						.addNumber(&m_vars.m_cloud_mid_color.m_luminance).addMin(0).addMax(10).addStep(0.1f).setPrecision(2));

					core->addOption(toggleOption("Rainbow")
						.addToggle(&m_vars.m_cloud_mid_color.m_rainbow_toggle));
				}
				break;
			case 7:
				core->addOption(toggleOption("Toggle")
					.addToggle(&m_vars.m_cloud_shadow_minus_base_colour_times_shadow_strength.m_toggle_color));

				if (m_vars.m_cloud_shadow_minus_base_colour_times_shadow_strength.m_toggle_color) {
					core->addOption(numberOption<float>("[R]ed")
						.addNumber(&m_vars.m_cloud_shadow_minus_base_colour_times_shadow_strength.m_color[0]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("[G]reen")
						.addNumber(&m_vars.m_cloud_shadow_minus_base_colour_times_shadow_strength.m_color[1]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("[B]lue")
						.addNumber(&m_vars.m_cloud_shadow_minus_base_colour_times_shadow_strength.m_color[2]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("Luminance")
						.addNumber(&m_vars.m_cloud_shadow_minus_base_colour_times_shadow_strength.m_luminance).addMin(0).addMax(10).addStep(0.1f).setPrecision(2));

					core->addOption(toggleOption("Rainbow")
						.addToggle(&m_vars.m_cloud_shadow_minus_base_colour_times_shadow_strength.m_rainbow_toggle));
				}
				break;
			case 8:
				core->addOption(toggleOption("Toggle")
					.addToggle(&m_vars.m_moon_color.m_toggle_color));

				if (m_vars.m_moon_color.m_toggle_color) {
					core->addOption(numberOption<float>("[R]ed")
						.addNumber(&m_vars.m_moon_color.m_color[0]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("[G]reen")
						.addNumber(&m_vars.m_moon_color.m_color[1]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("[B]lue")
						.addNumber(&m_vars.m_moon_color.m_color[2]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("Luminance")
						.addNumber(&m_vars.m_moon_color.m_luminance).addMin(0).addMax(10).addStep(0.1f).setPrecision(2));

					core->addOption(toggleOption("Rainbow")
						.addToggle(&m_vars.m_sun_color.m_rainbow_toggle));
				}
				break;
			case 9:
				core->addOption(toggleOption("Toggle")
					.addToggle(&m_vars.m_sun_color.m_toggle_color));

				if (m_vars.m_sun_color.m_toggle_color) {
					core->addOption(numberOption<float>("[R]ed")
						.addNumber(&m_vars.m_sun_color.m_color[0]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("[G]reen")
						.addNumber(&m_vars.m_sun_color.m_color[1]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("[B]lue")
						.addNumber(&m_vars.m_sun_color.m_color[2]).addMin(0).addMax(255).addStep(1).setPrecision(1));

					core->addOption(numberOption<float>("Luminance")
						.addNumber(&m_vars.m_sun_color.m_luminance).addMin(0).addMax(10).addStep(0.1f).setPrecision(2));

					core->addOption(toggleOption("Rainbow")
						.addToggle(&m_vars.m_moon_color.m_rainbow_toggle));
				}
				break;
			}
		});

		renderer::addSubmenu("Visual Settings", "visual_settings", [](core* core) {
			core->addOption(numberOption<float>("Shadow Light")
				.addNumber(&patterns::visual_settings->m_shadow_light).addMin(-100).addMax(100).addStep(1).setPrecision(0));

			core->addOption(numberOption<float>("Reflection")
				.addNumber(&patterns::visual_settings->m_reflection).addMin(-100).addMax(100).addStep(1).setPrecision(0));

			core->addOption(numberOption<float>("Gamma")
				.addNumber(&patterns::visual_settings->m_gamma).addMin(-100).addMax(100).addStep(1).setPrecision(0));

			core->addOption(numberOption<float>("Near Blur")
				.addNumber(&patterns::visual_settings->m_blur).addMin(-100).addMax(100).addStep(1).setPrecision(0));

			core->addOption(numberOption<float>("Far Blur")
				.addNumber(&patterns::visual_settings->m_blur2).addMin(-100).addMax(100).addStep(1).setPrecision(0));

			core->addOption(numberOption<float>("Sky Intensity")
				.addNumber(&patterns::visual_settings->m_sky_intensity).addMin(-100).addMax(100).addStep(1).setPrecision(0));

			core->addOption(numberOption<float>("Saturation")
				.addNumber(&patterns::visual_settings->m_saturation).addMin(-100).addMax(100).addStep(1).setPrecision(0));
		});
	}

	void rendering_menu::update() {
		render();
		if (m_vars.m_see_through_walls) {
			CAM::SET_THIRD_PERSON_AIM_CAM_NEAR_CLIP_THIS_UPDATE(418.490f);
		}

		
		// ...

		if (m_vars.m_azimuth_east_color.m_rainbow_toggle) {
			if (m_vars.m_azimuth_east_color.m_color[0] > 0 && isApproximatelyEqual(m_vars.m_azimuth_east_color.m_color[2], 0.0f, epsilon)) {
				m_vars.m_azimuth_east_color.m_color[0] -= 1.0f;
				m_vars.m_azimuth_east_color.m_color[1] += 1.0f;
			}
			if (m_vars.m_azimuth_east_color.m_color[1] > 0 && isApproximatelyEqual(m_vars.m_azimuth_east_color.m_color[0], 0.0f, epsilon)) {
				m_vars.m_azimuth_east_color.m_color[1] -= 1.0f;
				m_vars.m_azimuth_east_color.m_color[2] += 1.0f;
			}
			if (m_vars.m_azimuth_east_color.m_color[2] > 0 && isApproximatelyEqual(m_vars.m_azimuth_east_color.m_color[1], 0.0f, epsilon)) {
				m_vars.m_azimuth_east_color.m_color[0] += 1.0f;
				m_vars.m_azimuth_east_color.m_color[2] -= 1.0f;
			}
		}

		if (m_vars.m_azimuth_west_color.m_rainbow_toggle) {
			if (m_vars.m_azimuth_west_color.m_color[0] > 0 && isApproximatelyEqual(m_vars.m_azimuth_west_color.m_color[2], 0.0f, epsilon)) {
				m_vars.m_azimuth_west_color.m_color[0] -= 1.0f;
				m_vars.m_azimuth_west_color.m_color[1] += 1.0f;
			}
			if (m_vars.m_azimuth_west_color.m_color[1] > 0 && isApproximatelyEqual(m_vars.m_azimuth_west_color.m_color[0], 0.0f, epsilon)) {
				m_vars.m_azimuth_west_color.m_color[1] -= 1.0f;
				m_vars.m_azimuth_west_color.m_color[2] += 1.0f;
			}
			if (m_vars.m_azimuth_west_color.m_color[2] > 0 && isApproximatelyEqual(m_vars.m_azimuth_west_color.m_color[1], 0.0f, epsilon)) {
				m_vars.m_azimuth_west_color.m_color[0] += 1.0f;
				m_vars.m_azimuth_west_color.m_color[2] -= 1.0f;
			}
		}

		if (m_vars.m_azimuth_transition_color.m_rainbow_toggle) {
			if (m_vars.m_azimuth_transition_color.m_color[0] > 0 && isApproximatelyEqual(m_vars.m_azimuth_transition_color.m_color[2], 0.0f, epsilon)) {
				m_vars.m_azimuth_transition_color.m_color[0] -= 1.0f;
				m_vars.m_azimuth_transition_color.m_color[1] += 1.0f;
			}
			if (m_vars.m_azimuth_transition_color.m_color[1] > 0 && isApproximatelyEqual(m_vars.m_azimuth_transition_color.m_color[0], 0.0f, epsilon)) {
				m_vars.m_azimuth_transition_color.m_color[1] -= 1.0f;
				m_vars.m_azimuth_transition_color.m_color[2] += 1.0f;
			}
			if (m_vars.m_azimuth_transition_color.m_color[2] > 0 && isApproximatelyEqual(m_vars.m_azimuth_transition_color.m_color[1], 0.0f, epsilon)) {
				m_vars.m_azimuth_transition_color.m_color[0] += 1.0f;
				m_vars.m_azimuth_transition_color.m_color[2] -= 1.0f;
			}
		}

		if (m_vars.m_zenith_color.m_rainbow_toggle) {
			if (m_vars.m_zenith_color.m_color[0] > 0 && isApproximatelyEqual(m_vars.m_zenith_color.m_color[2], 0.0f, epsilon)) {
				m_vars.m_zenith_color.m_color[0] -= 1.0f;
				m_vars.m_zenith_color.m_color[1] += 1.0f;
			}
			if (m_vars.m_zenith_color.m_color[1] > 0 && isApproximatelyEqual(m_vars.m_zenith_color.m_color[0], 0.0f, epsilon)) {
				m_vars.m_zenith_color.m_color[1] -= 1.0f;
				m_vars.m_zenith_color.m_color[2] += 1.0f;
			}
			if (m_vars.m_zenith_color.m_color[2] > 0 && isApproximatelyEqual(m_vars.m_zenith_color.m_color[1], 0.0f, epsilon)) {
				m_vars.m_zenith_color.m_color[0] += 1.0f;
				m_vars.m_zenith_color.m_color[2] -= 1.0f;
			}
		}

		if (m_vars.m_zenith_transition_color.m_rainbow_toggle) {
			if (m_vars.m_zenith_transition_color.m_color[0] > 0 && isApproximatelyEqual(m_vars.m_zenith_transition_color.m_color[2], 0.0f, epsilon)) {
				m_vars.m_zenith_transition_color.m_color[0] -= 1.0f;
				m_vars.m_zenith_transition_color.m_color[1] += 1.0f;
			}
			if (m_vars.m_zenith_transition_color.m_color[1] > 0 && isApproximatelyEqual(m_vars.m_zenith_transition_color.m_color[0], 0.0f, epsilon)) {
				m_vars.m_zenith_transition_color.m_color[1] -= 1.0f;
				m_vars.m_zenith_transition_color.m_color[2] += 1.0f;
			}
			if (m_vars.m_zenith_transition_color.m_color[2] > 0 && isApproximatelyEqual(m_vars.m_zenith_transition_color.m_color[1], 0.0f, epsilon)) {
				m_vars.m_zenith_transition_color.m_color[0] += 1.0f;
				m_vars.m_zenith_transition_color.m_color[2] -= 1.0f;
			}
		}

		if (m_vars.m_cloud_base_minus_mid_colour.m_rainbow_toggle) {
			if (m_vars.m_cloud_base_minus_mid_colour.m_color[0] > 0 && isApproximatelyEqual(m_vars.m_cloud_base_minus_mid_colour.m_color[2], 0.0f, epsilon)) {
				m_vars.m_cloud_base_minus_mid_colour.m_color[0] -= 1.0f;
				m_vars.m_cloud_base_minus_mid_colour.m_color[1] += 1.0f;
			}
			if (m_vars.m_cloud_base_minus_mid_colour.m_color[1] > 0 && isApproximatelyEqual(m_vars.m_cloud_base_minus_mid_colour.m_color[0], 0.0f, epsilon)) {
				m_vars.m_cloud_base_minus_mid_colour.m_color[1] -= 1.0f;
				m_vars.m_cloud_base_minus_mid_colour.m_color[2] += 1.0f;
			}
			if (m_vars.m_cloud_base_minus_mid_colour.m_color[2] > 0 && isApproximatelyEqual(m_vars.m_cloud_base_minus_mid_colour.m_color[1], 0.0f, epsilon)) {
				m_vars.m_cloud_base_minus_mid_colour.m_color[0] += 1.0f;
				m_vars.m_cloud_base_minus_mid_colour.m_color[2] -= 1.0f;
			}
		}

		if (m_vars.m_cloud_mid_color.m_rainbow_toggle) {
			if (m_vars.m_cloud_mid_color.m_color[0] > 0 && isApproximatelyEqual(m_vars.m_cloud_mid_color.m_color[2], 0.0f, epsilon)) {
				m_vars.m_cloud_mid_color.m_color[0] -= 1.0f;
				m_vars.m_cloud_mid_color.m_color[1] += 1.0f;
			}
			if (m_vars.m_cloud_mid_color.m_color[1] > 0 && isApproximatelyEqual(m_vars.m_cloud_mid_color.m_color[0], 0.0f, epsilon)) {
				m_vars.m_cloud_mid_color.m_color[1] -= 1.0f;
				m_vars.m_cloud_mid_color.m_color[2] += 1.0f;
			}
			if (m_vars.m_cloud_mid_color.m_color[2] > 0 && isApproximatelyEqual(m_vars.m_cloud_mid_color.m_color[1], 0.0f, epsilon)) {
				m_vars.m_cloud_mid_color.m_color[0] += 1.0f;
				m_vars.m_cloud_mid_color.m_color[2] -= 1.0f;
			}
		}

		if (m_vars.m_cloud_shadow_minus_base_colour_times_shadow_strength.m_rainbow_toggle) {
			if (m_vars.m_cloud_shadow_minus_base_colour_times_shadow_strength.m_color[0] > 0 && isApproximatelyEqual(m_vars.m_cloud_shadow_minus_base_colour_times_shadow_strength.m_color[2], 0.0f, epsilon)) {
				m_vars.m_cloud_shadow_minus_base_colour_times_shadow_strength.m_color[0] -= 1.0f;
				m_vars.m_cloud_shadow_minus_base_colour_times_shadow_strength.m_color[1] += 1.0f;
			}
			if (m_vars.m_cloud_shadow_minus_base_colour_times_shadow_strength.m_color[1] > 0 && isApproximatelyEqual(m_vars.m_cloud_shadow_minus_base_colour_times_shadow_strength.m_color[0], 0.0f, epsilon)) {
				m_vars.m_cloud_shadow_minus_base_colour_times_shadow_strength.m_color[1] -= 1.0f;
				m_vars.m_cloud_shadow_minus_base_colour_times_shadow_strength.m_color[2] += 1.0f;
			}
			if (m_vars.m_cloud_shadow_minus_base_colour_times_shadow_strength.m_color[2] > 0 && isApproximatelyEqual(m_vars.m_cloud_shadow_minus_base_colour_times_shadow_strength.m_color[1], 0.0f, epsilon)) {
				m_vars.m_cloud_shadow_minus_base_colour_times_shadow_strength.m_color[0] += 1.0f;
				m_vars.m_cloud_shadow_minus_base_colour_times_shadow_strength.m_color[2] -= 1.0f;
			}
		}

		if (m_vars.m_sun_color.m_rainbow_toggle) {
			if (m_vars.m_sun_color.m_color[0] > 0 && isApproximatelyEqual(m_vars.m_sun_color.m_color[2], 0.0f, epsilon)) {
				m_vars.m_sun_color.m_color[0] -= 1.0f;
				m_vars.m_sun_color.m_color[1] += 1.0f;
			}
			if (m_vars.m_sun_color.m_color[1] > 0 && isApproximatelyEqual(m_vars.m_sun_color.m_color[0], 0.0f, epsilon)) {
				m_vars.m_sun_color.m_color[1] -= 1.0f;
				m_vars.m_sun_color.m_color[2] += 1.0f;
			}
			if (m_vars.m_sun_color.m_color[2] > 0 && isApproximatelyEqual(m_vars.m_sun_color.m_color[1], 0.0f, epsilon)) {
				m_vars.m_sun_color.m_color[0] += 1.0f;
				m_vars.m_sun_color.m_color[2] -= 1.0f;
			}
		}

		if (m_vars.m_moon_color.m_rainbow_toggle) {
			if (m_vars.m_moon_color.m_color[0] > 0 && isApproximatelyEqual(m_vars.m_moon_color.m_color[2], 0.0f, epsilon)) {
				m_vars.m_moon_color.m_color[0] -= 1.0f;
				m_vars.m_moon_color.m_color[1] += 1.0f;
			}
			if (m_vars.m_moon_color.m_color[1] > 0 && isApproximatelyEqual(m_vars.m_moon_color.m_color[0], 0.0f, epsilon)) {
				m_vars.m_moon_color.m_color[1] -= 1.0f;
				m_vars.m_moon_color.m_color[2] += 1.0f;
			}
			if (m_vars.m_moon_color.m_color[2] > 0 && isApproximatelyEqual(m_vars.m_moon_color.m_color[1], 0.0f, epsilon)) {
				m_vars.m_moon_color.m_color[0] += 1.0f;
				m_vars.m_moon_color.m_color[2] -= 1.0f;
			}
		}

		STREAMING::OVERRIDE_LODSCALE_THIS_FRAME(m_vars.distance_scaling);

		if (m_vars.night_vision) {
			*script_global(1853988).at(PLAYER::PLAYER_ID(), 862).at(823).at(13).as<int*>() = -1;
			GRAPHICS::SET_NIGHTVISION(true);
		}
		else {
			GRAPHICS::SET_NIGHTVISION(false);
		}

		if (m_vars.thermal_vision) {
			*script_global(1853988).at(PLAYER::PLAYER_ID(), 862).at(823).at(13).as<int*>() = -1;
			GRAPHICS::SET_SEETHROUGH(true);
		}
		else {
			GRAPHICS::SET_SEETHROUGH(false);
		}

		if (m_vars.render_hd_only) {
			STREAMING::SET_RENDER_HD_ONLY(true);
		}
		else {
			STREAMING::SET_RENDER_HD_ONLY(false);
		}
		
	}
}