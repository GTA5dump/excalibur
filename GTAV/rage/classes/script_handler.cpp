#include "pch.h"
#include "CNetGamePlayer.h"
#include "script_handler.h"
#include "hooks/patterns.h"


int CGameScriptHandlerNetComponent::get_participant_index(CNetGamePlayer* player)
{
	if (player == (*patterns::network_player_mgr)->m_local_net_player)
		return m_local_participant_index;

	if (m_num_participants <= 1)
		return -1;

	for (int i = 0; i < m_num_participants - 1; i++)
	{
		if (m_participants[i] && m_participants[i]->m_net_game_player == player)
			return m_participants[i]->m_participant_index;
	}

	return -1;
}

bool CGameScriptHandlerNetComponent::is_player_a_participant(CNetGamePlayer* player) {
	return m_participant_bitset & (1 << player->m_player_id);
}