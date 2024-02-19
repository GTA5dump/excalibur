#pragma once
#include <cstdint>
#include "NonPhysicalPlayerDataBase.h"
#include "vector.h"

#pragma pack(push, 4)
class CNonPhysicalPlayerData : public rage::nonPhysicalPlayerDataBase
{
public:
    int32_t m_bubble_id; //0x0008
    int32_t m_player_id; //0x000C
    rage::vector3 m_position; //0x0010
}; //Size: 0x001C
static_assert(sizeof(CNonPhysicalPlayerData) == 0x1C);
#pragma pack(pop)