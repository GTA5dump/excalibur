#pragma once
#include <cstdint>
#include "PeerInfo.h"

namespace rage {
    class rlSessionInfo
    {
    public:
        uint64_t m_unk; //0x0000
        uint64_t m_session_token; //0x0008
        rlPeerInfo m_net_player_data; //0x0010
    };
    static_assert(sizeof(rlSessionInfo) == 0xD0);
}