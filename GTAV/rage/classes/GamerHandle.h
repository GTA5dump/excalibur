#pragma once
#include <cstdint>

namespace rage {
#pragma pack(push, 8)
	class rlGamerHandle {
	public:
		rlGamerHandle(uint64_t rockstar_id, uint8_t platform) : m_rockstar_id(rockstar_id), m_platform(platform) {}
		rlGamerHandle(uint64_t rockstar_id) : rlGamerHandle(0, 3) {}
		rlGamerHandle() : rlGamerHandle(0) {}
	public:
		uint64_t m_rockstar_id; //0x0000
		uint8_t m_platform; //0x0008
		uint8_t unk_0009; //0x0009
	public:
		bool deserialize(class datBitBuffer& buf);
		bool serialize(class datBitBuffer& buf);
	}; //Size: 0x0010
	static_assert(sizeof(rlGamerHandle) == 0x10);
#pragma pack(pop)
}