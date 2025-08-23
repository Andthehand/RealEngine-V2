#include <gtest/gtest.h>

#include <ryml.hpp>
#include <ryml_std.hpp>

#include "RealEngine.h"

using namespace RealEngine;

class ComponentSerializerTest : public ::testing::Test {
protected:
    ryml::Tree tree;
    ryml::NodeRef root;

    void SetUp() override {
        root = tree.rootref();
        root |= ryml::MAP;
    }
};

TEST_F(ComponentSerializerTest, TagComponent_SerializeDeserialize) {
    TagComponent originalTag("Player");
    // Serialize
    ComponentSerializer<TagComponent>::Serialize(root, originalTag);

    ASSERT_TRUE(root.has_child("TagComponent"));
    auto tagNode = root["TagComponent"];
    ASSERT_TRUE(tagNode.has_child("Tag"));
    std::string tagValue;
    tagNode["Tag"] >> tagValue;
    EXPECT_EQ(tagValue, "Player");

    // Deserialize
    TagComponent deserialized = ComponentSerializer<TagComponent>::Deserialize(tagNode);
    EXPECT_EQ(deserialized.Tag, "Player");
}

TEST_F(ComponentSerializerTest, IDComponent_SerializeDeserialize) {
    UUID uuid(123456789);
    IDComponent originalID(uuid);

    // Serialize
    ComponentSerializer<IDComponent>::Serialize(root, originalID);

    ASSERT_TRUE(root.has_child("IDComponent"));
    UUID idValue;
    root["IDComponent"] >> idValue;
    EXPECT_EQ(idValue, uuid);

    // Deserialize
    IDComponent deserialized = ComponentSerializer<IDComponent>::Deserialize(root["IDComponent"]);
    EXPECT_EQ(deserialized.ID, uuid);
}

TEST_F(ComponentSerializerTest, TransformComponent_SerializeDeserialize) {
    glm::vec3 position(1.0f, 2.0f, 3.0f);
    TransformComponent originalTransform(position);

    // Serialize
    ComponentSerializer<TransformComponent>::Serialize(root, originalTransform);

    ASSERT_TRUE(root.has_child("TransformComponent"));
    auto transformNode = root["TransformComponent"];
    ASSERT_TRUE(transformNode.has_child("Position"));
    glm::vec3 posValue;
    transformNode["Position"] >> posValue;
    EXPECT_EQ(posValue, position);

    // Deserialize
    TransformComponent deserialized = ComponentSerializer<TransformComponent>::Deserialize(transformNode);
    EXPECT_EQ(deserialized.Position, position);
}
