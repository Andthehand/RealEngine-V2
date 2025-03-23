#pragma once
#include "RealEngine/Logger/Log.h"

#include <ryml.hpp>

namespace RealEngine {
	C4_NORETURN static void YAMLErrorCallBack(const char* msg, size_t len, ryml::Location loc, void* userData) {
		RE_CORE_CRITICAL("YAML Parsing Error: {}", msg); 

		std::filesystem::path codeFileName = std::filesystem::path(std::string_view(loc.name.begin(), loc.name.end()));
		RE_CORE_CRITICAL("Location: {0}:{1}:{2}", codeFileName.filename(), loc.line, loc.col);

		abort();
	}

	inline void SetYAMLErrorCallbacks() {
		ryml::set_callbacks(ryml::Callbacks(nullptr, nullptr, nullptr, YAMLErrorCallBack));
	}
}
