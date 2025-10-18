#pragma once

#include "RealEngine/Types/RingBuffer.h"

#include <quill/sinks/Sink.h>

namespace RealEngine {
    struct ImGuiLog {
        std::string Text;
		quill::LogLevel Severity;
    };

	class ImGuiLogSink : public quill::Sink {
    public:
        ImGuiLogSink() = default;

        // The write_log signature varies across Quill releases. The
        // implementation below follows the official examples and receives the
        // formatted log text in `log_statement`.
        void write_log(
            quill::MacroMetadata const* /*log_metadata*/, 
            uint64_t /*log_timestamp*/, 
            std::string_view /*thread_id*/,
            std::string_view /*thread_name*/, 
            std::string const& /*process_id*/, 
            std::string_view logger_name,
            quill::LogLevel log_level,
            std::string_view /*log_level_description*/, 
            std::string_view /*log_level_short_code*/,
            std::vector<std::pair<std::string, std::string>> const* /*named_args*/,
            std::string_view log_message, 
            std::string_view /*log_statement*/) noexcept override {
            // log_statement contains the already-formatted message (pattern applied).
            // We copy to a std::string and push into the queue for the UI thread.
            // Keep write_log very small and noexcept to avoid destabilizing the backend.
            g_Queue.Push(ImGuiLog{ std::string(std::string(logger_name) + ": " + std::string(log_message)), log_level });
        }

        void flush_sink() override {
            // No-op
		}

		static RingBuffer<1024, ImGuiLog>& GetQueue() { return g_Queue; }
    private:
		static inline RingBuffer<1024, ImGuiLog> g_Queue;
	};
}