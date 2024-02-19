#include "pch.h"
#include "hooks/hooks.h"
#include "hooks/patterns.h"
#include "util/caller.h"
#include "rage/engine.h"
#include "rage/classes/NetObject.h"
#include "rage/classes/dataNodes.h"
#include "gui/util/notify.h"
#include "menu/util/helpers.h"
#include "menu/submenus/main/protections/protections_entity.h"
#include "menu/submenus/main/protections/protection_syncs.h"
namespace base::hooks {
	int hooks::receiveCloneSyncHook(CNetworkObjectMgr* mgr, CNetGamePlayer* src, CNetGamePlayer* dst, eNetObjType object_type, uint16_t object_id, rage::datBitBuffer* buffer, uint16_t unk, uint32_t timestamp) {
	
		if (object_type < eNetObjType::NET_OBJ_TYPE_AUTOMOBILE || object_type > eNetObjType::NET_OBJ_TYPE_TRAIN)
		{
			menu::notify::stacked(std::format("blocked sync crash from {}", src->GetName()).c_str());
			return 1;
		}

		if (auto net_obj = patterns::get_net_object(mgr, object_id, true); net_obj && net_obj->m_object_type != (int16_t)object_type)
		{
			menu::notify::stacked(std::format("blocked quantum crash from {}", src->GetName()).c_str());
			return 1;
		}

		g_alignment_tests["RCS"].m_block = false;
		g_alignment_tests["RCS"].m_monitor = true;
		g_alignment_tests["RCS"].m_thread_id = GetCurrentThreadId();

		g_alignment_tests["RCS"].m_monitor = false;
		if (g_alignment_tests["RCS"].m_block) {
			menu::notify::stacked(std::format("RCS blocked node crash from {}", src->GetName()).c_str());
			return 69;
		}

		if (menu::protections::syncs::vars::m_vars.block_incoming_syncs) {
			return 1;
		}

		auto& var = menu::protections::entity::vars::m_vars;

		if (var.entity_type_pos == 0) {
			if (object_type == eNetObjType::NET_OBJ_TYPE_AUTOMOBILE && var.m_sync_car) {
				return 1;
			}
			if (object_type == eNetObjType::NET_OBJ_TYPE_BIKE && var.m_sync_bike) {
				return 1;
			}
			if (object_type == eNetObjType::NET_OBJ_TYPE_BOAT && var.m_sync_boat) {
				return 1;
			}
			if (object_type == eNetObjType::NET_OBJ_TYPE_DOOR && var.m_sync_door) {
				return  1;
			}
			if (object_type == eNetObjType::NET_OBJ_TYPE_HELI && var.m_sync_heli) {
				return 1;
			}
			if (object_type == eNetObjType::NET_OBJ_TYPE_OBJECT && var.m_sync_object) {
				return 1;
			}
			if (object_type == eNetObjType::NET_OBJ_TYPE_PICKUP && var.m_sync_pickup) {
				return 1;
			}
			if (object_type == eNetObjType::NET_OBJ_TYPE_PICKUP_PLACEMENT && var.m_sync_pickup_placement) {
				return 1;
			}
			if (object_type == eNetObjType::NET_OBJ_TYPE_PLANE && var.m_sync_plane) {
				return 1;
			}
			if (object_type == eNetObjType::NET_OBJ_TYPE_PLAYER && var.m_sync_player) {
				return 1;
			}
			if (object_type == eNetObjType::NET_OBJ_TYPE_PED && var.m_sync_ped) {
				return 1;
			}
			if (object_type == eNetObjType::NET_OBJ_TYPE_SUBMARINE && var.m_sync_sub) {
				return 1;
			}
			if (object_type == eNetObjType::NET_OBJ_TYPE_TRAIN && var.m_sync_train) {
				return 1;
			}
			if (object_type == eNetObjType::NET_OBJ_TYPE_TRAILER && var.m_sync_trailer) {
				return 1;
			}

		}

		patterns::g_syncing_object_type = object_type;
		patterns::g_syncing_player = src;
		return ogReceiveCloneSyncHook(mgr, src, dst, object_type, object_id, buffer, unk, timestamp);
	}
}