#include "pch.h"
#include "vehicle_modifiers.h"
#include "menu/util/globals.h"
#include "gui/options/option.h"
#include "gui/util/panels.h"
#include "rage/classes/CPed.h"
#include "rage/classes/CPlayerInfo.h"
#include "menu/util/control.h"
#include "menu/util/raycast.h"
#include "rage/classes/vfx.h"

using namespace base::gui;
using namespace menu::vehicle::modifiers::vars;

namespace menu::vehicle::modifiers::vars {
	variables m_vars;

	void set_tire_scale() {
		if (patterns::ped_factory) {
			if ((*patterns::ped_factory)->m_local_ped) {
				if ((*patterns::ped_factory)->m_local_ped->m_vehicle) {
					CVehicle* veh = (*patterns::ped_factory)->m_local_ped->m_vehicle;
					if (veh->m_draw_data) {
						if (veh->m_draw_data->m_vehicle_stream_render) {
							veh->m_draw_data->m_vehicle_stream_render->m_tire_height = m_vars.m_height;
						}
					}
				}
			}
		}
	}

	void set_tire_width() {
		if (patterns::ped_factory) {
			if ((*patterns::ped_factory)->m_local_ped) {
				if ((*patterns::ped_factory)->m_local_ped->m_vehicle) {
					CVehicle* veh = (*patterns::ped_factory)->m_local_ped->m_vehicle;
					if (veh->m_draw_data) {
						if (veh->m_draw_data->m_vehicle_stream_render) {
							veh->m_draw_data->m_vehicle_stream_render->m_tire_width = m_vars.m_width;
						}
					}
				}
			}
		}
	}
}

namespace menu {

	void vehicle_modifiers_menu::render() {
		renderer::addSubmenu("Vehicle Modifiers", "Vehicle Modifiers", [](core* core) {
			const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

			core->addOption(numberOption<float>("Height")
				.addNumber(&m_vars.m_height)
				.addMin(0).addMax(10).setPrecision(1).addStep(0.1f)
				.addClick(set_tire_scale));

			core->addOption(numberOption<float>("Width")
				.addNumber(&m_vars.m_width)
				.addMin(0).addMax(10).setPrecision(1).addStep(0.1f)
				.addClick(set_tire_width));

			core->addOption(numberOption<float>("Scale")
				.addNumber(&m_vars.m_scale)
				.addMin(0).addMax(10).setPrecision(1).addStep(0.1f));
			});
	}

	void vehicle_modifiers_menu::update() {
		render();

		const auto vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);

		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) {
			uint64_t address = rage::engine::get_entity_address(vehicle);
			if (address) {
				if (patterns::ped_factory) {
					if ((*patterns::ped_factory)->m_local_ped) {
						if ((*patterns::ped_factory)->m_local_ped->m_vehicle) {
							CVehicle* veh = (*patterns::ped_factory)->m_local_ped->m_vehicle;
							if (veh->m_draw_data) {
								if (veh->m_draw_data->m_vehicle_stream_render) {
									m_vars.m_toggle = true;
									m_vars.m_height = veh->m_draw_data->m_vehicle_stream_render->m_tire_height;
									m_vars.m_width = veh->m_draw_data->m_vehicle_stream_render->m_tire_width;
								}
							}
						}
					}
				}
			}
		}
	}
}