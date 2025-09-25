#pragma once

#include <filesystem>
#include <cstdio>
#include <string>

namespace RealEngine {
	class FileHelper {
	public:
		FileHelper(const std::filesystem::path& filePath, const char* mode);
		~FileHelper();

		std::string ReadAllText();

		FILE* GetFileHandle() const { return m_File; }
	private:
		FILE* m_File = nullptr;
	};
}