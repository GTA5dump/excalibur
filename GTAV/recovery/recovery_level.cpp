#include "pch.h"
#include "recovery_level.h"
#include "gui/util/timer.h"
#include "rage/engine.h"
#include "menu/util/stats.h"
#include "gui/util/notify.h"
#include "levels.h"
#include <vector>
#include <array>

using namespace base::gui;
using namespace menu::recovery::level::vars;

namespace menu::recovery::level::vars {
	variables m_vars;
	int level_presets[] = { 1, 25, 50, 69, 75, 100, 120, 250, 420, 500, 666, 1000, 1234, 1337, 2000, 4000, 6969, 8000 };


	int get_rp_level() {
		return stats<int>::get("CHAR_SET_RP_GIFT_ADMIN");
	}

	void set_rp_level(int level) {
		if (level > 8000) level = 8000;

		stats<int>::set("CHAR_SET_RP_GIFT_ADMIN", levels::levels[level - 1]);
		menu::notify::stacked("Set Level Change Session For Changes To Take Effect");
	}

	void set_level(int level) {
		set_rp_level(level);
	}

	int get_level() {
		get_rp_level();
	}

	static bool active = false;
	void set_level_keyboard() {
		MISC::DISPLAY_ONSCREEN_KEYBOARD(true, (char*)"Input", (char*)"", (char*)"", (char*)"", (char*)"", (char*)"", 20);
		while (MISC::UPDATE_ONSCREEN_KEYBOARD() == 0) {
			active = true;
			renderer::getRenderer()->reset_keys();
			util::fiber::go_to_main();
		}
		active = false;
		if (!MISC::GET_ONSCREEN_KEYBOARD_RESULT())
			return;
		set_level(std::atoi(MISC::GET_ONSCREEN_KEYBOARD_RESULT()));
	}
}

namespace menu {

	void recovery_level_menu::render() {
		renderer::addSubmenu("Level", "Recovery Level", [](core* core) {
			core->addOption(keyboardOption("Input Level")
				.addClick(set_level_keyboard));

			core->addOption(breakOption("Presets"));

			for (int level : level_presets) {
				core->addOption(buttonOption(std::to_string(level).c_str())
					.addClick([=] { set_level(level); }));
			}

		});

	}

	void recovery_level_menu::update() {
		render();

	}
}