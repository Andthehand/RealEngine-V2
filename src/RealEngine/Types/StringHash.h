#pragma once

#include <string>
#include <cstdint>

namespace RealEngine {
    class StringHash {
    public:
        explicit StringHash(const std::string& string);
        explicit StringHash(const char* string);

        static constexpr StringHash StaticHash(const char* str) {
            return StringHash(ConstexprFnv1aHash(str));
        }

        constexpr operator uint32_t() const { return m_Hash; }

        constexpr bool operator==(const StringHash& other) const { return m_Hash == other.m_Hash; }
        constexpr bool operator!=(const StringHash& other) const { return m_Hash != other.m_Hash; }
    private:
        constexpr explicit StringHash(uint32_t hash) : m_Hash(hash) {}

        void InitDebugString(const char* str);

        static uint32_t HashRuntime(const char* str);
        static constexpr uint32_t ConstexprFnv1aHash(const char* str, uint32_t hash = 2166136261u) {
            return (*str == '\0') ? hash : ConstexprFnv1aHash(str + 1, (hash ^ static_cast<uint32_t>(*str)) * 16777619u);
        }
    private:
        uint32_t m_Hash;

#ifdef RE_DEBUG
        std::string m_String;
#endif
    };
}
