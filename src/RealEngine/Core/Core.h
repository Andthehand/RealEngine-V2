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

#ifdef _MSC_VER
	/**
	 * @brief Defines a packed struct for MSVC compiler.
	 * Usage: PACKED_STRUCT(Name) { ... };
	 */
	#define PACKED_STRUCT(name) __pragma(pack(push, 1)) struct name __pragma(pack(pop))
#elif defined(__GNUC__)
	/**
     * @brief Defines a packed struct for GCC/Clang compilers.
     * Usage: PACKED_STRUCT(Name) { ... };
     */
	#define PACKED_STRUCT(name) struct __attribute__((packed)) name
#endif

/// Expands a macro argument (used internally to ensure proper macro expansion).
#define RE_EXPAND_MACRO(x) x
/// Converts a macro argument to a string literal.
#define RE_STRINGIFY_MACRO(x) #x

/**
 * @brief Helper macro to bind member functions to event callbacks.
 *
 * Example usage:
 * @code
 * EventDispatcher dispatcher(e);
 * dispatcher.Dispatch<WindowCloseEvent>(RE_BIND_EVENT_FN(Application::OnWindowClose));
 * @endcode
 *
 * It creates a lambda that perfectly forwards arguments to the class member function.
 */
#define RE_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
#define RE_RAISE_EVENT(event) ::RealEngine::Application::Get().OnEvent(std::move(event))

namespace RealEngine {
	/// Alias for std::unique_ptr (scope-based ownership).
	template<typename T>
	using Scope = std::unique_ptr<T>;

	/**
	 * @brief Creates a Scope (unique_ptr) instance.
	 * @tparam T The type to allocate.
	 * @tparam Args Constructor argument types.
	 * @param args Arguments forwarded to T's constructor.
	 * @return A std::unique_ptr managing the new instance.
	 */
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) {
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	/// Alias for std::shared_ptr (reference-counted ownership).
	template<typename T>
	using Ref = std::shared_ptr<T>;

	/**
	 * @brief Creates a Ref (shared_ptr) instance.
	 * @tparam T The type to allocate.
	 * @tparam Args Constructor argument types.
	 * @param args Arguments forwarded to T's constructor.
	 * @return A std::shared_ptr managing the new instance.
	 */
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) {
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	/// Alias for std::weak_ptr (non-owning weak reference).
	template<typename T>
	using Weak_Ref = std::weak_ptr<T>;

	/**
	 * @brief Creates a Weak_Ref (weak_ptr) instance.
	 * @tparam T The type to reference.
	 * @tparam Args Constructor argument types.
	 * @return A std::weak_ptr instance.
	 */
	template<typename T, typename ... Args>
	constexpr Weak_Ref<T> CreateWeakRef() {
		return std::weak_ptr<T>();
	}
}