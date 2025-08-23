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

    // Serialize using << operator
    auto tagNode = root[TagComponent::GetName()];
    tagNode << originalTag;

    ASSERT_TRUE(root.has_child(TagComponent::GetName()));
    ASSERT_TRUE(tagNode.has_child("Tag"));
    std::string tagValue;
    tagNode["Tag"] >> tagValue;
    EXPECT_EQ(tagValue, "Player");

    // Deserialize using >> operator
    TagComponent deserialized{};
    tagNode >> deserialized;
    EXPECT_EQ(deserialized.Tag, "Player");
}

TEST_F(ComponentSerializerTest, IDComponent_SerializeDeserialize) {
    UUID uuid(123456789);
    IDComponent originalID(uuid);

    // Serialize using << operator
    auto idNode = root[IDComponent::GetName()];
    idNode << originalID;

    ASSERT_TRUE(root.has_child(IDComponent::GetName()));
    ASSERT_TRUE(idNode.has_child("ID"));
    UUID idValue;
    idNode >> idValue; // uses UUID >> overload via ADL
    EXPECT_EQ(idValue, uuid);

    // Deserialize using >> operator
    IDComponent deserialized{};
    idNode >> deserialized;
    EXPECT_EQ(deserialized.ID, uuid);
}

TEST_F(ComponentSerializerTest, TransformComponent_SerializeDeserialize) {
    glm::vec3 position(1.0f, 2.0f, 3.0f);
    TransformComponent originalTransform(position);

    // Serialize using << operator
    auto transformNode = root[TransformComponent::GetName()];
    transformNode << originalTransform;

    ASSERT_TRUE(root.has_child(TransformComponent::GetName()));
    ASSERT_TRUE(transformNode.has_child("Position"));
    glm::vec3 posValue;
    transformNode["Position"] >> posValue;
    EXPECT_EQ(posValue, position);

    // Deserialize using >> operator
    TransformComponent deserialized{};
    transformNode >> deserialized;
    EXPECT_EQ(deserialized.Position, position);
}
