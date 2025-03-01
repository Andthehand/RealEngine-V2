#pragma once
#include "Core.h"
#include "Profiler.h"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)


namespace RealEngine {
	class Log {
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};

}

//Core log macros
#define RE_CORE_TRACE(...)    ::RealEngine::Log::GetCoreLogger()->trace(__VA_ARGS__);	   RE_INTERNAL_PROFILE_TRACE_TRACE(__VA_ARGS__)
#define RE_CORE_INFO(...)     ::RealEngine::Log::GetCoreLogger()->info(__VA_ARGS__);	   RE_INTERNAL_PROFILE_TRACE_INFO(__VA_ARGS__)
#define RE_CORE_WARN(...)     ::RealEngine::Log::GetCoreLogger()->warn(__VA_ARGS__);	   RE_INTERNAL_PROFILE_TRACE_WARN(__VA_ARGS__)
#define RE_CORE_ERROR(...)    ::RealEngine::Log::GetCoreLogger()->error(__VA_ARGS__);	   RE_INTERNAL_PROFILE_TRACE_ERROR(__VA_ARGS__)
#define RE_CORE_CRITICAL(...) ::RealEngine::Log::GetCoreLogger()->critical(__VA_ARGS__);   RE_INTERNAL_PROFILE_TRACE_CRITICAL(__VA_ARGS__)
																						   
//Client log macros																		   
#define RE_TRACE(...)         ::RealEngine::Log::GetClientLogger()->trace(__VA_ARGS__);	   RE_INTERNAL_PROFILE_TRACE_TRACE(__VA_ARGS__)
#define RE_INFO(...)          ::RealEngine::Log::GetClientLogger()->info(__VA_ARGS__);	   RE_INTERNAL_PROFILE_TRACE_INFO(__VA_ARGS__)
#define RE_WARN(...)          ::RealEngine::Log::GetClientLogger()->warn(__VA_ARGS__);	   RE_INTERNAL_PROFILE_TRACE_WARN(__VA_ARGS__)
#define RE_ERROR(...)         ::RealEngine::Log::GetClientLogger()->error(__VA_ARGS__);	   RE_INTERNAL_PROFILE_TRACE_ERROR(__VA_ARGS__)
#define RE_CRITICAL(...)      ::RealEngine::Log::GetClientLogger()->critical(__VA_ARGS__); RE_INTERNAL_PROFILE_TRACE_CRITICAL(__VA_ARGS__)