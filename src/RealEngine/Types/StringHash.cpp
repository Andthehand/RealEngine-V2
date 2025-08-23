#include "StringHash.h"

namespace RealEngine {
    StringHash::StringHash(const std::string& string)
        : m_Hash(HashRuntime(string.c_str())) {
        InitDebugString(string.c_str());
    }

    StringHash::StringHash(const char* string) {
        if (string == nullptr) {
            m_Hash = HashRuntime("");
            InitDebugString("");
        }
        else {
            m_Hash = HashRuntime(string);
            InitDebugString(string);
        }
    }

#ifdef RE_DEBUG
    void StringHash::InitDebugString(const char* str) {
        m_String = std::string(str);
    }
#else
    void StringHash::InitDebugString(const char*) {}
#endif

    uint32_t StringHash::HashRuntime(const char* str) {
        uint32_t hash = 2166136261u;
        while (*str) {
            hash ^= static_cast<uint32_t>(*str++);
            hash *= 16777619u;
        }
        return hash;
    }
}
