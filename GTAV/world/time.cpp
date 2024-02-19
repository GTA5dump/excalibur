#include "pch.h"
#include "time.h"
#include "menu/util/control.h"

using namespace base::gui;
using namespace menu::world::time::vars;

namespace menu::world::time::vars {
	variables m_vars;



}

namespace menu {

	void time_menu::render() {
		renderer::addSubmenu("Time", "time", [](core* core) {
			static int H = 0, M = 0, S = 0;

			core->addOption(toggleOption("Always Day")
				.addToggle(&m_vars.always_day));

			core->addOption(toggleOption("Always Night")
				.addToggle(&m_vars.always_night));

			core->addOption(toggleOption("Freeze Time")
				.addToggle(&m_vars.freeze_time));

			core->addOption(toggleOption("Sync with System Time")
				.addToggle(&m_vars.sync_time));

			core->addOption(numberOption<int>("Hour")
				.addNumber(&H).addMin(0).addMax(24).addStep(1)
				.addClick([] { NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(H, M, S); }));

			core->addOption(numberOption<int>("Minute")
				.addNumber(&M).addMin(0).addMax(24).addStep(1)
				.addClick([] { NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(H, M, S); }));

			core->addOption(numberOption<int>("Second")
				.addNumber(&S).addMin(0).addMax(24).addStep(1)
				.addClick([] { NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(H, M, S); }));
		});
	}

	void time_menu::update() {
		render();

		if (m_vars.sync_time) {
			time_t now = time(0);
			tm t;
			localtime_s(&t, &now);
			CLOCK::SET_CLOCK_TIME(t.tm_hour, t.tm_min, t.tm_sec);
		}
		if (m_vars.freeze_time) {
			CLOCK::PAUSE_CLOCK(true);
		}
		else {
			CLOCK::PAUSE_CLOCK(false);
		}
		if (m_vars.always_day) {
			NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(15, 0, 0);
		}
		if (m_vars.always_night) {
			NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(1, 0, 0);
		}

		if (m_vars.always_day == true)
			m_vars.always_night = false;

		if (m_vars.always_night == true)
			m_vars.always_day = false;
	}
}