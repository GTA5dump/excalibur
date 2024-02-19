#pragma once
#include <type_traits>

namespace detail {
	extern "C" void* _spooferStub();
	template <typename Ret, typename... Args>
	inline Ret shellcodeStubHelper(const void* shell, Args... args) {
		auto fn = (Ret(*)(Args...))(shell);
		return fn(args...);
	}
	template <size_t argC, typename>
	struct argumentRemapper {
		template <typename ret, typename first, typename second, typename third, typename fourth, typename ...pack>
		static auto call(const void* shell, void* shellParam, first fr, second sc, third tr, fourth ft, pack... pc) -> ret {
			return shellcodeStubHelper<ret, first, second, third, fourth, void*, void*, pack...>(shell, fr, sc, tr, ft, shellParam, nullptr, pc...);
		}
	};
	template <size_t argC>
	struct argumentRemapper<argC, std::enable_if_t<argC <= 4>> {
		// 4 or less params
		template<typename ret, typename first = void*, typename second = void*, typename third = void*, typename fourth = void*>
		static auto call(const void* shell, void* shellParam, first fr = {}, second sc = {}, third tr = {}, fourth ft = {}) -> ret {
			return shellcodeStubHelper<ret, first, second, third, fourth, void*, void*>(shell, fr, sc, tr, ft, shellParam, nullptr);
		}
	};
}

struct shellParams { const void* trampoline; void* function; void* reg; };
template <typename ret, typename ...arguments>
static inline auto spoof_call(const void* trampoline, ret(*fn)(arguments...), arguments... args) -> ret {
	shellParams p{ trampoline, (void*)(fn) };
	using mapper = detail::argumentRemapper<sizeof...(arguments), void>;
	return mapper::template call<ret, arguments...>((const void*)&detail::_spooferStub, &p, args...);
}