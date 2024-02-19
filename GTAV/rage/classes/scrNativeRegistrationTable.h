#pragma once
#include "pch.h"
#include "scrNativeRegistration.h"

namespace rage {
#pragma pack(push, 1)
	class scrNativeRegistrationTable {
	public:
		scrNativeRegistration* m_entries[255]; //0x0000
		uint32_t m_seed; //0x07F8
		bool m_initialized; //0x07FC

		rage::scrCmd get_handler(uint64_t hash) {
			for (auto entry = m_entries[(uint8_t)(hash & 0xFF)]; entry; entry = entry->get_next_registration()) {
				for (uint32_t i{}, end{ entry->get_num_entries() }; i < end; ++i) {
					if (auto entry_hash = entry->get_hash(i); entry_hash == hash) {
						return entry->m_handlers[i];
					}
				}
			}
			return nullptr;
		}
	}; //Size: 0x07FD
	static_assert(sizeof(scrNativeRegistrationTable) == 0x7FD);
#pragma pack(pop)
}