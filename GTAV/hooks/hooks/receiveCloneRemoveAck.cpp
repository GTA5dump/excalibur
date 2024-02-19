#include "pch.h"
#include "hooks/hooks.h"
#include "hooks/patterns.h"
#include "util/caller.h"
#include "rage/engine.h"
#include "rage/classes/NetObject.h"
#include "gui/util/notify.h"
#include "rage/classes/CPed.h"

namespace base::hooks {
	void hooks::receiveCloneRemoveAckHook(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, int32_t object_id, int32_t timestamp) {
		rage::netObject* object = patterns::get_net_object(mgr, object_id, true);

		if (util::is_valid_ptr((*patterns::ped_factory)->m_local_ped)) {
			if (object == (*patterns::ped_factory)->m_local_ped->m_net_object) {
				menu::notify::stacked(std::format("Blocked Sync Remove Crash From {}", src->GetName()).c_str());
				return;
			}
		}

		if (object) {
			if (object->m_object_type == playerObjType) {
				menu::notify::stacked(std::format("{} Tried to ghost", src->GetName()).c_str());
				return;
			}
		}
		patterns::g_syncing_player = src;
		return ogReceiveCloneRemoveAckHook(mgr, src, dst, object_id, timestamp);
	}
}