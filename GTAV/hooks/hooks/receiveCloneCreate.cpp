#include "pch.h"
#include "hooks/hooks.h"
#include "hooks/patterns.h"
#include "util/caller.h"
#include "rage/engine.h"
#include "rage/classes/NetObject.h"
#include "gui/util/notify.h"

#include "menu/submenus/main/protections/protections_entity.h"
namespace base::hooks {
	bool hooks::receiveCloneCreateHook(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, eNetObjType object_type, int32_t object_id, int32_t object_flag, rage::datBitBuffer* buffer, int32_t timestamp) {

		if (object_type < eNetObjType::NET_OBJ_TYPE_AUTOMOBILE || object_type > eNetObjType::NET_OBJ_TYPE_TRAIN) {
			menu::notify::stacked(std::format("blocked quantum crash from {}", src->GetName()).c_str());
			return true;
		}

		g_alignment_tests["RCC"].m_block = false;
		g_alignment_tests["RCC"].m_monitor = true;
		g_alignment_tests["RCC"].m_thread_id = GetCurrentThreadId();

		g_alignment_tests["RCC"].m_monitor = false;
		if (g_alignment_tests["RCC"].m_block) {
			menu::notify::stacked(std::format("RCC blocked node crash from {}", src->GetName()).c_str());
			return 69;
		}

		auto& var = menu::protections::entity::vars::m_vars;

		if (var.entity_type_pos == 1) {
			if (object_type == eNetObjType::NET_OBJ_TYPE_AUTOMOBILE && var.m_car) {
				return false;
			}
			if (object_type == eNetObjType::NET_OBJ_TYPE_BIKE && var.m_bike) {
				return false;
			}
			if (object_type == eNetObjType::NET_OBJ_TYPE_BOAT && var.m_boat) {
				return false;
			}
			if (object_type == eNetObjType::NET_OBJ_TYPE_DOOR && var.m_door) {
				return false;
			}
			if (object_type == eNetObjType::NET_OBJ_TYPE_HELI && var.m_heli) {
				return false;
			}
			if (object_type == eNetObjType::NET_OBJ_TYPE_OBJECT && var.m_object) {
				return false;
			}
			if (object_type == eNetObjType::NET_OBJ_TYPE_PICKUP && var.m_pickup) {
				return false;
			}
			if (object_type == eNetObjType::NET_OBJ_TYPE_PICKUP_PLACEMENT && var.m_pickup_placement) {
				return false;
			}
			if (object_type == eNetObjType::NET_OBJ_TYPE_PLANE && var.m_plane) {
				return false;
			}
			if (object_type == eNetObjType::NET_OBJ_TYPE_PLAYER && var.m_player) {
				return false;
			}
			if (object_type == eNetObjType::NET_OBJ_TYPE_PED && var.m_ped) {
				return false;
			}
			if (object_type == eNetObjType::NET_OBJ_TYPE_SUBMARINE && var.m_sub) {
				return false;
			}
			if (object_type == eNetObjType::NET_OBJ_TYPE_TRAIN && var.m_train) {
				return false;
			}
			if (object_type == eNetObjType::NET_OBJ_TYPE_TRAILER && var.m_trailer) {
				return false;
			}

		}
		patterns::g_syncing_object_type = object_type;
		patterns::g_syncing_player = src;
		return ogReceiveCloneCreateHook(mgr, src, dst, object_type, object_id, object_flag, buffer, timestamp);
	}
}