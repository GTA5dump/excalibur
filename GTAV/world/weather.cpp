#include "pch.h"
#include "weather.h"
#include "menu/util/control.h"
#include "rage/classes/vfx.h"
using namespace base::gui;
using namespace menu::world::weather::vars;

namespace menu::world::weather::vars {
	variables m_vars;

	const char* weather_type[] = {
		   "clear", "clearing", "clouds", "extrasunny", "foggy", "halloween", "neutral", "overcast", "rain", "smog", "snow", "snowlight", "Blizzard", "thunder"
	}; inline std::size_t weather_id = 0;

	inline const char* cloud_type[] = {

		"shower", "Snowy 01", "Stormy 01", "Stratoscumulus", "Stripey", "Wispy", "Altostratus", "Cirrocumulus", "Altostratus", "Clear 01", "Cloudy 01" ,"Contrails", "NoClouds", "Puffs", "Rain", "Snow"
	}; inline std::size_t cloud_id = 0;

	void SetClouds(const char* cloudtexture) {
		MISC::LOAD_CLOUD_HAT(cloudtexture, 3.f);
	}





	inline std::pair<uint32_t, std::string> names[] = {
		{ 0xE947723D, "Rainstorm Drop" },
		{ 0xF4698119, "Thunder Drop" },
		{ 0xB13E1842, "Snow Light Drop" },
		{ 0x7F84E74E, "Snow Heavy Drop" },
		{ 0xFA37E4E2, "Blizzard Drop" },
		{ 0xC11D1EC6, "Underwater Drop" },
		{ 0x69163FA7, "Lake Fog Drop" },
		{ 0x91C32C69, "Woodland Pollen Drop" },
		{ 0x8DE5FE6A, "Woodland Firefly Drop" },
		{ 0x36196668, "Wetland Flies Drop" },
	};
	struct scroll_names_struct { std::string name; int id; };
	inline std::vector<scroll_names_struct> scroll_names;


	inline std::string get_shader_name(uint32_t name_hash) {
		auto vit = std::find_if(begin(names), end(names), [=](std::pair<uint32_t, std::string> e) { return e.first == name_hash; });
		if (vit != end(names)) {
			return vit->second;
		}

		return "Unknown";
	}
	inline const char* weather_fx_names[] = {
		"Rainstorm Drop", "Thunder Drop", "Snow Light Drop", "Snow Heavy Drop", "Blizzard Drop", "Underwater Drop", "Lake Fog Drop", "Woodland Pollen Drop", "Woodland Firefly Drop", "Wetland Flies Drop"
	}; inline std::size_t weather_fx_names_id = 0;


	template<typename Type>
	struct scroll_struct {
		const char* m_name;
		Type m_result;
	};
}

namespace menu {

	void weather_menu::render() {
		renderer::addSubmenu("Weather", "weather", [](core* core) {
			core->addOption(submenuOption("Weather Settings")
				.setTarget("weather_fx"));

			core->addOption(scrollOption<const char*, std::size_t>("Modify Weather")
				.addScroll(&weather_type).setPosition(&weather_id).addClick([] { 	MISC::SET_WEATHER_TYPE_NOW_PERSIST(weather_type[weather_id]); }));

			core->addOption(scrollOption<const char*, std::size_t>("Modify Clouds")
				.addScroll(&cloud_type).setPosition(&cloud_id).addClick([] { SetClouds(cloud_type[cloud_id]); }));

			core->addOption(buttonOption("Flash Lightning")
				.addClick([] { MISC::FORCE_LIGHTNING_FLASH(); }));
		});

		renderer::addSubmenu("Weather Settings", "weather_fx", [](core* core) {
			core->addOption(scrollOption<const char*, int>("Type")
				.addScroll(&weather_fx_names).setPosition(&m_vars.m_scroll));

			core->addOption(numberOption<float>("[R]ed")
				.addNumber(&m_vars.m_shaders[m_vars.m_scroll].red).addMin(0).addMax(255).setPrecision(0)
				.addClick([] { m_vars.m_shaders[m_vars.m_scroll].m_drop->m_color.x = m_vars.m_shaders[m_vars.m_scroll].red / 255.f; }));

			core->addOption(numberOption<float>("[G]reen")
				.addNumber(&m_vars.m_shaders[m_vars.m_scroll].green).addMin(0).addMax(255).setPrecision(0)
				.addClick([] { m_vars.m_shaders[m_vars.m_scroll].m_drop->m_color.y = m_vars.m_shaders[m_vars.m_scroll].green / 255.f; }));

			core->addOption(numberOption<float>("[B]lue")
				.addNumber(&m_vars.m_shaders[m_vars.m_scroll].blue).addMin(0).addMax(255).setPrecision(0)
				.addClick([] { m_vars.m_shaders[m_vars.m_scroll].m_drop->m_color.z = m_vars.m_shaders[m_vars.m_scroll].blue / 255.f; }));

			core->addOption(numberOption<float>("Luminance").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_luminance).addMin(0.f).addMax(100.f).addStep(0.1f).setPrecision(1.f)
				.addClick([] {
					m_vars.m_shaders[m_vars.m_scroll].m_drop->m_color.x = (m_vars.m_shaders[m_vars.m_scroll].red / 255.f) * m_vars.m_shaders[m_vars.m_scroll].m_luminance;
					m_vars.m_shaders[m_vars.m_scroll].m_drop->m_color.y = (m_vars.m_shaders[m_vars.m_scroll].green / 255.f) * m_vars.m_shaders[m_vars.m_scroll].m_luminance;
					m_vars.m_shaders[m_vars.m_scroll].m_drop->m_color.z = (m_vars.m_shaders[m_vars.m_scroll].blue / 255.f) * m_vars.m_shaders[m_vars.m_scroll].m_luminance;
					}));

			core->addOption(breakOption("Modifiers"));

			core->addOption(numberOption<float>("Gravity").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_drop->m_gravity).addMin(-100.f).addMax(100.f).addStep(0.1f).setPrecision(1.f));
			core->addOption(numberOption<float>("Box Centre Offset X").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_drop->m_box_centre_offset.x).addMin(-100.f).addMax(100.f).addStep(0.01f).setPrecision(2.f));
			core->addOption(numberOption<float>("Box Centre Offset Y").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_drop->m_box_centre_offset.y).addMin(-100.f).addMax(100.f).addStep(0.01f).setPrecision(2.f));
			core->addOption(numberOption<float>("Box Centre Offset Z").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_drop->m_box_centre_offset.z).addMin(-100.f).addMax(100.f).addStep(0.01f).setPrecision(2.f));
			core->addOption(numberOption<float>("Box Size X").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_drop->m_box_size.x).addMin(-100.f).addMax(100.f).addStep(0.01f).setPrecision(2.f));
			core->addOption(numberOption<float>("Box Size Y").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_drop->m_box_size.y).addMin(-100.f).addMax(100.f).addStep(0.01f).setPrecision(2.f));
			core->addOption(numberOption<float>("Box Size Z").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_drop->m_box_size.z).addMin(-100.f).addMax(100.f).addStep(0.01f).setPrecision(2.f));
			core->addOption(numberOption<float>("Life Minimum").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_drop->m_life_min_max.x).addMin(-100.f).addMax(100.f).addStep(0.01f).setPrecision(2.f));
			core->addOption(numberOption<float>("Life Maximum").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_drop->m_life_min_max.y).addMin(-100.f).addMax(100.f).addStep(0.01f).setPrecision(2.f));
			core->addOption(numberOption<float>("Velocity Minimum X").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_drop->m_velocity_min.x).addMin(-100.f).addMax(100.f).addStep(0.01f).setPrecision(2.f));
			core->addOption(numberOption<float>("Velocity Minimum Y").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_drop->m_velocity_min.y).addMin(-100.f).addMax(100.f).addStep(0.01f).setPrecision(2.f));
			core->addOption(numberOption<float>("Velocity Minimum Z").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_drop->m_velocity_min.z).addMin(-100.f).addMax(100.f).addStep(0.01f).setPrecision(2.f));
			core->addOption(numberOption<float>("Velocity Maximum X").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_drop->m_velocity_max.x).addMin(-100.f).addMax(100.f).addStep(0.01f).setPrecision(2.f));
			core->addOption(numberOption<float>("Velocity Maximum Y").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_drop->m_velocity_max.y).addMin(-100.f).addMax(100.f).addStep(0.01f).setPrecision(2.f));
			core->addOption(numberOption<float>("Velocity Maximum Z").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_drop->m_velocity_max.z).addMin(-100.f).addMax(100.f).addStep(0.01f).setPrecision(2.f));
			core->addOption(numberOption<float>("Size Minimum X").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_drop->m_size_min_max.x).addMin(-100.f).addMax(100.f).addStep(0.01f).setPrecision(2.f));
			core->addOption(numberOption<float>("Size Minimum Y").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_drop->m_size_min_max.y).addMin(-100.f).addMax(100.f).addStep(0.01f).setPrecision(2.f));
			core->addOption(numberOption<float>("Size Maximum X").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_drop->m_size_min_max.z).addMin(-100.f).addMax(100.f).addStep(0.01f).setPrecision(2.f));
			core->addOption(numberOption<float>("Size Maximum Y").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_drop->m_size_min_max.w).addMin(-100.f).addMax(100.f).addStep(0.01f).setPrecision(2.f));
			core->addOption(numberOption<float>("Fade In").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_drop->m_fade_in_out.x).addMin(-100.f).addMax(100.f).addStep(0.01f).setPrecision(2.f));
			core->addOption(numberOption<float>("Fade Out").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_drop->m_fade_in_out.y).addMin(-100.f).addMax(100.f).addStep(0.01f).setPrecision(2.f));
			core->addOption(numberOption<float>("Fade Near").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_drop->m_fade_near_far.x).addMin(-100.f).addMax(100.f).addStep(0.01f).setPrecision(2.f));
			core->addOption(numberOption<float>("Fade Far").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_drop->m_fade_near_far.y).addMin(-100.f).addMax(100.f).addStep(0.01f).setPrecision(2.f));
			core->addOption(numberOption<float>("Edge Softness").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_drop->m_edge_softness).addMin(-100.f).addMax(100.f).addStep(0.01f).setPrecision(2.f));
			core->addOption(numberOption<float>("Particle Color Percentage").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_drop->m_particle_color_percentage).addMin(-100.f).addMax(100.f).addStep(0.01f).setPrecision(2.f));
			core->addOption(numberOption<float>("Background Distortion Visibility Percentage").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_drop->m_background_distortion_visibility_percentage).addMin(-100.f).addMax(100.f).addStep(0.01f).setPrecision(2.f));
			core->addOption(numberOption<float>("Background Distortion Alpha Booster").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_drop->m_background_distortion_alpha_booster).addMin(-100.f).addMax(100.f).addStep(0.01f).setPrecision(2.f));
			core->addOption(numberOption<float>("Background Distortion Amount").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_drop->m_background_distortion_amount).addMin(-100.f).addMax(100.f).addStep(0.01f).setPrecision(2.f));
			core->addOption(numberOption<float>("Local Lights Multiplier").addNumber(&m_vars.m_shaders[m_vars.m_scroll].m_drop->m_local_lights_multiplier).addMin(-100.f).addMax(100.f).addStep(0.01f).setPrecision(2.f));
		});
	}

	void weather_menu::update() {

		static bool init = false;
		if (!init) {
			for (uint32_t i = 0; i < 0xA; i++) {
				rage::CWeatherVfx* current = &patterns::weather_fx[i];
				if (!get_shader_name(current->m_name_hash).empty()) {
					float luminance = 1.f;
					float red = (current->m_color.x / 255.f) * luminance;
					float green = (current->m_color.y / 255.f) * luminance;
					float blue = (current->m_color.z / 255.f) * luminance;
					m_vars.m_shaders.push_back({ current, red, green, blue, luminance });
				}
			}
			init = true;
		}

		render();

		
	}
}