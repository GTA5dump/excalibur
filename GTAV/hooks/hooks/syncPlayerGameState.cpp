#include "pch.h"
#include "hooks/hooks.h"
#include "hooks/patterns.h"
#include "util/caller.h"
#include "menu/submenus/main/protections/protection_detection.h"
#include "rage/classes/dataNodes.h"

namespace base::hooks {

	bool syncPlayerGameStateHook(uint64_t rcx, CPlayerGameStateDataNode* node) {
		auto _return = ogSyncPlayerGameStateHook(rcx, node);
		auto& var = menu::protections::detection::vars::m_vars;

		if (var.m_godmode) {
			node->m_is_invincible = false;
		}

		if (var.m_spectate) {
			node->m_spectating_net_id = 0;
			node->m_is_spectating = false;
		}

		if (var.m_superjump) {
			node->m_super_jump = false;
		}

		if (var.m_frame_flags) {
			node->m_respawning = false;
		}

		return _return;
	}
}