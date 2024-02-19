#include "pch.h"
#include "settings.h"
#include "gui/renderer.h"
#include "util/log.h"
#include "settings/position.h"
#include "settings/color.h"
#include "settings/hotkeys.h"
#include "util/dirs.h"
using namespace base::gui;
using namespace menu::settings::vars;

namespace menu::settings::vars {
	variables m_vars;
	static bool active = false;
	void save_theme() {
		MISC::DISPLAY_ONSCREEN_KEYBOARD(true, (char*)"Input", (char*)"", (char*)"", (char*)"", (char*)"", (char*)"", 20);
		while (MISC::UPDATE_ONSCREEN_KEYBOARD() == 0) {
			active = true;
			renderer::getRenderer()->reset_keys();
			util::fiber::go_to_main();
		}
		active = false;
		if (!MISC::GET_ONSCREEN_KEYBOARD_RESULT())
			return;
		m_vars.theme_to_save = MISC::GET_ONSCREEN_KEYBOARD_RESULT();
		renderer::getRenderer()->save_theme(m_vars.theme_to_save);
	}
}

namespace menu {

	void settings_menu::render() {
		renderer::addSubmenu("Settings", "Settings", [](core* core) {
			core->addOption(submenuOption("Themes")
				.addTranslate()
				.setTarget("settings_themes"));

			core->addOption(submenuOption("Hotkeys")
				.addTranslate()
				.setTarget("Hotkeys"));

			core->addOption(submenuOption("Position")
				.addTranslate()
				.setTarget("Settings Position"));

			core->addOption(submenuOption("Color")
				.addTranslate()
				.setTarget("Settings Color"));

			core->addOption(numberOption<std::size_t>("Page Length")
				.addNumber(&renderer::getRenderer()->m_max_vis_options).addMin(0).addMax(20));

			core->addOption(toggleOption("Smooth Scroll")
				.addToggle(&renderer::getRenderer()->m_smooth_scroll));

			core->addOption(toggleOption("Auto Save Settings")
				.addToggle(&m_vars.m_auto_save));

			core->addOption(buttonOption("Unload")
				.addTranslate()
				.addClick([] { g_running = false; }));
		});

		renderer::addSubmenu("Themes", "settings_themes", [](core* core) {
			core->addOption(keyboardOption("Save Theme")
				.addClick([] { save_theme(); }).addRightText(m_vars.theme_to_save));

			core->addOption(buttonOption("Reset to Default")
				.addClick([] { renderer::getRenderer()->reset_theme(); }));

			core->addOption(breakOption("Themes"));
			renderer::getRenderer()->m_cached_themes.clear();
			std::vector<std::string> themes = util::dirs::get_files_in_directory(util::dirs::get_path(theme), ".json");
			if (themes.size()) {
				for (std::string theme : themes) {
					std::size_t index = renderer::getRenderer()->m_cached_themes.size();
					if (index < 0) index = 0;
					renderer::getRenderer()->m_cached_themes.push_back(theme);


					core->addOption(submenuOption(theme.c_str())
						.setTarget("selected_theme").addClick([=] { m_vars.m_selected_theme = index; }));
				}
			}
			else {
				core->addOption(buttonOption("~c~Empty"));
			}
				});
			renderer::addSubmenu("Themes", "selected_theme", [](core* core) {
				core->addOption(buttonOption("Load")
					.addClick([] { util::fiber::pool::add([] {  renderer::getRenderer()->load_theme(renderer::getRenderer()->m_cached_themes[m_vars.m_selected_theme].c_str());  }); }));

				core->addOption(buttonOption("Delete")
					.addClick([=] { std::filesystem::remove(std::format("{}{}.json", util::dirs::get_path(theme), renderer::getRenderer()->m_cached_themes[m_vars.m_selected_theme].c_str())); }));

				});
	}

	

	void settings_menu::update() {
		render();
		getPositionMenu()->update();
		getColorMenu()->update();
		getHotkeysMenu()->update();
	}
}