#pragma once
#include "RealEngine/Core/Core.h"
#include "RealEngine/Core/Profiler.h"

#pragma warning(push, 0)
#include <quill/Logger.h>
#include <quill/LogMacros.h>
#pragma warning(pop)

namespace RealEngine {
	class Log {
	public:
		static void Init();

		inline static quill::Logger* GetCoreLogger() { return s_CoreLogger; }
		inline static quill::Logger* GetClientLogger() { return s_ClientLogger; }
	private:
		// Does not own the logger, it is created and managed by the quill::Backend
		static quill::Logger* s_CoreLogger;
		static quill::Logger* s_ClientLogger;
	};
}

//Core log macros
#define RE_CORE_TRACE(...)		LOG_TRACE_L1(::RealEngine::Log::GetCoreLogger(), __VA_ARGS__);		RE_INTERNAL_PROFILE_TRACE_TRACE(__VA_ARGS__)
#define RE_CORE_INFO(...)		LOG_INFO(::RealEngine::Log::GetCoreLogger(), __VA_ARGS__);			RE_INTERNAL_PROFILE_TRACE_WARN(__VA_ARGS__)
#define RE_CORE_WARN(...)		LOG_WARNING(::RealEngine::Log::GetCoreLogger(), __VA_ARGS__);			RE_INTERNAL_PROFILE_TRACE_WARN(__VA_ARGS__)
#define RE_CORE_ERROR(...)		LOG_ERROR(::RealEngine::Log::GetCoreLogger(), __VA_ARGS__);			RE_INTERNAL_PROFILE_TRACE_ERROR(__VA_ARGS__)
#define RE_CORE_CRITICAL(...)	LOG_CRITICAL(::RealEngine::Log::GetCoreLogger(), __VA_ARGS__);		RE_INTERNAL_PROFILE_TRACE_CRITICAL(__VA_ARGS__)
																						   
//Client log macros																		   
#define RE_TRACE(...)		LOG_TRACE_L1(::RealEngine::Log::GetClientLogger(), __VA_ARGS__);			RE_INTERNAL_PROFILE_TRACE_TRACE(__VA_ARGS__)
#define RE_INFO(...)		LOG_INFO(::RealEngine::Log::GetClientLogger(), __VA_ARGS__);			RE_INTERNAL_PROFILE_TRACE_TRACE(__VA_ARGS__)
#define RE_WARN(...)		LOG_WARNING(::RealEngine::Log::GetClientLogger(), __VA_ARGS__);			RE_INTERNAL_PROFILE_TRACE_WARN(__VA_ARGS__)
#define RE_ERROR(...)		LOG_ERROR(::RealEngine::Log::GetClientLogger(), __VA_ARGS__);				RE_INTERNAL_PROFILE_TRACE_ERROR(__VA_ARGS__)
#define RE_CRITICAL(...)	LOG_CRITICAL(::RealEngine::Log::GetClientLogger(), __VA_ARGS__);			RE_INTERNAL_PROFILE_TRACE_CRITICAL(__VA_ARGS__)