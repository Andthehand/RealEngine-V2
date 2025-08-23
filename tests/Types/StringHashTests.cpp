#include <gtest/gtest.h>
#include <string>
#include <cstdint>

#include "RealEngine/Types/StringHash.h"

using namespace RealEngine;

// Compile-time checks
namespace {
    constexpr uint32_t fnv1a32(const char* s) {
        uint32_t h = 2166136261u;
        for (size_t i = 0; s[i] != '\0'; ++i) {
            h ^= static_cast<uint32_t>(static_cast<unsigned char>(s[i]));
            h *= 16777619u;
        }
        return h;
    }
}

static_assert(static_cast<uint32_t>(StringHash::StaticHash("")) == fnv1a32(""),
              "StaticHash(\"\") must match FNV-1a at compile time");
static_assert(static_cast<uint32_t>(StringHash::StaticHash("a")) == fnv1a32("a"),
              "StaticHash(\"a\") must match FNV-1a at compile time");
static_assert(static_cast<uint32_t>(StringHash::StaticHash("hello")) == fnv1a32("hello"),
              "StaticHash(\"hello\") must match FNV-1a at compile time");
static_assert(static_cast<uint32_t>(StringHash::StaticHash("RealEngine")) == fnv1a32("RealEngine"),
              "StaticHash(\"RealEngine\") must match FNV-1a at compile time");
static_assert(static_cast<uint32_t>(StringHash::StaticHash("The quick brown fox jumps over the lazy dog")) == fnv1a32("The quick brown fox jumps over the lazy dog"),
              "StaticHash(long literal) must match FNV-1a at compile time");

TEST(StringHashTests, StaticVsRuntimeAgree) {
    auto check = [](const char* s) {
        // Compare constexpr StaticHash with runtime constructors
        uint32_t staticHash = static_cast<uint32_t>(StringHash::StaticHash(s));
        uint32_t runtimeFromCStr = static_cast<uint32_t>(StringHash(s));
        uint32_t runtimeFromStd = static_cast<uint32_t>(StringHash(std::string{s}));
        EXPECT_EQ(staticHash, runtimeFromCStr) << "Mismatch for cstr: " << s;
        EXPECT_EQ(staticHash, runtimeFromStd) << "Mismatch for std::string: " << s;
        EXPECT_EQ(runtimeFromCStr, runtimeFromStd) << "Runtime mismatch between cstr and std::string: " << s;
    };

    check("");
    check("a");
    check("hello");
    check("RealEngine");
    check("The quick brown fox jumps over the lazy dog");
}

TEST(StringHashTests, EqualityAndInequality) {
    StringHash a1("alpha");
    StringHash a2(std::string{"alpha"});
    StringHash b("beta");

    EXPECT_TRUE(a1 == a2);
    EXPECT_FALSE(a1 != a2);

    EXPECT_NE(static_cast<uint32_t>(a1), static_cast<uint32_t>(b));
    EXPECT_TRUE(a1 != b);
    EXPECT_FALSE(a1 == b);
}

TEST(StringHashTests, ConversionOperatorToUint32) {
    StringHash h("value");
    uint32_t v1 = static_cast<uint32_t>(h);
    uint32_t v2 = static_cast<uint32_t>(StringHash("value"));
    EXPECT_EQ(v1, v2);
}

TEST(StringHashTests, EmptyStringProducesOffsetBasis) {
    // FNV-1a 32-bit offset basis
    constexpr uint32_t offsetBasis = 2166136261u;
    uint32_t runtimeEmpty = static_cast<uint32_t>(StringHash(""));
    uint32_t staticEmpty = static_cast<uint32_t>(StringHash::StaticHash(""));
    EXPECT_EQ(runtimeEmpty, offsetBasis);
    EXPECT_EQ(staticEmpty, offsetBasis);
}