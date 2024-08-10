#pragma once
#include <memory>

#ifdef RE_DEBUG
	#if defined(RE_PLATFORM_WINDOWS)
		#define RE_DEBUGBREAK() __debugbreak()
	#elif defined(RE_PLATFORM_LINUX)
		#include <signal.h>
		#define RE_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
		#define RE_ENABLE_ASSERTS
	#else
		#define RE_DEBUGBREAK()
#endif

namespace RealEngine {
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}