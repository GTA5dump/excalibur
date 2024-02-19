#include "pch.h"
#include "position.h"
#include "gui/renderer.h"
#include "gui/util/notify.h"
#include "gui/util/panels.h"
using namespace base::gui;

namespace menu {
	void position_menu::render() {
		renderer::addSubmenu("Position", "Settings Position", [](core* core) {
			core->addOption(numberOption<float>("Horizontal Position")
				.addNumber(&renderer::getRenderer()->m_position.x).addMin(0).addMax(1)
				.addStep(0.01f).setPrecision(2));

			core->addOption(numberOption<float>("Vertical Position")
				.addNumber(&renderer::getRenderer()->m_position.y).addMin(0).addMax(1)
				.addStep(0.01f).setPrecision(2));

			core->addOption(numberOption<float>("Vertical Position")
				.addNumber(&renderer::getRenderer()->m_option.m_padding.x).addMin(0).addMax(1)
				.addStep(0.001f).setPrecision(2));

			core->addOption(numberOption<float>("Wrap")
				.addTooltip("Hotkeys Supported. Press F12 to bind. Test test estsetssssssss testestes tse setse tsetes tse test sets etset estset setsetsetests").addNumber(&renderer::getRenderer()->m_wrap).addMin(-1).addMax(1)
				.addStep(0.001f).setPrecision(3));
		});
	}

	void position_menu::update() {
		render();
	}
}