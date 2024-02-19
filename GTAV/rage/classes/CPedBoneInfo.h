#pragma once
#include "vector.h"

enum class ePedBoneType {
    HEAD,
    L_FOOT,
    R_FOOT,
    L_ANKLE,
    R_ANKLE,
    L_HAND,
    R_HAND,
    NECK,
    ABDOMEN
};

class CPedBoneInfo {
public:
    rage::vector3 m_model_coords; //0x0000
    char pad_000C[4]; //0x000C
}; //Size: 0x0010
static_assert(sizeof(CPedBoneInfo) == 0x10);