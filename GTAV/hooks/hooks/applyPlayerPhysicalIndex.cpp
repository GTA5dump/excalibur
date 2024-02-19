#include "pch.h"
#include "hooks/hooks.h"
#include "gui/util/notify.h"
namespace base::hooks {

	void* hooks::applyPlayerPhysicalIndexHook(CNetworkPlayerMgr* netPlayerMgr, CNetGamePlayer* player, uint8_t new_index) {
		const auto* playerData = player->GetGamerInfo();

		if (playerData) {
			if (new_index == 0xFF) {
				menu::notify::stacked(std::format("{} is leaving slot {}", player->GetName(), player->m_player_id).c_str());
			}
			else {
				menu::notify::stacked(std::format("{} is joining slot {}", player->GetName(), new_index).c_str());
			}
		}

		return ogApplyPlayerPhysicalIndexHook(netPlayerMgr, player, new_index);
	}
}