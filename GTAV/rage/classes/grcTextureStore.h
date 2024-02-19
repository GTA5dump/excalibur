#pragma once
#include <cstdint>
#include "pgDictionaryPool.h"

namespace rage {
    class grcTextureStore {
    public:
        char pad_0000[56]; //0x0000
        pgDictionaryPool* m_pool; //0x0038
        uint8_t* m_mask; //0x0040
        uint32_t m_count; //0x0048
        uint32_t m_size; //0x0052
    public:
        auto BitshiftMask(uint32_t index, uint8_t amount) { return m_mask[index] >> amount; }
        bool IsElementValid(uint32_t index) {
            if (!m_mask)
                return false;
            if (index >= m_count)
                return false;
            return ~BitshiftMask(index, 7) & 1;
        }
        pgDictionaryPool* GetElement(uint32_t index) {
            if (IsElementValid(index)) {
                if (m_pool[index].m_dictionary) {
                    return &m_pool[index];
                }
            }
            return nullptr;
        }
        rage::pgDictionary* FindDictionary(uint32_t hash) {
            for (decltype(m_count) i{ m_count }; i; --i) {
                if (auto element = GetElement(i); element) {
                    if (element->m_dictionary_hash == hash) {
                        return element->m_dictionary;
                    }
                }
            }
            return nullptr;
        }
        std::map<uint32_t, rage::pgDictionary*> GetAllDictionaries() {
            std::map<uint32_t, rage::pgDictionary*> vec{};
            for (decltype(m_count) i{ m_count }; i; --i) {
                if (auto element = GetElement(i); element) {
                    if (element->m_dictionary_hash) {
                        vec.insert({ element->m_dictionary_hash, element->m_dictionary });
                    }
                }
            }
            return vec;
        }
    }; //Size: 0x0056
}