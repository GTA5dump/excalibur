#include "pch.h"
#include "color.h"
#include "gui/renderer.h"
#include "rage/classes/joaat.h"
#include "util/log.h"
#include "gui/util/fonts.h"
#include "gui/util/texture.h"
#include "gui/util/panels.h"
#include "gui/util/notify.h"

using namespace base::gui;

namespace menu {

	void color_menu::render() {

		renderer::addSubmenu("Color", "Settings Color", [](core* core) {
			core->addOption(colorOption("Header Color", renderer::getRenderer()->m_header.m_color)
				.setTarget("Header Color"));

			core->addOption(colorOption("Header Text Color", renderer::getRenderer()->m_header.m_text_color)
				.setTarget("Header Text Color"));

			core->addOption(colorOption("Title Color", renderer::getRenderer()->m_title.m_color)
				.setTarget("Title Color"));

			core->addOption(colorOption("Title Text Color", renderer::getRenderer()->m_title.m_text_color)
				.setTarget("Title Text Color"));

			core->addOption(colorOption("Background Color", renderer::getRenderer()->m_option.m_color)
				.setTarget("Background Color"));

			core->addOption(colorOption("Scroller Color", renderer::getRenderer()->m_scroller_color)
				.setTarget("Scroller Color"));

			core->addOption(colorOption("Scroller Text Color", renderer::getRenderer()->m_option.m_color)
				.setTarget("Scroller Text Color"));

			core->addOption(colorOption("Scroller Selected Text Color", renderer::getRenderer()->m_option.m_selected_text_color)
				.setTarget("Scroller Text Color"));

			core->addOption(colorOption("Footer Color", renderer::getRenderer()->m_footer.m_color)
				.setTarget("Footer Color"));

			core->addOption(colorOption("Footer Text Color", renderer::getRenderer()->m_footer.m_text_color)
				.setTarget("Footer Text Color"));
		});

		renderer::addSubmenu("Footer Color", "Footer Color", [](core* core) {
			core->addOption(numberOption<int>("[R]ed")
				.addNumber(&renderer::getRenderer()->m_footer.m_color.r)
				.addMin(0).addMax(255));

			core->addOption(numberOption<int>("[G]reen")
				.addNumber(&renderer::getRenderer()->m_footer.m_color.g)
				.addMin(0).addMax(255));

			core->addOption(numberOption<int>("[B]lue")
				.addNumber(&renderer::getRenderer()->m_footer.m_color.b)
				.addMin(0).addMax(255));
		});

		renderer::addSubmenu("Scroller Color", "Scroller Color", [](core* core) {
			core->addOption(numberOption<int>("[R]ed")
				.addNumber(&renderer::getRenderer()->m_scroller_color.r)
				.addMin(0).addMax(255));

			core->addOption(numberOption<int>("[G]reen")
				.addNumber(&renderer::getRenderer()->m_scroller_color.g)
				.addMin(0).addMax(255));

			core->addOption(numberOption<int>("[B]lue")
				.addNumber(&renderer::getRenderer()->m_scroller_color.b)
				.addMin(0).addMax(255));
		});

		renderer::addSubmenu("Background Color", "Background Color", [](core* core) {
			core->addOption(numberOption<int>("[R]ed")
				.addNumber(&renderer::getRenderer()->m_option.m_color.r)
				.addMin(0).addMax(255));

			core->addOption(numberOption<int>("[G]reen")
				.addNumber(&renderer::getRenderer()->m_option.m_color.g)
				.addMin(0).addMax(255));

			core->addOption(numberOption<int>("[B]lue")
				.addNumber(&renderer::getRenderer()->m_option.m_color.b)
				.addMin(0).addMax(255));
		});

		renderer::addSubmenu("Title Color", "Title Color", [](core* core) {
			core->addOption(numberOption<int>("[R]ed")
				.addNumber(&renderer::getRenderer()->m_title.m_color.r)
				.addMin(0).addMax(255));

			core->addOption(numberOption<int>("[G]reen")
				.addNumber(&renderer::getRenderer()->m_title.m_color.g)
				.addMin(0).addMax(255));

			core->addOption(numberOption<int>("[B]lue")
				.addNumber(&renderer::getRenderer()->m_title.m_color.b)
				.addMin(0).addMax(255));
		});

		renderer::addSubmenu("Header Color", "Header Color", [](core* core) {
			core->addOption(numberOption<int>("[R]ed")
				.addNumber(&renderer::getRenderer()->m_header.m_color.r)
				.addMin(0).addMax(255));

			core->addOption(numberOption<int>("[G]reen")
				.addNumber(&renderer::getRenderer()->m_header.m_color.g)
				.addMin(0).addMax(255));

			core->addOption(numberOption<int>("[B]lue")
				.addNumber(&renderer::getRenderer()->m_header.m_color.b)
				.addMin(0).addMax(255));
		});

	}

	void color_menu::update() {
		render();
	}
}