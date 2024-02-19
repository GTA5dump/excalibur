#include "pch.h"
#include "hooks/hooks.h"
#include "hooks/patterns.h"
#include "util/caller.h"

// maxi small cock momento?
//yoinked from orbit (dead class and siggy)
struct arxanReportItem {
        DWORD m_0x00;     // 0x0000
        DWORD m_0x04;     // 0x0004
        DWORD m_0x08;     // 0x0008
        DWORD m_0x0C;     // 0x000C
        DWORD m_0x10;     // 0x0010
        DWORD m_0x14;     // 0x0014
        DWORD m_0x18;     // 0x0018
        DWORD m_0x1C;     // 0x001C
        DWORD m_0x20;     // 0x0020
        DWORD m_0x24;     // 0x0024
        DWORD m_0x28;     // 0x0028
        DWORD m_0x2C;     // 0x002C
        DWORD m_0x30;     // 0x0030
        DWORD m_0x34;     // 0x0034

        bool isFrameflagReport() const { return this->m_0x18 == 0x18; }
};
static_assert(sizeof(arxanReportItem) == 0x38);

struct arxanContext {
	arxanReportItem m_reportItems[1024]; // 0x0000
	DWORD m_reportIndex;                 // 0xE000
	DWORD m_reportedItems;                 // 0xE004
	DWORD m_reportQueue;                 // 0xE008
};
static_assert(sizeof(arxanContext) == 0xE00C);

inline arxanContext* g_ArxanContextClass;

//Sig: 4C 8B D2 44 3B D9 0F 8D ? ? ? ? 45 8B 81 ? ? ? ? 33 C0 41 FF C0 (aka Arxan::AddDetection)


namespace base::hooks {

	//Andy has a big cock!?
	bool hooks::sendHTTPRequestHook(CHttpRequest* request) {

		if (request->RequestData && request->RequestData->Data) {			
			const auto path = std::string(request->Path);
			for (auto blockedApi : { "SubmitCompressed", "SubmitRealTime", "Bonus" }) {
				if (path.find(blockedApi) != std::string::npos) {
					request->Host = const_cast<char*>("google.com");
					return ogSendHTTPRequestHook(request);
				}
			}
		}
		return ogSendHTTPRequestHook(request);
	}
	//Andy has a big cock!?
	uint64_t hooks::addEventToListHook(uint64_t event_pool) {
		uint64_t caller = (uint64_t)_ReturnAddress();

		if (caller == patterns::report_myself) {
			LOG_CUSTOM_WARN("AC", "REPORT_MYSELF_EVENT creation");
			return false;
		}

		if (caller == patterns::check_crc) {
			LOG_CUSTOM_WARN("AC", "NETWORK_CHECK_CODE_CRCS_EVENT creation");
			return false;
		}

		if (caller == patterns::cash_spawn) {
			LOG_CUSTOM_WARN("AC", "REPORT_CASH_SPAWN_EVENT creation");
			return false;
		}

		return ogAddEventToListHook(event_pool);
	}

	void hooks::sendNetworkEventHook(uint64_t net_table, uint64_t event) {
		if (event) {
			short type = *(short*)(event + 8);

			if (type == 83u || type == 84u || type == 78u) {
				LOG_CUSTOM_WARN("AC", "network event - %i", type);

				uint64_t table = *(uint64_t*)event;
				caller::call<int>(*(uint64_t*)table, event, 1); // Deallocate event
				return;
			}
		}

		return ogSendNetworkEventHook(net_table, event);
	}

	int hooks::ntQueryVirtualMemoryHook(void* _this, HANDLE handle, PVOID base_addr, int info_class, MEMORY_BASIC_INFORMATION* info, int size, size_t* return_len) {
		return 1;
	}

	bool inline is_address_in_game_region(uint64_t address)
	{
		static uint64_t moduleBase = NULL;
		static uint64_t moduleSize = NULL;
		if ((!moduleBase) || (!moduleSize))
		{
			MODULEINFO info;
			if (!GetModuleInformation(GetCurrentProcess(), GetModuleHandle(0), &info, sizeof(info)))
			{
				LOG_ERROR("GetModuleInformation failed!");
				return true;
			}
			else
			{
				moduleBase = (uint64_t)GetModuleHandle(0);
				moduleSize = (uint64_t)info.SizeOfImage;
			}
		}
		return address > moduleBase && address < (moduleBase + moduleSize);
	}

	bool is_jump(__int64 fptr)
	{
		if (!is_address_in_game_region(fptr))
			return false;

		auto value = *(std::uint8_t*)(fptr);
		return value == 0xE9;
	}

	bool is_unwanted_dependency(__int64 cb)
	{
		auto f1 = *(__int64*)(cb + 0x60);
		auto f2 = *(__int64*)(cb + 0x100);
		auto f3 = *(__int64*)(cb + 0x1A0);

		if (!is_address_in_game_region(f1) || !is_address_in_game_region(f2) || !is_address_in_game_region(f3))
			return false;

		return is_jump(f1) || is_jump(f2) || is_jump(f3);
	}

	void hooks::queueDependencyHook(void* dependency) {
		if (is_unwanted_dependency((__int64)dependency))
		{
			return;
		}
		return ogQueueDependencyHook(dependency);
	}

	std::vector<std::string> blocked_metrics = {
	"DIG",
	"XP_LOSS",
	"AWARD_XP",
	"CF",
	"CC",
	"CNR",
	"SCRIPT",
	"CHEAT",
	"AUX_DEUX",
	"WEATHER",
	"HARDWARE_OS",
	"HARDWARE_GPU",
	"HARDWARE_MOBO",
	"HARDWARE_MEM",
	"HARDWARE_CPU",
	"PCSETTINGS",
	"CASH_CREATED",
	"DR_PS",
	"UVC",
	"W_L",
	"ESVCS",
	"IDLEKICK",
	"GSCB",
	"GSINV",
	"GSCW",
	"GSINT",
	"EARN",
	"GARAGE_TAMPER"
	};

	bool sendMetricHook(rage::rlMetric* _this, bool unk) {
		LOG_WARN(std::format("METRIC: {} {} {}", _this->get_name(), _this->get_name_hash(), _this->get_size()).c_str());

		if (std::find(begin(blocked_metrics), end(blocked_metrics), _this->get_name()) != end(blocked_metrics)) {
			LOG_WARN(std::format("Blocking bad metric: {}", _this->get_name()).c_str());
			return false;
		}

		return ogSendMetricHook(_this, unk);
	}

}