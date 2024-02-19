#pragma once
#include <cstdint>
#include "base.h"

namespace rage {
	template <typename T>
	class fwRefAwareBaseImpl : public T {
	private:
		void* m_ref; // 0x08
	};
	class fwRefAwareBase : public fwRefAwareBaseImpl<datBase> {};
	static_assert(sizeof(fwRefAwareBase) == 0x10);
	class fwExtension {
	public:
		virtual ~fwExtension() = default;
		virtual void unk_0x08() = 0;
		virtual void unk_0x10() = 0;
		virtual uint32_t get_id() = 0;
	}; //Size: 0x0008
	static_assert(sizeof(fwExtension) == 0x8);
	class fwExtensionContainer {
	public:
		fwExtension* m_entry; //0x0000
		fwExtensionContainer* m_next; //0x0008
	}; //Size: 0x0010
	static_assert(sizeof(fwExtensionContainer) == 0x10);
	class fwExtensibleBase : public fwRefAwareBase {
	public:
		//virtual bool is_of_type(uint32_t hash) = 0;
		//virtual uint32_t const& get_type() = 0;
		fwExtensionContainer* m_extension_container; // 0x0010
		void* m_extensible_unk; // 0x0018
		template <typename T>
		bool is_of_type() {
			static auto name = (typeid(T).name()) + 6; // Skip "class "
			static auto name_hash = joaat(name);
			return is_of_type(name_hash);
		}
	}; //Size: 0x0020
	static_assert(sizeof(fwExtensibleBase) == 0x20);
}