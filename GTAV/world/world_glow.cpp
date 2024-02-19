#include "pch.h"
#include "world_glow.h"
#include "menu/util/control.h"

using namespace base::gui;
using namespace menu::world::glow::vars;

namespace menu::world::glow::vars {
	variables m_vars;


	void world_rgb() {
		if (m_vars.worldr > 0 && m_vars.worldb == 0) {
			m_vars.worldr--;
			m_vars.worldg++;
		}
		if (m_vars.worldg > 0 && m_vars.worldr == 0) {
			m_vars.worldg--;
			m_vars.worldb++;
		}
		if (m_vars.worldb > 0 && m_vars.worldg == 0) {
			m_vars.worldr++;
			m_vars.worldb--;
		}
	}
}

namespace menu {

	void world_glow_menu::render() {
		renderer::addSubmenu("Aesthtic Lights", "world_glow", [](core* core) {
			core->addOption(toggleOption("Toggle")
				.addToggle(&m_vars.world_glow));

			core->addOption(toggleOption("Rainbow")
				.addToggle(&m_vars.world_rainbow));

			core->addOption(breakOption("Colors"));

			core->addOption(numberOption<float>("Intensity")
				.addNumber(&m_vars.world_intensity)
				.addMin(0).addMax(255)
				.addStep(1).setPrecision(0));

			core->addOption(numberOption<int>("[R]ed")
				.addNumber(&m_vars.worldr)
				.addMin(0).addMax(255)
				.addStep(1).setPrecision(0));

			core->addOption(numberOption<int>("[G]reen")
				.addNumber(&m_vars.worldg)
				.addMin(0).addMax(255)
				.addStep(1).setPrecision(0));

			core->addOption(numberOption<int>("[B]lue")
				.addNumber(&m_vars.worldb)
				.addMin(0).addMax(255)
				.addStep(1).setPrecision(0));
		});
	}

	void world_glow_menu::update() {
		render();
		if (m_vars.world_glow) {
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
			if (m_vars.world_rainbow) {
				world_rgb();
				GRAPHICS::DRAW_LIGHT_WITH_RANGE(coords, m_vars.worldr, m_vars.worldg, m_vars.worldb, 1000, m_vars.world_intensity);
			}
			else {
				GRAPHICS::DRAW_LIGHT_WITH_RANGE(coords, m_vars.worldr, m_vars.worldg, m_vars.worldb, 1000, m_vars.world_intensity);
			}
		}
	
	}
}