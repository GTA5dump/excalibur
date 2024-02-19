#include "pch.h"
#include "blackhole.h"
#include "menu/util/control.h"

using namespace base::gui;
using namespace menu::world::blackhole::vars;

namespace menu::world::blackhole::vars {
	variables m_vars;



}

namespace menu {

	void blackhole_menu::render() {
		renderer::addSubmenu("Blackhole", "black_hole", [](core* core) {
			core->addOption(toggleOption("Toggle")
				.addToggle(&m_vars.black_hole));

			core->addOption(toggleOption("Include Vehicles")
				.addToggle(&m_vars.include_vehicles));

			core->addOption(toggleOption("Include Peds")
				.addToggle(&m_vars.include_peds));

			const auto me = (*patterns::ped_factory)->m_local_ped->get_position();

			core->addOption(buttonOption("Set at my Position")
				.addClick([=] { m_vars.m_blackhole_pos.x = me->x; m_vars.m_blackhole_pos.y = me->y; m_vars.m_blackhole_pos.z = me->z; }));

			core->addOption(numberOption<float>("X")
				.addNumber(&m_vars.m_blackhole_pos.x).addMin(0).addMax(10000).addStep(10).setPrecision(0));

			core->addOption(numberOption<float>("Y")
				.addNumber(&m_vars.m_blackhole_pos.y).addMin(0).addMax(10000).addStep(10).setPrecision(0));

			core->addOption(numberOption<float>("Z")
				.addNumber(&m_vars.m_blackhole_pos.z).addMin(0).addMax(10000).addStep(10).setPrecision(0));
		
		});
	}

	void blackhole_menu::update() {
		render();

		if (m_vars.black_hole) {
			for (auto entity : control::get_entities(m_vars.include_vehicles, m_vars.include_peds)) {
				if (control::request_control(entity, 0)) {
					auto entity_coord = ENTITY::GET_ENTITY_COORDS(entity, false);
					ENTITY::APPLY_FORCE_TO_ENTITY(entity, 1, { ((m_vars.m_blackhole_pos.x - entity_coord.x) * 9.f), ((m_vars.m_blackhole_pos.y - entity_coord.y) * 9.f), ((m_vars.m_blackhole_pos.z - entity_coord.z) * 9.f) }, { 0.f, 0.f, 0.f }, 0, false, true, true, 0, 0);
				}
			}
			GRAPHICS::DRAW_MARKER(28, { m_vars.m_blackhole_pos.x, m_vars.m_blackhole_pos.y, m_vars.m_blackhole_pos.z }, { 0.f, 0.f ,  0.f }, { 0, 0, 0 }, { 5.f, 5.f, 5.f }, 0 * 255, 0 * 255, 0 * 255, 255, 0, 0, 0, 0, 0, 0, 0);
		}
	}
}