#pragma once

#include <tracy/Tracy.hpp>

#define RE_PROFILE 1

#if RE_PROFILE
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

	#define RE_PROFILE_SECTION() ZoneScoped

	#define RE_INTERNAL_PROFILE_TRACE_TRACE(...)    ::RealEngine::InternalProfilelog(std::format(__VA_ARGS__))
	#define RE_INTERNAL_PROFILE_TRACE_INFO(...)     ::RealEngine::InternalProfilelogColor(std::format(__VA_ARGS__), tracy::Color::Green)
	#define RE_INTERNAL_PROFILE_TRACE_WARN(...)     ::RealEngine::InternalProfilelogColor(std::format(__VA_ARGS__), tracy::Color::Yellow)
	#define RE_INTERNAL_PROFILE_TRACE_ERROR(...)    ::RealEngine::InternalProfilelogColor(std::format(__VA_ARGS__), tracy::Color::Red)
	#define RE_INTERNAL_PROFILE_TRACE_CRITICAL(...) ::RealEngine::InternalProfilelogColor(std::format(__VA_ARGS__), tracy::Color::Blue)

#else
	#define RE_PROFILE_FRAME()

	#define RE_PROFILE_FUNCTION()

	#define RE_PROFILE_SECTION()

	#define RE_INTERNAL_PROFILE_TRACE_TRACE(...)    
	#define RE_INTERNAL_PROFILE_TRACE_INFO(...)     
	#define RE_INTERNAL_PROFILE_TRACE_WARN(...)     
	#define RE_INTERNAL_PROFILE_TRACE_ERROR(...)    
	#define RE_INTERNAL_PROFILE_TRACE_CRITICAL(...) 
#endif