#pragma once
#include <cstdint>
#include "grcTexture.h"

namespace rage {
    class pgDictionary {
    public:
        virtual ~pgDictionary() = default;
        uint64_t unk_0008; //0x0008
        uint64_t unk_0010; //0x0010
        uint32_t unk_0018; //0x0018
        uint32_t unk_001C; //0x001C
        uint64_t unk_0020; //0x0020
        int16_t m_count; //0x0028
        int16_t unk_002A; //0x002A
        char pad_002C[4]; //0x002C
        grcTexture** m_items; //0x0030
        uint32_t unk_0038; //0x0038

        bool AddElement(grcTexture* element) {
            m_count++;
            m_items[m_count - 1] = element;
            return m_items && m_items[m_count - 1] && IsElementValid(m_count - 1);
        }
        bool IsElementValid(uint32_t index) {
            if (!m_items)
                return false;
            if (index >= m_count)
                return false;
            return m_items[index];
        }
        grcTexture* GetElement(uint32_t index) {
            if (IsElementValid(index)) {
                if (m_items[index]->m_name) {
                    return m_items[index];
                }
            }
            return nullptr;
        }
        rage::grcTexture* FindTexture(std::string name) {
            for (decltype(m_count) i{ m_count }; i; --i) {
                if (auto element = GetElement(i); element) {
                    if (!name.compare(element->m_name)) {
                        return element;
                    }
                }
            }
            return nullptr;
        }
        std::vector<std::string> GetAllTextureNames() {
            std::vector<std::string> vec{};
            for (decltype(m_count) i{ m_count }; i; --i) {
                if (auto element = GetElement(i); element) {
                    vec.push_back(element->m_name);
                }
            }
            return vec;
        }
    }; //Size: 0x003C
}