#pragma once

#include <filesystem>

namespace RealEngine {
	class FileDialogs {
	public:
		static std::filesystem::path OpenFile(const char* filter = "");
		static std::filesystem::path SaveFile(const char* filter = "");
	};

	class InfoDialog {
		public:
		static void WarnUser(const std::string& title, const std::string& message);
	};
}