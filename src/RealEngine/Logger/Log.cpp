#include "Log.h"

namespace RealEngine {
	quill::Logger* Log::s_CoreLogger;
	quill::Logger* Log::s_ClientLogger;

	void Log::Init() {
		quill::Backend::start();

		auto console_sink = quill::Frontend::create_or_get_sink<quill::ConsoleSink>("RealEngine_Console_Sink");
		auto file_sink = quill::Frontend::create_or_get_sink<quill::FileSink>("logs/RealEngine.log", []() {
			quill::FileSinkConfig cfg;
			cfg.set_open_mode('w');
			cfg.set_filename_append_option(quill::FilenameAppendOption::None);
			return cfg;
		}(), quill::FileEventNotifier{});

		s_CoreLogger = quill::Frontend::create_or_get_logger("RealEngine", { console_sink, file_sink },
			quill::PatternFormatterOptions("[%(time)] [%(log_level)] %(logger): %(message)", "%H:%M:%S"));
		s_ClientLogger = quill::Frontend::create_or_get_logger("APP", { console_sink, file_sink },
			quill::PatternFormatterOptions("[%(time)] [%(log_level)] %(logger): %(message)", "%H:%M:%S"));

		s_CoreLogger->set_log_level(quill::LogLevel::TraceL1);
		s_ClientLogger->set_log_level(quill::LogLevel::TraceL1);
	}
}