#pragma once
#include "vector.h"

namespace rage {
	class CNavigation {
	public:
		char pad_0000[32]; //0x0000
		float m_heading; //0x0020
		float m_heading_2; //0x0024
		char pad_0028[8]; //0x0028
		struct vector3 m_rotation; //0x0030
		char pad_003C[20]; //0x003C
		struct vector3 m_position; //0x0050
	}; //Size: 0x005C
}