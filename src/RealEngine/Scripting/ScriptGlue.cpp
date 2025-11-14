#include "ScriptGlue.h"

#define RE_ADD_INTERNAL_CALL(functionName) \
	assembly.AddInternalCall("RealEngine.InternalCalls", #functionName, reinterpret_cast<void*>(&functionName));

namespace RealEngine {
	enum class LogLevel {
		Trace = 0,
		Info = 1,
		Warn = 2,
		Error = 3,
		Critical = 4
	};

	static void NativeLog(LogLevel level, Coral::String message) {
		switch (level) {
			case LogLevel::Trace:		RE_TRACE("{}", std::string(message)); break;
			case LogLevel::Info:		RE_INFO("{}", std::string(message)); break;
			case LogLevel::Warn:		RE_WARN("{}", std::string(message)); break;
			case LogLevel::Error:		RE_ERROR("{}", std::string(message)); break;
			case LogLevel::Critical:	RE_CRITICAL("{}", std::string(message)); break;
			default: 
				RE_CORE_ASSERT(false, "Unknown log level!"); 
				break;
		}
	}

	void ScriptGlue::RegisterFunctions(Coral::ManagedAssembly& assembly) {
		RE_ADD_INTERNAL_CALL(NativeLog);

		assembly.UploadInternalCalls();
	}
}