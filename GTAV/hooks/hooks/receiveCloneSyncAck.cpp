#include "pch.h"
#include "hooks/hooks.h"
#include "hooks/patterns.h"
#include "util/caller.h"
#include "rage/engine.h"
#include "rage/classes/NetObject.h"
#include "gui/util/notify.h"

#include "menu/submenus/main/protections/protections_entity.h"
namespace base::hooks {

	bool IsNetworkObjectOwner(CNetGamePlayer* src, rage::netObject* netObject) {
		return src != nullptr && netObject != nullptr && src->m_player_id != -1 && (src->m_player_id == netObject->m_owner_id || src->m_player_id == netObject->m_next_owner_id);
	}

	void hooks::receiveCloneSyncAckHook(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, rage::datBitBuffer* buffer, uint16_t object_id, int32_t ack_code) {

		rage::netObject* netObject = patterns::get_net_object(mgr, object_id, true);
		int16_t object_type = netObject == nullptr ? -1 : netObject->m_object_type;

		if (object_type < (int16_t)eNetObjType::NET_OBJ_TYPE_AUTOMOBILE || object_type >(int16_t)eNetObjType::NET_OBJ_TYPE_TRAIN) {
			menu::notify::stacked(std::format("blocked quantum crash from {}", src->GetName()).c_str());
			return;
		}

		if (!IsNetworkObjectOwner(dst, netObject)) {
			menu::notify::stacked(std::format("{} tried to change owner id", src->GetName()).c_str());
			return;
		}

		patterns::g_syncing_player = src;
		return ogReceiveCloneSyncAckHook(mgr, src, dst, buffer, object_id, ack_code);
	}
}