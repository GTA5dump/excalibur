#pragma once
#include "pch.h"
#include "vector.h"
#include "scrValue.h"

namespace rage {
	class scrVectorSpace {
	public:
		void Reset() {
			BufferCount = 0;
		}
		void CopyReferencedParametersOut() {
			while (BufferCount--) {
				Orig[BufferCount][0].Float = Buffer[BufferCount].x;
				Orig[BufferCount][1].Float = Buffer[BufferCount].y;
				Orig[BufferCount][2].Float = Buffer[BufferCount].z;
			}
		}
		uint32_t BufferCount; //0x0000
		scrValue* Orig[4]; //0x0004
		scrVector Buffer[4]; //0x0020
	}; //Size: 0x0060
	class scrNativeCallContext {
	public:
		void reset() {
			ArgCount = 0;
			VectorSpace.Reset();
		}
		template <typename t>
		void push_arg(t&& value) {
			static_assert(sizeof(t) <= sizeof(std::uint64_t));
			*reinterpret_cast<std::remove_cv_t<std::remove_reference_t<t>>*>(reinterpret_cast<std::uint64_t*>(Args) + (ArgCount++)) = std::forward<t>(value);
		}
		template <typename t>
		t& get_arg(std::size_t index) {
			static_assert(sizeof(t) <= sizeof(std::uint64_t));
			return *reinterpret_cast<t*>(reinterpret_cast<std::uint64_t*>(Args) + index);
		}
		template <typename t>
		void set_arg(std::size_t index, t&& value) {
			static_assert(sizeof(t) <= sizeof(std::uint64_t));
			*reinterpret_cast<std::remove_cv_t<std::remove_reference_t<t>>*>(reinterpret_cast<std::uint64_t*>(Args) + index) = std::forward<t>(value);
		}
		template <typename t>
		t* get_return_value() {
			return reinterpret_cast<t*>(Return);
		}
		template <typename t>
		void set_return_value(t value) {
			*reinterpret_cast<std::remove_cv_t<std::remove_reference_t<t>>*>(Return) = value;
		}
	public:
		scrValue* Return; //0x0000
		uint32_t ArgCount; //0x0008
		scrValue* Args; //0x0010
		scrVectorSpace VectorSpace;
	}; //Size: 0x00E0

	using scrNativeHandler = void(*)(scrNativeCallContext*);

}