#pragma once
#include <cstdint>
#include "RTTI.h"

#pragma pack(push, 8)
class CPedInventory : rage::atRTTI<CPedInventory> {
public:
    uint64_t unk_0008; //0x0008
    class CPed* m_ped; //0x0010
    uint64_t unk_0018; //0x0018
    uint32_t unk_0020; //0x0020
    uint64_t unk_0028; //0x0028
    uint64_t unk_0030; //0x0030
    uint32_t unk_0038; //0x0038
    char pad_003C[4]; //0x003C
    uint8_t unk_0040; //0x0040
    char pad_0041[7]; //0x0041
    uint64_t unk_0048; //0x0048
    uint32_t unk_0050; //0x0050
    uint64_t unk_0058; //0x0058
    uint64_t unk_0060; //0x0060
    uint32_t unk_0068; //0x0068
    char pad_006C[4]; //0x006C
    uint8_t unk_0070; //0x0070
    char pad_0071[7]; //0x0071
    bool m_infinite_ammo : 1; //0x0078
    bool m_infinite_clip : 1; //0x0078
    char pad_0079[7]; //0x0079
    uint64_t unk_0080; //0x0080
}; //Size: 0x0088
static_assert(sizeof(CPedInventory) == 0x88);
#pragma pack(pop)