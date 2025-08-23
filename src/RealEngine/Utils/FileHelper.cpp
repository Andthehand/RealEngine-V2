#include "FileHelper.h"

namespace RealEngine {

	FileHelper::FileHelper(std::filesystem::path filePath, const char* mode) {
#if defined(_MSC_VER)
		if (fopen_s(&m_File, filePath.string().c_str(), mode) != 0) {
			m_File = nullptr;
		}
#else
		m_File = fopen(filePath.string().c_str(), "w");
#endif
		
		RE_CORE_ASSERT(m_File, "Failed to open file: {0}", filePath.string());
	}

	FileHelper::~FileHelper() {
		if (m_File) {
			fclose(m_File);
		}
	}

	std::string FileHelper::ReadAllText() {
		if (!m_File) return std::string();

		// Reserve capacity using file size (approximate, especially in text mode), then read to EOF.
		long endPos = -1;
		if (fseek(m_File, 0, SEEK_END) == 0) {
			endPos = ftell(m_File);
		}
		rewind(m_File);

		std::string result;
		if (endPos > 0) {
			result.reserve(static_cast<size_t>(endPos));
		}

		// Read in chunks to handle large files.
		char buffer[8192];
		for (;;) {
			size_t n = fread(buffer, 1, sizeof(buffer), m_File);
			if (n > 0) result.append(buffer, n);
			if (n < sizeof(buffer)) break; // EOF or error
		}

		// Leave the file at EOF, mirroring typical whole-file read behavior.
		return result;
	}
}
