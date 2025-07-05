#pragma once
#include "RealEngine/Logger/Log.h"

#include <ryml.hpp>

namespace RealEngine {
	/**
	 * @brief Callback function invoked on YAML parsing errors.
	 *
	 * Logs the error message and the source location (file, line, column),
	 * then aborts the program.
	 *
	 * @param msg Error message string.
	 * @param len Length of the error message.
	 * @param loc Location information from ryml parser.
	 * @param userData User data pointer (unused).
	 */
	C4_NORETURN static void YAMLErrorCallBack(const char* msg, size_t len, ryml::Location loc, void* userData) {
		RE_CORE_CRITICAL("YAML Parsing Error: {}", msg); 

		std::filesystem::path codeFileName = std::filesystem::path(std::string_view(loc.name.begin(), loc.name.end()));
		RE_CORE_CRITICAL("Location: {0}:{1}:{2}", codeFileName.filename(), loc.line, loc.col);

		abort();
	}

	/**
	 * @brief Sets the YAML parser error callbacks to use YAMLErrorCallBack.
	 *
	 * Should be called once during initialization before parsing YAML.
	 */
	inline void SetYAMLErrorCallbacks() {
		ryml::set_callbacks(ryml::Callbacks(nullptr, nullptr, nullptr, YAMLErrorCallBack));
	}
}
