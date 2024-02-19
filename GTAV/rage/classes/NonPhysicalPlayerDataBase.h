#pragma once
#include <cstdint>

namespace rage {
	class nonPhysicalPlayerDataBase {
	public:
		virtual ~nonPhysicalPlayerDataBase(); //0x0000 (0)
		virtual void _0x08(); //0x0008 (1)
		virtual void _0x10(); //0x0010 (2)
		virtual void _0x18(); //0x0018 (3)
		virtual void log(); //0x0020 (4)
	}; //Size: 0x0008
	static_assert(sizeof(nonPhysicalPlayerDataBase) == 0x8);
}