#include "pch.h"
#include "hooks/hooks.h"
#include "util/fiber_pool.h"
#include "rage/classes/SessionInfo.h"
#include "rage/classes/Network.h"
#include "rage/classes/rlTaskStatus.h"
#include "menu/util/matchmaking_service.h"
#include "menu/submenus/main/network/network_browsers.h"
namespace rage
{
	class JSONNode
	{
	public:
		char* m_key;                    //0x0000
		char pad_0008[32];              //0x0008
		class rage::JSONNode* m_sibling;//0x0028
		class rage::JSONNode* m_child;  //0x0030
		char* m_value;                  //0x0038
		char pad_0040[8];               //0x0040

		inline JSONNode* get_child_node(const char* name)
		{
			for (auto node = m_child; node; node = node->m_sibling)
			{
				if (strcmp(name, node->m_key) == 0)
					return node;
			}

			return nullptr;
		}
	};//Size: 0x0048
	static_assert(sizeof(rage::JSONNode) == 0x48);
}

namespace
{
	// https://stackoverflow.com/a/5167641
	static std::vector<std::string> split(const std::string& s, char seperator)
	{
		std::vector<std::string> output;

		std::string::size_type prev_pos = 0, pos = 0;

		while ((pos = s.find(seperator, pos)) != std::string::npos)
		{
			std::string substring(s.substr(prev_pos, pos - prev_pos));

			output.push_back(substring);

			prev_pos = ++pos;
		}

		output.push_back(s.substr(prev_pos, pos - prev_pos));// Last word

		return output;
	}
}

namespace base::hooks {

	bool hooks::processMatchmakingFindResponseHook(void* _this, void* rdx, rage::JSONNode* node, int* unk)
	{
		bool ret = ogProcessMatchmakingFindResponseHook(_this, rdx, node, unk);

		if (menu::g_matchmaking_service->is_active())
		{
			int i = 0;
			for (auto result = node->get_child_node("Results")->m_child; result; result = result->m_sibling)
			{
				const auto& values = split(result->get_child_node("Attributes")->m_value, ',');
				menu::g_matchmaking_service->get_found_sessions()[i].attributes.discriminator = std::stoi(values[2]);
				menu::g_matchmaking_service->get_found_sessions()[i].attributes.player_count = std::stoi(values[4]);
				menu::g_matchmaking_service->get_found_sessions()[i].attributes.language = std::stoi(values[5]);
				menu::g_matchmaking_service->get_found_sessions()[i].attributes.region = std::stoi(values[6]);
				i++;
			}
		}

		return ret;
	}
}

