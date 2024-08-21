#include "StringHash.h"

#include <xxhash.h>

namespace RealEngine {
	StringHash::StringHash(const std::string& string) {
		RE_PROFILE_FUNCTION();
		m_Hash = XXH32(string.c_str(), string.size(), 0);

#ifdef RE_DEBUG
		m_String = string;
#endif
	}

	StringHash::StringHash(const char* string) {
		RE_PROFILE_FUNCTION();
		m_Hash = XXH32(string, strlen(string), 0);

#ifdef RE_DEBUG
		m_String = string;
#endif
	}
}