#pragma once
#include <cstdint>
#include "pgDictionary.h"

namespace rage {
    class pgDictionaryPool {
    public:
        pgDictionary* m_dictionary; //0x0000
        char pad_0008[4]; //0x0008
        uint32_t m_dictionary_hash; //0x000C
        char pad_0010[8]; //0x0010
    }; //Size: 0x0018
}