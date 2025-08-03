#pragma once
#include "RealEngine/Core/Core.h"
#include "RealEngine/Core/Profiler.h"

#pragma warning(push, 0)
#include <quill/Logger.h>
#include <quill/LogMacros.h>

#include <quill/Backend.h>
#include <quill/Frontend.h>
#include <quill/sinks/ConsoleSink.h>
#include <quill/sinks/FileSink.h>
#pragma warning(pop)

namespace RealEngine {
	/**
	 * @brief Logging utility that wraps Quill for engine and client logging.
	 */
	class Logger {
	public:
		/**
		* @brief Initializes the logging system.
		*
		* Should be called once at application startup.
		*/
		static void Init();

		inline static void Flush() { 
			s_CoreLogger->flush_log();
			s_ClientLogger->flush_log();
		}

		inline static quill::Logger* GetCoreLogger() { return s_CoreLogger; }
		inline static quill::Logger* GetClientLogger() { return s_ClientLogger; }
	private:
		// Does not own the logger, it is created and managed by the quill::Backend
		static quill::Logger* s_CoreLogger;
		static quill::Logger* s_ClientLogger;
	};
}

// -------------------------------
// Core (engine) logging macros
// -------------------------------
#define RE_CORE_TRACE(...)		LOG_TRACE_L1(::RealEngine::Logger::GetCoreLogger(), __VA_ARGS__);		RE_INTERNAL_PROFILE_TRACE_TRACE(__VA_ARGS__)
#define RE_CORE_INFO(...)		LOG_INFO(::RealEngine::Logger::GetCoreLogger(), __VA_ARGS__);			RE_INTERNAL_PROFILE_TRACE_INFO(__VA_ARGS__)
#define RE_CORE_WARN(...)		LOG_WARNING(::RealEngine::Logger::GetCoreLogger(), __VA_ARGS__);		RE_INTERNAL_PROFILE_TRACE_WARN(__VA_ARGS__)
#define RE_CORE_ERROR(...)		LOG_ERROR(::RealEngine::Logger::GetCoreLogger(), __VA_ARGS__);			RE_INTERNAL_PROFILE_TRACE_ERROR(__VA_ARGS__)
#define RE_CORE_CRITICAL(...)	LOG_CRITICAL(::RealEngine::Logger::GetCoreLogger(), __VA_ARGS__);		RE_INTERNAL_PROFILE_TRACE_CRITICAL(__VA_ARGS__)

// -------------------------------
// Client (game/app) logging macros
// -------------------------------																	   
#define RE_TRACE(...)		LOG_TRACE_L1(::RealEngine::Logger::GetClientLogger(), __VA_ARGS__);		RE_INTERNAL_PROFILE_TRACE_TRACE(__VA_ARGS__)
#define RE_INFO(...)		LOG_INFO(::RealEngine::Logger::GetClientLogger(), __VA_ARGS__);			RE_INTERNAL_PROFILE_TRACE_INFO(__VA_ARGS__)
#define RE_WARN(...)		LOG_WARNING(::RealEngine::Logger::GetClientLogger(), __VA_ARGS__);			RE_INTERNAL_PROFILE_TRACE_WARN(__VA_ARGS__)
#define RE_ERROR(...)		LOG_ERROR(::RealEngine::Logger::GetClientLogger(), __VA_ARGS__);			RE_INTERNAL_PROFILE_TRACE_ERROR(__VA_ARGS__)
#define RE_CRITICAL(...)	LOG_CRITICAL(::RealEngine::Logger::GetClientLogger(), __VA_ARGS__);		RE_INTERNAL_PROFILE_TRACE_CRITICAL(__VA_ARGS__)