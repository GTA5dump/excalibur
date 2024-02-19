#pragma once
#include "pch.h"
#include <span>

namespace memory {
	class Ptr {
	public:
		Ptr(void* ptr = nullptr);
		explicit Ptr(std::uintptr_t ptr);

		template<typename T>
		std::enable_if_t<std::is_pointer_v<T>, T> as() const;

		template<typename T>
		std::enable_if_t<std::is_lvalue_reference_v<T>, T> as() const;

		template<typename T>
		std::enable_if_t<std::is_same_v<T, std::uintptr_t>, T> as() const;

		template<typename T>
		Ptr add(T offset) const;

		template<typename T>
		Ptr sub(T offset) const;

		Ptr rip() const;

		Ptr call() const;
		Ptr from_instruction() const;
		Ptr lea() const;

		explicit operator bool();

		friend bool operator==(Ptr a, Ptr b);
		friend bool operator!=(Ptr a, Ptr b);

	private:
		void* ptr;
	};

	inline Ptr::Ptr(void* ptr) : ptr(ptr) {}

	inline Ptr::Ptr(std::uintptr_t ptr) : ptr(reinterpret_cast<void*>(ptr)) {}

	template<typename T>
	inline std::enable_if_t<std::is_pointer_v<T>, T> Ptr::as() const {
		return static_cast<T>(ptr);
	}

	template<typename T>
	inline std::enable_if_t<std::is_lvalue_reference_v<T>, T> Ptr::as() const {
		return *static_cast<std::add_pointer_t<std::remove_reference_t<T>>>(ptr);
	}

	template<typename T>
	inline std::enable_if_t<std::is_same_v<T, std::uintptr_t>, T> Ptr::as() const {
		return reinterpret_cast<std::uintptr_t>(ptr);
	}

	template<typename T>
	inline Ptr Ptr::add(T offset) const {
		return Ptr(as<std::uintptr_t>() + offset);
	}

	template<typename T>
	inline Ptr Ptr::sub(T offset) const {
		return Ptr(as<std::uintptr_t>() - offset);
	}

	inline Ptr Ptr::rip() const {
		return add(as<std::int32_t&>()).add(4);
	}

	inline Ptr Ptr::call() const {
		return add(1).rip();
	}

	inline Ptr Ptr::lea() const {
		return add(2).rip();
	}

	inline Ptr Ptr::from_instruction() const {
		return add(3).rip();
	}

	inline bool operator==(Ptr a, Ptr b) {
		return a.ptr == b.ptr;
	}

	inline bool operator!=(Ptr a, Ptr b) {
		return a.ptr != b.ptr;
	}

	inline Ptr::operator bool() {
		return ptr != nullptr;
	}

	inline std::optional<std::uint8_t> to_hex(char const c) {
		switch (c) {
		case '0': return static_cast<std::uint8_t>(0x0);
		case '1': return static_cast<std::uint8_t>(0x1);
		case '2': return static_cast<std::uint8_t>(0x2);
		case '3': return static_cast<std::uint8_t>(0x3);
		case '4': return static_cast<std::uint8_t>(0x4);
		case '5': return static_cast<std::uint8_t>(0x5);
		case '6': return static_cast<std::uint8_t>(0x6);
		case '7': return static_cast<std::uint8_t>(0x7);
		case '8': return static_cast<std::uint8_t>(0x8);
		case '9': return static_cast<std::uint8_t>(0x9);
		case 'a': return static_cast<std::uint8_t>(0xa);
		case 'b': return static_cast<std::uint8_t>(0xb);
		case 'c': return static_cast<std::uint8_t>(0xc);
		case 'd': return static_cast<std::uint8_t>(0xd);
		case 'e': return static_cast<std::uint8_t>(0xe);
		case 'f': return static_cast<std::uint8_t>(0xf);
		case 'A': return static_cast<std::uint8_t>(0xA);
		case 'B': return static_cast<std::uint8_t>(0xB);
		case 'C': return static_cast<std::uint8_t>(0xC);
		case 'D': return static_cast<std::uint8_t>(0xD);
		case 'E': return static_cast<std::uint8_t>(0xE);
		case 'F': return static_cast<std::uint8_t>(0xF);
		default: return std::nullopt;
		}
	}


	class pattern
	{
	public:
		pattern(std::string_view ida_sig) {
			const auto size = ida_sig.size();
			for (std::size_t i{}; i != size; ++i) {
				if (ida_sig[i] == ' ')
					continue;
				bool last = (i == ida_sig.size() - 1);
				if (ida_sig[i] != '?') {
					if (!last) {
						auto c1 = to_hex(ida_sig[i]);
						auto c2 = to_hex(ida_sig[i + 1]);
						if (c1 && c2) {
							m_bytes.emplace_back(static_cast<std::uint8_t>((*c1 * 0x10) + *c2));
						}
					}
				}
				else {
					m_bytes.push_back({});

					if (ida_sig[i + 1] == '?') {
						++i;
					}
				}
			}
		}
		explicit pattern(const void* bytes, std::string_view mask) {
			const auto size = mask.size();
			for (std::size_t i{}; i != size; ++i) {
				if (mask[i] != '?')
					m_bytes.emplace_back(static_cast<const std::uint8_t*>(bytes)[i]);
				else
					m_bytes.push_back(std::nullopt);
			}
		}

		inline pattern(const char* ida_sig) :
			pattern(std::string_view(ida_sig))
		{}

		std::vector<std::optional<std::uint8_t>> m_bytes;
	};

	class range
	{
	public:
		range(Ptr base, std::size_t size) :
			m_base(base),
			m_size(size)
		{
		}

		Ptr begin() const {
			return m_base;
		}

		Ptr end() const {
			return m_base.add(m_size);
		}

		std::size_t size() const {
			return m_size;
		}

		bool contains(Ptr h) const {
			return h.as<std::uintptr_t>() >= begin().as<std::uintptr_t>() && h.as<std::uintptr_t>() <= end().as<std::uintptr_t>();
		}

		static Ptr scan_pattern(const std::optional<std::uint8_t>* sig, std::size_t length, Ptr begin, std::size_t module_size) {
			std::size_t maxShift = length;
			std::size_t max_idx = length - 1;

			std::size_t wild_card_idx{ static_cast<size_t>(-1) };
			for (int i{ static_cast<int>(max_idx - 1) }; i >= 0; --i) {
				if (!sig[i]) {
					maxShift = max_idx - i;
					wild_card_idx = i;
					break;
				}
			}

			std::size_t shift_table[UINT8_MAX + 1]{};
			for (std::size_t i{}; i <= UINT8_MAX; ++i) {
				shift_table[i] = maxShift;
			}

			for (std::size_t i{ wild_card_idx + 1 }; i != max_idx; ++i) {
				shift_table[*sig[i]] = max_idx - i;
			}

			const auto scan_end = module_size - length;
			for (std::size_t current_idx{}; current_idx <= scan_end;) {
				for (std::ptrdiff_t sig_idx{ (std::ptrdiff_t)max_idx }; sig_idx >= 0; --sig_idx) {
					if (sig[sig_idx] && *begin.add(current_idx + sig_idx).as<uint8_t*>() != *sig[sig_idx]) {
						current_idx += shift_table[*begin.add(current_idx + max_idx).as<uint8_t*>()];
						break;
					}
					else if (sig_idx == NULL) {
						return begin.add(current_idx);
					}
				}
			}
			return nullptr;
		}

		Ptr scan(pattern const& sig) const {
			auto data = sig.m_bytes.data();
			auto length = sig.m_bytes.size();

			if (auto result = scan_pattern(data, length, m_base, m_size); result)
			{
				return result;
			}

			return nullptr;
		}

		static bool pattern_matches(std::uint8_t* target, const std::optional<std::uint8_t>* sig, std::size_t length) {
			for (std::size_t i{}; i != length; ++i) {
				if (sig[i] && *sig[i] != target[i]) {
					return false;
				}
			}

			return true;
		}

		std::vector<Ptr> scan_all(pattern const& sig) const {
			std::vector<Ptr> result{};
			auto data = sig.m_bytes.data();
			auto length = sig.m_bytes.size();

			const auto scan_end = m_size - length;
			for (std::uintptr_t i{}; i != scan_end; ++i) {
				if (pattern_matches(m_base.add(i).as<std::uint8_t*>(), data, length)) {
					result.push_back(m_base.add(i));
				}
			}

			return std::move(result);
		}
	protected:
		Ptr m_base;
		std::size_t m_size;
	};

	class module : public range
	{
	public:
		module(HMODULE mod) :
			range(mod, 0)
		{
			auto dosHeader = m_base.as<IMAGE_DOS_HEADER*>();
			auto ntHeader = m_base.add(dosHeader->e_lfanew).as<IMAGE_NT_HEADERS*>();
			m_size = ntHeader->OptionalHeader.SizeOfImage;
		}
		explicit module(std::nullptr_t) :
			module(GetModuleHandle(nullptr))
		{
		}
		explicit module(std::string_view name) :
			module(GetModuleHandleA(name.data()))
		{
		}
		explicit module(std::wstring_view name) :
			module(GetModuleHandleW(name.data()))
		{
		}

		memory::Ptr get_export(std::string_view symbol_name)
		{
			return GetProcAddress(m_base.as<HMODULE>(), symbol_name.data());
		}
	};

	class batch {
	public:
		explicit batch() = default;
		~batch() noexcept = default;

		void Add(std::pair<const char*, pattern> entry, std::function<void(Ptr)> callback, bool& out);
		void run(range region);

		struct entry {
			std::string m_name;
			pattern m_pattern;
			std::function<void(memory::Ptr)> m_callback;
			bool m_out;

			explicit entry(std::string name, pattern pattern, std::function<void(memory::Ptr)> callback, bool out) :
				m_name(std::move(name)),
				m_pattern(std::move(pattern)),
				m_callback(std::move(callback)),
				m_out(std::move(out))
			{}
		};

	private:
		std::vector<entry> m_entries;
	};

	template<typename T>
	concept SpanCompatibleType = requires(T a)
	{
		std::span{ a };
	};

	class byte_patch
	{
	public:
		virtual ~byte_patch()
		{
			restore();
		}

		void apply() const
		{
			memcpy(m_address, m_value.get(), m_size);
		}

		void restore() const
		{
			memcpy(m_address, m_original_bytes.get(), m_size);
		}

		void remove() const
		{
			if (const auto it = std::find(m_patches.begin(), m_patches.end(), this); it != m_patches.end())
			{
				m_patches.erase(it);
			}
		}

		template<typename TAddr>
		static const std::unique_ptr<byte_patch>& make(TAddr address, std::remove_pointer_t<std::remove_reference_t<TAddr>> value)
		{
			return m_patches.emplace_back(std::unique_ptr<byte_patch>(new byte_patch(address, value)));
		}

		template<typename TAddr, typename T>
			requires SpanCompatibleType<T>
		static const std::unique_ptr<byte_patch>& make(TAddr address, T span_compatible)
		{
			return m_patches.emplace_back(std::unique_ptr<byte_patch>(new byte_patch(address, std::span{ span_compatible })));
		}

		void restore_all()
		{
			m_patches.clear();
		}

	private:
		template<typename TAddr>
		byte_patch(TAddr address, std::remove_pointer_t<std::remove_reference_t<TAddr>> value) :
			m_address(address)
		{
			m_size = sizeof(std::remove_pointer_t<std::remove_reference_t<TAddr>>);

			m_original_bytes = std::make_unique<byte[]>(m_size);
			memcpy(m_original_bytes.get(), m_address, m_size);

			m_value = std::make_unique<byte[]>(m_size);
			memcpy(m_value.get(), &value, m_size);
		}

		template<typename TAddr, typename T, std::size_t N>
		byte_patch(TAddr address, std::span<T, N> span) :
			m_address((void*)address)
		{
			m_size = span.size();

			m_original_bytes = std::make_unique<byte[]>(m_size);
			memcpy(m_original_bytes.get(), m_address, m_size);

			m_value = std::make_unique<byte[]>(m_size);
			for (int i = 0; i < m_size; i++)
				m_value[i] = span[i];
		}

	protected:
		static inline std::vector<std::unique_ptr<byte_patch>> m_patches;

	private:
		void* m_address;
		std::unique_ptr<byte[]> m_value;
		std::unique_ptr<byte[]> m_original_bytes;
		std::size_t m_size;

		friend bool operator==(const std::unique_ptr<byte_patch>& a, const byte_patch* b)
		{
			return a->m_address == b->m_address;
		};
	};

	template<typename ValueType, typename AddressType>
	static void patchAddress(AddressType address, ValueType value) {
		DWORD oldProtect;
		VirtualProtect((void*)address, sizeof(value), PAGE_EXECUTE_READWRITE, &oldProtect);

		memcpy((void*)address, &value, sizeof(value));

		VirtualProtect((void*)address, sizeof(value), oldProtect, &oldProtect);
	}

	template<typename AddressType>
	static void patchAddress(AddressType address, std::vector<DWORD> offsets) {
		for (int i = 0; i < offsets.size(); i++) {
			DWORD oldProtect;
			DWORD value = offsets[i];
			VirtualProtect((void*)(address + i), sizeof(value), PAGE_EXECUTE_READWRITE, &oldProtect);

			memcpy((void*)(address + i), &value, sizeof(value));

			VirtualProtect((void*)(address + i), sizeof(value), oldProtect, &oldProtect);
		}
	}

	template <typename ValueType, typename AddressType>
	void restorePatch(AddressType address, ValueType value)
	{
		DWORD oldProtect;
		VirtualProtect((void*)address, sizeof(value), PAGE_EXECUTE_READWRITE, &oldProtect);

		memcpy((void*)address, &value, sizeof(value));

		VirtualProtect((void*)address, sizeof(value), oldProtect, &oldProtect);
	}

	template <typename AddressType>
	void restorePatch(AddressType address, const std::vector<BYTE>& patchBytes)
	{
		DWORD oldProtect;
		VirtualProtect((void*)address, patchBytes.size(), PAGE_EXECUTE_READWRITE, &oldProtect);

		memcpy((void*)address, patchBytes.data(), patchBytes.size());

		VirtualProtect((void*)address, patchBytes.size(), oldProtect, &oldProtect);
	}
}