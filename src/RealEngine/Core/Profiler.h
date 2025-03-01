#pragma once
#include <spdlog/fmt/bundled/format.h>

#define RE_PROFILE 1

#if RE_PROFILE && defined(TRACY_ENABLE) 
	#define TRACY_CALLSTACK 8
	#include <tracy/Tracy.hpp>

	namespace RealEngine {
		inline void InternalProfilelog(std::string text) {
			TracyMessage(text.c_str(), text.length());
		}

		inline void InternalProfilelogColor(std::string text, uint32_t color) {
			TracyMessageC(text.c_str(), text.length(), color);
		}
	}

	#define RE_PROFILE_FRAME() FrameMark

	#define RE_PROFILE_FUNCTION() ZoneScoped

	#define RE_PROFILE_SCOPE(name) ZoneScopedN(name)


	#define RE_INTERNAL_PROFILE_FORMAT(text, ...) text

	#define RE_INTERNAL_PROFILE_TRACE_TRACE(text, ...)		::RealEngine::InternalProfilelog(RE_INTERNAL_PROFILE_FORMAT(__VA_OPT__(fmt::format(text, __VA_ARGS__) ,) text))
	#define RE_INTERNAL_PROFILE_TRACE_INFO(text, ...)		::RealEngine::InternalProfilelogColor(RE_INTERNAL_PROFILE_FORMAT(__VA_OPT__(fmt::format(text, __VA_ARGS__) ,) text), tracy::Color::Green)
	#define RE_INTERNAL_PROFILE_TRACE_WARN(text, ...)		::RealEngine::InternalProfilelogColor(RE_INTERNAL_PROFILE_FORMAT(__VA_OPT__(fmt::format(text, __VA_ARGS__) ,) text), tracy::Color::Yellow)
	#define RE_INTERNAL_PROFILE_TRACE_ERROR(text, ...)		::RealEngine::InternalProfilelogColor(RE_INTERNAL_PROFILE_FORMAT(__VA_OPT__(fmt::format(text, __VA_ARGS__) ,) text), tracy::Color::Red)
	#define RE_INTERNAL_PROFILE_TRACE_CRITICAL(text, ...)	::RealEngine::InternalProfilelogColor(RE_INTERNAL_PROFILE_FORMAT(__VA_OPT__(fmt::format(text, __VA_ARGS__) ,) text), tracy::Color::Blue)

#else
	#define RE_PROFILE_FRAME()

	#define RE_PROFILE_FUNCTION()

	#define RE_PROFILE_SCOPE(name)

	#define RE_INTERNAL_PROFILE_TRACE_TRACE(...)    
	#define RE_INTERNAL_PROFILE_TRACE_INFO(...)     
	#define RE_INTERNAL_PROFILE_TRACE_WARN(...)     
	#define RE_INTERNAL_PROFILE_TRACE_ERROR(...)    
	#define RE_INTERNAL_PROFILE_TRACE_CRITICAL(...) 
#endif
