#pragma once
#include "pch.h"
#include "rage/classes/vector.h"

struct CBlip {
    char _0x0000[0x4];
    int m_handle;
    char _0x0008[0x8];
    rage::vector3 m_coords;
    char _0x001C[0x24];
    int m_sprite;
    char _0x0044[0x4];
    int m_color;
    int m_color2;
    rage::vector2 m_scale;
    float m_rotation;

    bool is_visible() {
        return *(bool*)((uint64_t)this + 0x10);
    }
};

struct CBlipList {
    CBlip* m_blips[1500];
};