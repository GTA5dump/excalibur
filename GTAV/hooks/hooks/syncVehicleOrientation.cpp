#include "pch.h"
#include "hooks/hooks.h"
#include "hooks/patterns.h"
#include "util/caller.h"
#include "menu/submenus/main/network/network_spoofing.h"
#include "rage/classes/CPed.h"

namespace base::hooks {
	void syncVehicleOrientationHook(uint64_t rcx, uint64_t* rdx) {
		auto& var = menu::network::spoofing::vars::m_vars;
		struct orientation {
			char _0x0000[0xC0];
			math::matrix<float> m_transform;
		}; orientation* _orientation = (orientation*)rcx;

		uint64_t entity = 0;
		if (entity) {
			memcpy(&_orientation->m_transform, (math::matrix<float>*)(entity + 0x60), sizeof(_orientation->m_transform));
		}
		else {
			memset(&_orientation->m_transform, 0, sizeof(_orientation->m_transform));
			_orientation->m_transform.m_elements[0][0] = 1.f;
			_orientation->m_transform.m_elements[1][1] = 1.f;
			_orientation->m_transform.m_elements[2][2] = 1.f;
		}
		if (var.m_vehicle_spinbot || var.m_vehicle_static || var.m_vehicle_jitter) {
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) {
				if (patterns::ped_factory) {
					if ((*patterns::ped_factory)->m_local_ped) {
						if ((uint64_t)(*patterns::ped_factory)->m_local_ped->m_vehicle == entity) {
							rage::engine::handle_rotation_values_from_order(&_orientation->m_transform, &var.m_vehicle_hook_value, 2);
							return;
						}
					}
				}
			}
		}

		ogsyncVehicleOrientationHook(rcx, rdx);
	}
}