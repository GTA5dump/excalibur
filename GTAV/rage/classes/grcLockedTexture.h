#pragma once
#include <cstdint>

namespace rage {
    enum class grcLockFlags : int32_t {
        Read = 1,
        Write = 2,
        Unknown = 4,
        WriteDiscard = 8,
        NoOverwrite = 16
    };
    class grcLockedTexture {
    public:
        int32_t m_level; //0x0000
        void* m_bits; //0x0004
        int32_t m_pitch; //0x000C
        int32_t m_pad; //0x0010
        uint32_t m_width; //0x0014
        uint32_t m_height; //0x0018
        int32_t m_format; //0x001C
        int32_t m_num_sub_levels; //0x0020
    }; //Size: 0x0028
    static_assert(sizeof(grcLockedTexture) == 0x28);
}