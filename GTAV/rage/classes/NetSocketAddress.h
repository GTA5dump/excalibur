#pragma once
#include <cstdint>

namespace rage {
	union netAddress {
		uint32_t m_packed; //0x0000
		struct {
			uint8_t m_field4; //0x0000
			uint8_t m_field3; //0x0001
			uint8_t m_field2; //0x0002
			uint8_t m_field1; //0x0003
		};
	}; //Size: 0x0004
	static_assert(sizeof(netAddress) == 0x04);
	class netSocketAddress {
	public:
		union rage::netAddress m_ip; //0x0000
		uint16_t m_port; //0x0004
	};
	static_assert(sizeof(rage::netSocketAddress) == 0x08);
}