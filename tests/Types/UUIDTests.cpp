#include <gtest/gtest.h>
#include <unordered_set>
#include <unordered_map>

#include "RealEngine/Types/UUID.h"

using RealEngine::UUID;

TEST(UUIDTests, DefaultConstructorProducesDifferentValuesConsecutively) {
    UUID a;
    UUID b;
    EXPECT_NE(static_cast<uint64_t>(a), static_cast<uint64_t>(b));
}

TEST(UUIDTests, ValueConstructorSetsExactValue) {
    uint64_t v = 0x1234'5678'9ABC'DEF0ull;
    UUID u(v);
    EXPECT_EQ(static_cast<uint64_t>(u), v);
}

TEST(UUIDTests, EqualityAndInequalityOperators) {
    UUID a(42);
    UUID b(42);
    UUID c(43);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);

    EXPECT_TRUE(a != c);
    EXPECT_FALSE(a == c);
}

TEST(UUIDTests, ConversionOperatorToUint64) {
    uint64_t v = 987654321ull;
    UUID u(v);
    uint64_t out = static_cast<uint64_t>(u);
    EXPECT_EQ(out, v);
}

TEST(UUIDTests, CopyAndAssignmentPreserveValue) {
    UUID a(777);
    UUID b = a;           // copy-construct
    UUID c(0);
    c = a;                // copy-assign

    EXPECT_EQ(static_cast<uint64_t>(a), static_cast<uint64_t>(b));
    EXPECT_EQ(static_cast<uint64_t>(a), static_cast<uint64_t>(c));
}

TEST(UUIDTests, HashSpecializationWorksInUnorderedContainers) {
    UUID a(1);
    UUID b(1);
    UUID c(2);

    std::unordered_set<UUID> s;
    s.insert(a);
    s.insert(b); // same value, should not increase size
    s.insert(c);
    EXPECT_EQ(s.size(), 2u);
    EXPECT_TRUE(s.find(a) != s.end());
    EXPECT_TRUE(s.find(c) != s.end());

    std::unordered_map<UUID, int> m;
    m[a] = 10;
    m[b] = 20; // should overwrite same key
    m[c] = 30;

    EXPECT_EQ(m.size(), 2u);
    EXPECT_EQ(m[a], 20);
    EXPECT_EQ(m[c], 30);
}