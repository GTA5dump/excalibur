#include "pch.h"
#include "water.h"
#include "menu/util/control.h"

using namespace base::gui;
using namespace menu::world::water::vars;

namespace menu::world::water::vars {
	variables m_vars;


	void ocean_loop(eOceanTypes type, std::function<void(uint64_t)> callback) {
		uint64_t quad_pool = 0;
		short quad_count = 0;

		switch (type) {
		case OCEAN_TYPE_OCEAN:
			quad_pool = patterns::ocean_quads.m_ocean->m_quad_pool;
			quad_count = patterns::ocean_quads.m_ocean->m_quad_count;
			break;

		case OCEAN_TYPE_WAVE:
			quad_pool = patterns::ocean_quads.m_wave->m_quad_pool;
			quad_count = patterns::ocean_quads.m_wave->m_quad_count;
			break;

		case OCEAN_TYPE_CALMING:
			quad_pool = patterns::ocean_quads.m_calming->m_quad_pool;
			quad_count = patterns::ocean_quads.m_calming->m_quad_count;
			break;
		}

		for (short i = 0; i < quad_count; i++) {
			switch (type) {
			case OCEAN_TYPE_OCEAN:
				callback((quad_pool + (i * sizeof(rage::ocean_quad))));
				break;

			case OCEAN_TYPE_WAVE:
				callback((quad_pool + (i * sizeof(rage::ocean_wave_quad))));
				break;

			case OCEAN_TYPE_CALMING:
				callback((quad_pool + (i * sizeof(rage::ocean_calming_quad))));
				break;
			}
		}
	}

	void ocean_task(eOceanTypes type, eOceanTasks task) {
		ocean_loop(type, [=](uint64_t pool) {
			switch (task) {
			case OCEAN_DISABLE: {
				rage::ocean_quad* quad = (rage::ocean_quad*)(pool);

				if (m_vars.m_disable_ocean && quad->m_height == 0.0f) {
					quad->m_height = -10000.0f;
				}
				else if (!m_vars.m_disable_ocean && quad->m_height == -10000.0f) {
					quad->m_height = 0.0f;
				}

				break;
			}

			case OCEAN_CLEAR: {
				rage::ocean_quad* quad = (rage::ocean_quad*)(pool);
				quad->m_alpha = m_vars.m_clear_ocean ? 0x01010101 : 0x1A1A1A1A;
				break;
			}

			case OCEAN_FIERCE: {
				rage::ocean_wave_quad* quad = (rage::ocean_wave_quad*)(pool);
				quad->m_amplitude = m_vars.m_fierce_ocean ? quad->m_amplitude + 2000 : quad->m_amplitude - 2000;
				break;
			}
			}
			});
	}
	
}

namespace menu {

	void water_menu::render() {
		renderer::addSubmenu("Water", "water/ocean", [](core* core) {
			core->addOption(toggleOption("Part Water")
				.addToggle(&m_vars.part_water));

			core->addOption(numberOption<float>("Wave Intensity")
				.addNumber(&m_vars.m_wave_intensity).addMin(0).addMax(10).addStep(0.1).setPrecision(1)
				.addClick([] { WATER::SET_DEEP_OCEAN_SCALER(m_vars.m_wave_intensity); }));

			core->addOption(buttonOption("Reset Wave Intensity")
				.addClick([] {WATER::RESET_DEEP_OCEAN_SCALER(); }));

		});
	}

	void water_menu::update() {
		render();

		static bool once = false;
		if (!once) {
			m_vars.m_wave_intensity = WATER::GET_DEEP_OCEAN_SCALER();
			once = true;
		}

		if (m_vars.part_water) {
			float offset[] = { -4, 4 };
			for (int i = 0; i < 5; i++) {
				Vector3 current_coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
				if (i < 2) current_coords.x += offset[(i % 2 == 0)];
				else if (i < 4) current_coords.y += offset[(i % 2 == 0)];
				WATER::MODIFY_WATER({ current_coords.x, current_coords.y }, -500000.0f, 0.2f);
			}
		}
	}
}