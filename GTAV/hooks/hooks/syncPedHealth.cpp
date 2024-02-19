#include "pch.h"
#include "hooks/hooks.h"
#include "hooks/patterns.h"
#include "util/caller.h"
#include "menu/submenus/main/protections/protection_detection.h"
#include "rage/classes/dataNodes.h"

namespace base::hooks {

	void syncPedHealthHook(uint64_t rcx, uint64_t rdx) {
		ogSyncPedHealthHook(rcx, rdx);
		auto& var = menu::protections::detection::vars::m_vars;

		if (*patterns::ped_factory) {
			CPed* ped = *(CPed**)(rcx - 0x1b0);
			if (ped) {
				if (ped == (*patterns::ped_factory)->m_local_ped) {
					if (var.m_health) {
						if (*(int*)(rdx + 0xC4) > 328) {
							*(int*)(rdx + 0xC4) = 328;
						}
					}

					if (var.m_armor) {
						if (*(int*)(rdx + 0xC8) > 50) {
							*(int*)(rdx + 0xC8) = 50;
						}
						else {
							if ((*(int*)(rdx + 0xC8) % 50) != 0) {
								*(int*)(rdx + 0xC8) = 0;
							}
						}
					}
				}
			}
		}
	}
}