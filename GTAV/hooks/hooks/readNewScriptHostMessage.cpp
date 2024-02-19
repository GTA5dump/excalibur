#include "pch.h"
#include "hooks/hooks.h"
#include "gui/util/notify.h"
#include "util/caller.h"
#include "rage/classes/CNetGamePlayer.h"
#include "rage/classes/CPlayerInfo.h"
namespace base::hooks {

	bool hooks::readNewScriptHostMessageHook(uint64_t rcx, uint64_t rdx) {
		uint8_t data[0x50];
		memset(data, 0, 0x50);

		uint64_t script_table = *(uint64_t*)rcx;
		*(uint64_t*)&data[0] = caller::call<uint64_t>(*(uint64_t*)(script_table + 0x78), rcx);

		if (caller::call<bool>(patterns::read_new_script_host_message, data, *(uint64_t*)(rdx), *(uint32_t*)(rdx + 0x8), 0)) {
			CNetGamePlayer* new_host = *(CNetGamePlayer**)(rdx + 0x10);
			if (new_host != nullptr) {
				bool forced = false;
				uint16_t host_token = *(uint16_t*)&data[0x8];
				if (host_token == 0xFFFF) {
					forced = true;
				}

				CGameScriptHandler* script_handler = caller::call<CGameScriptHandler*>(*(uint64_t*)(script_table + 0x48), rcx, *(uint64_t*)(&data[0]));
				if (util::is_valid_ptr(script_handler)) {
					if (util::is_valid_ptr(script_handler->m_script_thread)) {
						if (!strcmp(script_handler->m_script_thread->m_name, "freemode")) {
							if (new_host->m_player_id != NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0)) {
								menu::notify::stacked(std::format("{} {}", new_host->GetName(), forced ? "foced script host" : "is now script host").c_str());
							}
						}
					}
				}
				
			}
		}

		return ogReadNewScriptHostMessageHook(rcx, rdx);
	}

}