#include <gtest/gtest.h>

#include "RealEngine.h"

using namespace RealEngine;

struct TestComponent {
    int value{};
};

TEST(SceneTests, GetEntity_ByUUID_ReturnsSameEntityHandle)
{
    Scene scene;

    UUID id{123456789ULL};
    Entity e1 = scene.CreateEntity(id, "TestEntity");

    EXPECT_FALSE(e1.HasComponent<TestComponent>());

    Entity e2 = scene.GetEntity(id);
    e2.AddComponent<TestComponent>(TestComponent{42});

    EXPECT_TRUE(e1.HasComponent<TestComponent>());
    EXPECT_TRUE(e2.HasComponent<TestComponent>());
    EXPECT_EQ(e1.GetComponent<TestComponent>().value, 42);
    EXPECT_EQ(e2.GetComponent<TestComponent>().value, 42);
}
