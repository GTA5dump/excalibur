#include "pch.h"
#include "matchmaking_service.h"
#include "rage/classes/Network.h"
#include "hooks/hooks.h"
#include "rage/classes/rlTaskStatus.h"
#include "util/fiber.h"
#include "menu/submenus/main/network/network_browsers.h"
namespace menu {
	matchmaking_service::matchmaking_service()
	{
		g_matchmaking_service = this;
	}

	matchmaking_service::~matchmaking_service()
	{
		g_matchmaking_service = nullptr;
	}

	bool matchmaking_service::matchmake(std::optional<int> constraint)
	{

		for (auto& session : m_found_sessions)
		{
			session.is_valid = true;
		}

		NetworkGameFilterMatchmakingComponent component{};
		strcpy(component.m_filter_name, "Group");
		component.m_game_mode = 0;
		component.m_num_parameters = 0;

		if (network::browsers::vars::m_vars.region_filter_enabled)
		{
			component.SetParameter("MMATTR_REGION", 0, network::browsers::vars::m_vars.region_filter);
		}

		if (constraint)
		{
			component.SetParameter("MMATTR_DISCRIMINATOR", 1, constraint.value());
		}

		rage::rlTaskStatus state{};
		static rage::rlSessionInfo result_sessions[MAX_SESSIONS_TO_FIND];

		m_active = true;

		if (caller::call<bool>(patterns::start_session_search, 0, 1, &component, MAX_SESSIONS_TO_FIND, result_sessions, &m_num_sessions_found, &state))
		{
			while (state.status == 1)
				util::fiber::go_to_main();

			if (state.status == 3)
			{
				for (int i = 0; i < m_num_sessions_found; i++)
				{
					m_found_sessions[i].info = result_sessions[i];

					if (constraint && m_found_sessions[i].attributes.player_count >= 30)
						m_found_sessions[i].is_valid = false;

					if (network::browsers::vars::m_vars.language_filter_enabled
						&& m_found_sessions[i].attributes.language != network::browsers::vars::m_vars.language_filter)
						m_found_sessions[i].is_valid = false;

					if (network::browsers::vars::m_vars.player_count_filter_enabled
						&& (m_found_sessions[i].attributes.player_count < network::browsers::vars::m_vars.player_count_filter_minimum
							|| m_found_sessions[i].attributes.player_count > network::browsers::vars::m_vars.player_count_filter_maximum))
					{
						m_found_sessions[i].is_valid = false;
					}

					if (network::browsers::vars::m_vars.pool_filter_enabled
						&& ((m_found_sessions[i].attributes.discriminator & (1 << 14)) == (1 << 14))
						!= (bool)network::browsers::vars::m_vars.pool_filter)
						m_found_sessions[i].is_valid = false;
				}

				if (network::browsers::vars::m_vars.sort_method != 0)
				{
					std::qsort(m_found_sessions, m_num_sessions_found, sizeof(session), [](const void* a1, const void* a2) -> int {
						std::strong_ordering result;

						if (network::browsers::vars::m_vars.sort_method == 1)
						{
							result = (((session*)(a1))->attributes.player_count <=> ((session*)(a2))->attributes.player_count);
						}

						if (result == 0)
							return 0;

						if (result > 0)
							return network::browsers::vars::m_vars.sort_direction ? -1 : 1;

						if (result < 0)
							return network::browsers::vars::m_vars.sort_direction ? 1 : -1;


						std::unreachable();
						});
				}

				m_active = false;
				return true;
			}
		}
		else
		{
			m_active = false;
			return false;
		}

		m_active = false;
		return false;
	}
}