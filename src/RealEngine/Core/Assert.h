/**
 * @file Assert.h
 * @brief Runtime and static assertion macros for RealEngine.
 *
 * Provides macros for debug-time runtime assertions (`RE_ASSERT`, `RE_CORE_ASSERT`) and compile-time assertions (`RE_CORE_STATIC_ASSERT`),
 * with optional custom error messages. If an assertion fails, a critical log message is printed and execution is interrupted.
 *
 * Assertions are only active if `RE_ENABLE_ASSERTS` is defined.
 *
 * @note These macros automatically insert file and line number context in log output.
 */

#pragma once
#include <filesystem>

#include "RealEngine/Core/Core.h"
#include "RealEngine/Logger/Log.h"

#ifdef RE_ENABLE_ASSERTS

	// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define RE_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { RE##type##CRITICAL(msg, __VA_ARGS__); ::RealEngine::Log::Flush(); RE_DEBUGBREAK(); } }
	#define RE_INTERNAL_ASSERT_NO_MSG(type, check) RE_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: '{0}' {1}:{2}", RE_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)
	#define RE_INTERNAL_ASSERT_WITH_MSG(type, check, ...) RE_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: '{0}' {1}:{2}", __VA_ARGS__, std::filesystem::path(__FILE__).filename().string(), __LINE__)
	#define RE_INTERNAL_ASSERT_WITH_MSG_AND_ARGS(type, check, msg, ...) RE_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: '" msg "'", __VA_ARGS__)

	#define RE_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, arg3, macro, ...) macro
	#define RE_INTERNAL_ASSERT_GET_MACRO(...) RE_EXPAND_MACRO( RE_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, RE_INTERNAL_ASSERT_WITH_MSG_AND_ARGS, RE_INTERNAL_ASSERT_WITH_MSG, RE_INTERNAL_ASSERT_NO_MSG) )

	/**
	 * @def RE_ASSERT(...)
	 * @brief Runtime assertion for application-level checks.
	 * Disabled if RE_ENABLE_ASSERTS is not defined.
	 */
	#define RE_ASSERT(...) RE_EXPAND_MACRO( RE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	/**
	* @def RE_CORE_ASSERT(...)
	* @brief Runtime assertion for engine/core-level checks.
	* Disabled if RE_ENABLE_ASSERTS is not defined.
	*/
	#define RE_CORE_ASSERT(...) RE_EXPAND_MACRO( RE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )

	/**
	 * @def RE_CORE_STATIC_ASSERT(...)
	 * @brief Compile-time assertion, wraps C++ `static_assert`.
	 */
	#define RE_CORE_STATIC_ASSERT(...) static_assert(__VA_ARGS__)
#else
	#pragma warning( disable : 4552 4189 )
	#define RE_CORE_STATIC_ASSERT(...)

	#define RE_ASSERT(...)
	#define RE_CORE_ASSERT(...)
#endif