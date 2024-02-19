#pragma once
#include <cstdint>

namespace rage {
	template<typename TKey, typename TEntry>
	class atMap {
	private:
		struct Entry {
			TKey hash;
			TEntry data;
			Entry* next;
		};
	public:
		atMap() {
			//m_initialized = false;
		}
		TEntry* begin() { return m_data; }
		TEntry* end() { return m_data + m_size; }
		const TEntry* begin() const { return m_data; }
		const TEntry* end() const { return m_data + m_size; }
		TEntry* data() { return m_data; }
		const TEntry* data() const { return m_data; }
		uint16_t size() const { return m_size; }
		TEntry& operator[](uint16_t index) { return m_data[index]; }
		const TEntry& operator[](uint16_t index) const { return m_data[index]; }
	public:
		void ForAllEntriesWithHash(const std::function<void(TKey hash, TEntry*)>& cb) {
			for (int idx{}; idx != m_size; ++idx) {
				for (auto i{ m_data[idx] }; i; i = i->next) {
					cb(i->hash, &i->data);
				}
			}
		}
	private:
		Entry** m_data;
		uint16_t m_size;
		uint16_t m_count;
		Entry* m_nextFree;
	};
}