#include "pch.h"
#include "hooks/hooks.h"
#include "hooks/patterns.h"
#include "util/caller.h"
#include "rage/engine.h"
#include "rage/classes/NetObject.h"
#include "gui/util/notify.h"
#include "menu/util/helpers.h"

namespace base::hooks {
	bool hooks::canApplyDataHook(rage::netSyncTree* tree, rage::netObject* object) {

		g_alignment_tests["CAD"].m_block = false;
		g_alignment_tests["CAD"].m_monitor = true;
		g_alignment_tests["CAD"].m_thread_id = GetCurrentThreadId();

		static bool init = ([] { menu::helpers::sync_node_finder::init(); }(), true);

		if (tree->m_child_node_count && tree->m_next_sync_node && menu::helpers::check_node(tree->m_next_sync_node, patterns::g_syncing_player, object))
		{
			return false;
		}

		g_alignment_tests["CAD"].m_monitor = false;
		if (g_alignment_tests["CAD"].m_block) {
			menu::notify::stacked(std::format("CAD blocked node crash from {}", patterns::g_syncing_player->GetName()).c_str());
			return 69;
		}

		return ogCanApplyDataHook(tree, object);
	}
}