#include "pch.h"
#include "paint_gun.h"
#include "rage/invoker/natives.h"
#include "rage/engine.h"
#include "util/util.h"


using namespace base::gui;
using namespace menu::weapon::paint_gun::vars;

namespace menu::weapon::paint_gun::vars {
	variables m_vars;
}

namespace menu {
	void paint_gun_menu::render() {
		renderer::addSubmenu("Paint Gun", "Paint Gun", [](core* core) {
			core->addOption(toggleOption("Toggle Paint Gun")
				.addToggle(&m_vars.m_toggle));

			core->addOption(numberOption<float>("Range")
				.addNumber(&m_vars.m_range).addMin(0).addMax(1000)
				.addStep(0.01).setPrecision(2));

			core->addOption(numberOption<float>("Intensity")
				.addNumber(&m_vars.m_intensity).addMin(0).addMax(1000)
				.addStep(1).setPrecision(0));

			core->addOption(colorOption("Edit Color", m_vars.m_color)
				.setTarget("Edit Paint Color"));
		});

		renderer::addSubmenu("Edit Color", "Edit Paint Color", [](core* core) {
			core->addOption(numberOption<int>("[R]ed")
				.addNumber(&m_vars.m_color.r)
				.addMin(0).addMax(255));

			core->addOption(numberOption<int>("[G]reen")
				.addNumber(&m_vars.m_color.g)
				.addMin(0).addMax(255));

			core->addOption(numberOption<int>("[B]lue")
				.addNumber(&m_vars.m_color.b)
				.addMin(0).addMax(255));

			core->addOption(numberOption<int>("[A]lpha")
				.addNumber(&m_vars.m_color.a)
				.addMin(0).addMax(255));
		});

	}

	void paint_gun_menu::update() {
		render();

		if (m_vars.m_toggle) {
			static std::vector<Vector3> a;
			Vector3 b;
			if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &b)); {
				a.push_back(b);
			}
			for (auto pos : a) {
				GRAPHICS::DRAW_LIGHT_WITH_RANGE(pos, m_vars.m_color.r, m_vars.m_color.g, m_vars.m_color.b, m_vars.m_range, m_vars.m_intensity);

			}
		}
	}
}