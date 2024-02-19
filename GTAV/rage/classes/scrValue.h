#pragma once
#include <cstdint>
#include <wtypes.h>

namespace rage {
	union scrValue {
		int32_t Int;
		uint32_t Uns;
		float Float;
		LPCSTR String;
		scrValue* Reference;
		size_t Any;
		bool operator==(const scrValue& val) {
			return Int == val.Int;
		}
	};
}