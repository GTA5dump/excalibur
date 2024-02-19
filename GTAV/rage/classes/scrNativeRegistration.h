#pragma once
#include "pch.h"

namespace rage {
    using scrCmd = fnptr<void(class scrNativeCallContext*)>;
    using scrNativeHash = uint64_t;
    class scrNativeRegistration {
    public:
        scrNativeRegistration* m_next; //0x0000
        scrNativeRegistration* m_previous; //0x0008
        rage::scrCmd m_handlers[7]; //0x0010
        uint32_t m_num_entries; //0x0048
        uint32_t m_num_entries_2; //0x004C
        uint64_t m_hashes[7 * 2]; //0x0050

        scrNativeRegistration* get_next_registration() {
            uint64_t result{};
            uint64_t nextRegistration{ uint64_t(&m_next) };
            uint64_t previousRegistration{ nextRegistration ^ (uint64_t)m_previous };
            int8_t* registrations{ (int8_t*)&result - nextRegistration };
            for (uint8_t i{ 2 }; i; --i) {
                *(uint32_t*)&registrations[nextRegistration] = static_cast<uint32_t>(previousRegistration) ^ *(uint32_t*)nextRegistration;
                nextRegistration += 4;
            }
            return reinterpret_cast<scrNativeRegistration*>(result);
        }
        void set_next_registration(scrNativeRegistration* registration) {
            m_next = (scrNativeRegistration*)(((uint64_t)((uint64_t*)&m_next) << 32) ^ ((uint32_t)((uint64_t*)&m_next) << 0) ^ (uint64_t)registration);
            m_previous = NULL;
        }
        uint32_t get_num_entries() {
            return static_cast<uint32_t>(((uintptr_t)&m_num_entries) ^ m_num_entries ^ m_num_entries_2);
        }
        void set_num_entries(uint32_t entries) {
            m_num_entries = (uint32_t)&m_num_entries ^ entries;
            m_num_entries_2 = entries;
        }
        uint64_t get_hash(uint32_t index) {
            uint64_t result{};
            auto nativeAddress{ 16 * index + uintptr_t(&m_next) + 0x54 };
            auto registrations{ (char*)&result - nativeAddress };
            auto addressIndex{ nativeAddress ^ *(uint32_t*)(nativeAddress + 0x8) };
            for (uint8_t i{ 2 }; i; --i) {
                *(uint32_t*)&registrations[nativeAddress] = static_cast<uint32_t>(addressIndex ^ *(uint32_t*)(nativeAddress));
                nativeAddress += 4;
            }
            return result;
        }
        void set_hash(uint32_t index, uint64_t newHash) {
            auto hash = &m_hashes[index * 2];
            hash[0] = ((uint64_t)hash << 32) ^ ((uint32_t)hash << 0) ^ (uint64_t)newHash;
            hash[1] = 0;
        }
    }; //Size: 0x00C0
    static_assert(sizeof(scrNativeRegistration) == 0xC0);
}