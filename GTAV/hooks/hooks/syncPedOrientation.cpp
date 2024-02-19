#include "pch.h"
#include "hooks/hooks.h"
#include "hooks/patterns.h"
#include "util/caller.h"
#include "menu/submenus/main/network/network_spoofing.h"

namespace base::hooks {
	//v26 momento :)
	void syncPedOrientationHook(uint64_t rcx, uint64_t rdx) {
		auto& var = menu::network::spoofing::vars::m_vars;
		if (var.m_ped_spinbot) {
			if (rcx) {
				if (patterns::ped_factory) {
					CPed* ped = *(CPed**)(rcx - 0x1B0);
					if (ped == (*patterns::ped_factory)->m_local_ped) {
						if (var.m_ped_spinbot) {
							if (var.m_ped_spinbot || var.m_ped_jitter) {
								*(bool*)(rdx + 0xC1) = true;
								*(bool*)(rdx + 0xC2) = true;
								*(float*)(rdx + 0xC4) = var.m_ped_hook_value.x;
								*(float*)(rdx + 0xC8) = var.m_ped_hook_value.y;
								return;
							}

							if (var.m_ped_face_direction) {
								float Val = 0.f;

								switch (var.m_ped_face_direction_val) {
								case 0: Val = -90.f; break;
								case 1: Val = 90.f; break;
								case 2: Val = 180.f; break;
								}

								if (var.m_ped_relative) {
									Val += ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
								}

								if (Val > 180.f) Val = -180.f + (Val - 180.f);

								*(bool*)(rdx + 0xC1) = true;
								*(bool*)(rdx + 0xC2) = true;
								*(float*)(rdx + 0xC4) = Val * 0.0174532924f;
								*(float*)(rdx + 0xC8) = Val * 0.0174532924f;
							}

							return;
						}
					}
				}
			}
		}
		ogSyncPedOrientationHook(rcx, rdx);
	}

}