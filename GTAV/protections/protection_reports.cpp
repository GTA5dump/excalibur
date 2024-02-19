#include "pch.h"
#include "protection_reports.h"
using namespace base::gui;
using namespace menu::protections::reports::vars;

namespace menu::protections::reports::vars {
	variables m_vars;


}

namespace menu {

	void protections_reports_menu::render() {
		renderer::addSubmenu("Reports", "Protections Reports", [](core* core) {

			core->addOption(scrollOption<const char*, std::size_t>("Game Reports")
				.addScroll(&m_vars.block_reports)
				.setPosition(&m_vars.block_reports_id));

			core->addOption(scrollOption<const char*, std::size_t>("Arxan Reports")
				.addScroll(&m_vars.block_arxan_reports)
				.setPosition(&m_vars.block_arxan_reports_id));
		});

	}

	void protections_reports_menu::update() {
		render();

	}
}