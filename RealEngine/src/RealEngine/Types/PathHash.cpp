#include "PathHash.h"

#include <xxhash.h>

namespace RealEngine {
	PathHash::PathHash(const std::filesystem::path& path) {
		RE_PROFILE_FUNCTION();

		m_Hash = XXH32(path.c_str(), path.string().size(), 0);

#ifdef RE_DEBUG
		m_String = path;
#endif
	}

	PathHash::PathHash(const char* path) {
		RE_PROFILE_FUNCTION();
		m_Hash = XXH32(path, strlen(path), 0);

#ifdef RE_DEBUG
		m_String = path;
#endif
	}
}