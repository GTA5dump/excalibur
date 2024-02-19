#include "pch.h"
#include "vehicle_tyre_tracks.h"
#include "menu/util/globals.h"
#include "gui/options/option.h"
#include "gui/util/panels.h"
#include "rage/classes/CPed.h"
#include "rage/classes/CPlayerInfo.h"
#include "menu/util/control.h"
#include "menu/util/raycast.h"

#include "rage/classes/vfx.h"
#include "gui/util/rainbow.h"
using namespace base::gui;
using namespace menu::vehicle::tyre_tracks::vars;

namespace menu::vehicle::tyre_tracks::vars {
	variables m_vars;

	void persistent() {
		CWheelVfx* vfx_wheel = patterns::vfx_wheel.first;
		CWheelVfx* vfx_wheel_cache = m_vars.m_cache;

		for (uint32_t i = 0; i < (uint32_t)(patterns::vfx_wheel.second * 4); i++) {
			if (m_vars.m_toggle) {
				vfx_wheel[i].m_type1 = 53;
				vfx_wheel[i].m_type2 = 53;
				vfx_wheel[i].m_type3 = 64;
				vfx_wheel[i].m_type4 = 255;
				vfx_wheel[i].m_unk1 = TRUE;
				vfx_wheel[i].m_unk2 = TRUE;
				vfx_wheel[i].m_unk3 = TRUE;
				vfx_wheel[i].m_unk4 = TRUE;
				vfx_wheel[i].m_pressure_min = -1.f;
				vfx_wheel[i].m_pressure_max = 0.0f;
			}
			else {
				vfx_wheel[i].m_type1 = vfx_wheel_cache[i].m_type1;
				vfx_wheel[i].m_type2 = vfx_wheel_cache[i].m_type2;
				vfx_wheel[i].m_type3 = vfx_wheel_cache[i].m_type3;
				vfx_wheel[i].m_type4 = vfx_wheel_cache[i].m_type4;
				vfx_wheel[i].m_unk1 = vfx_wheel_cache[i].m_unk1;
				vfx_wheel[i].m_unk2 = vfx_wheel_cache[i].m_unk2;
				vfx_wheel[i].m_unk3 = vfx_wheel_cache[i].m_unk3;
				vfx_wheel[i].m_unk4 = vfx_wheel_cache[i].m_unk4;
				vfx_wheel[i].m_pressure_min = vfx_wheel_cache[i].m_pressure_min;
				vfx_wheel[i].m_pressure_max = vfx_wheel_cache[i].m_pressure_max;
			}
		}
	}

	void set_color(bool reset, color color) {
		CWheelVfx* vfx_wheel = patterns::vfx_wheel.first;
		CWheelVfx* vfx_wheel_cache = m_vars.m_cache;

		for (uint32_t i = 0; i < (uint32_t)(patterns::vfx_wheel.second * 4); i++) {
			if (!reset) {
				vfx_wheel[i].m_r = color.r;
				vfx_wheel[i].m_g = color.g;
				vfx_wheel[i].m_b = color.b;
			}
			else {
				vfx_wheel[i].m_r = vfx_wheel_cache[i].m_r;
				vfx_wheel[i].m_g = vfx_wheel_cache[i].m_g;
				vfx_wheel[i].m_b = vfx_wheel_cache[i].m_b;
			}
		}
	}

}

namespace menu {

	void vehicle_tyre_tracks_menu::render() {
		renderer::addSubmenu("Tyre Tracks", "Vehicle Tyre Tracks", [](core* core) {
			const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
			
			core->addOption(toggleOption("Toggle Tracks")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_toggle)
				.addClick(persistent));

			core->addOption(toggleOption("Randomize")
				.addTranslate().addHotkey()
				.addToggle(&m_vars.m_randomize)
				.addClick([] {
					m_vars.m_rainbow.toggle(m_vars.m_randomize);
					if (m_vars.m_randomize) {
						m_vars.m_rainbow.add(&m_vars.m_color);
					}
					else {
						m_vars.m_rainbow.remove(&m_vars.m_color);
						set_color(false, m_vars.m_color);
					}
			}));

			core->addOption(colorOption("Edit Color", m_vars.m_color)
				.setTarget("Edit Tyre Tracks Color"));

			core->addOption(buttonOption("Reset to Default")
				.addClick([] {
					m_vars.m_randomize = false;
					m_vars.m_rainbow.stop();
					set_color(true, color());
			}));
		});

		renderer::addSubmenu("Edit Color", "Edit Tyre Tracks Color", [](core* core) {
			core->addOption(numberOption<int>("[R]ed")
				.addNumber(&m_vars.m_color.r)
				.addMin(0).addMax(255)
				.addClick([]{ set_color(false, m_vars.m_color); }));

			core->addOption(numberOption<int>("[G]reen")
				.addNumber(&m_vars.m_color.g)
				.addMin(0).addMax(255)
				.addClick([] { set_color(false, m_vars.m_color); }));

			core->addOption(numberOption<int>("[B]lue")
				.addNumber(&m_vars.m_color.b)
				.addMin(0).addMax(255)
				.addClick([] { set_color(false, m_vars.m_color); }));

			core->addOption(numberOption<int>("[A]lpha")
				.addNumber(&m_vars.m_color.a)
				.addMin(0).addMax(255)
				.addClick([] { set_color(false, m_vars.m_color); }));
		});
	}

	bool init = false;

	void vehicle_tyre_tracks_menu::update() {
		render();

		if (!init) {
			m_vars.m_cache = (CWheelVfx*)malloc((sizeof(CWheelVfx) * patterns::vfx_wheel.second) * 4);
			memcpy(m_vars.m_cache, patterns::vfx_wheel.first, (sizeof(CWheelVfx) * patterns::vfx_wheel.second) * 4);
			init = true;
		}

		if (m_vars.m_randomize) {
			m_vars.m_rainbow.run();
			set_color(false, m_vars.m_color);
		}
		util::fiber::pool::add([] {
			persistent();
			set_color(false, m_vars.m_color);
		});

		CWheelVfx* vfx_wheel = patterns::vfx_wheel.first;
		CWheelVfx* vfx_wheel_cache = m_vars.m_cache;
		for (uint32_t i = 0; i < (uint32_t)(patterns::vfx_wheel.second * 4); i++) {
			if (m_vars.m_toggle) {
				vfx_wheel[i].m_type1 = 53;
				vfx_wheel[i].m_type2 = 53;
				vfx_wheel[i].m_type3 = 64;
				vfx_wheel[i].m_type4 = 255;
				vfx_wheel[i].m_unk1 = TRUE;
				vfx_wheel[i].m_unk2 = TRUE;
				vfx_wheel[i].m_unk3 = TRUE;
				vfx_wheel[i].m_unk4 = TRUE;
				vfx_wheel[i].m_pressure_min = -1.f;
				vfx_wheel[i].m_pressure_max = 0.0f;

			}
			else {
				vfx_wheel[i].m_type1 = vfx_wheel_cache[i].m_type1;
				vfx_wheel[i].m_type2 = vfx_wheel_cache[i].m_type2;
				vfx_wheel[i].m_type3 = vfx_wheel_cache[i].m_type3;
				vfx_wheel[i].m_type4 = vfx_wheel_cache[i].m_type4;
				vfx_wheel[i].m_unk1 = vfx_wheel_cache[i].m_unk1;
				vfx_wheel[i].m_unk2 = vfx_wheel_cache[i].m_unk2;
				vfx_wheel[i].m_unk3 = vfx_wheel_cache[i].m_unk3;
				vfx_wheel[i].m_unk4 = vfx_wheel_cache[i].m_unk4;
				vfx_wheel[i].m_pressure_min = vfx_wheel_cache[i].m_pressure_min;
				vfx_wheel[i].m_pressure_max = vfx_wheel_cache[i].m_pressure_max;

			}
		}

		set_color(false, m_vars.m_color);

		const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
	}
}