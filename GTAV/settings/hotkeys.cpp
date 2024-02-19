#include "pch.h"
#include "hotkeys.h"
#include "gui/renderer.h"
#include "gui/util/notify.h"
#include "gui/util/panels.h"
using namespace base::gui;

namespace menu {
	void hotkeys_menu::render() {
		renderer::addSubmenu("Hotkeys", "Hotkeys", [](core* core) {
			core->addOption(buttonOption("Save")
				.addClick([] { renderer::getRenderer()->save_hotkeys(); }));

			core->addOption(buttonOption("Reload")
				.addClick([] { renderer::getRenderer()->load_hotkeys(); }));

			core->addOption(breakOption("Hotkeys"));

			if (!renderer::getRenderer()->m_bool_hotkeys.empty()) {
				for (auto pair : renderer::getRenderer()->m_bool_hotkeys) {
					std::string display = std::format("{}({})", g_key_names[pair.second.m_key], pair.second.m_name);
					core->addOption(buttonOption(display.c_str()));
				}
			}
			else {
				core->addOption(buttonOption("~c~Empty"));
			}
		});
	}

	void hotkeys_menu::update() {
		render();
	}
}