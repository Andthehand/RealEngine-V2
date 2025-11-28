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
    glm::quat rotation(0.25f, 0.5f, 0.75f, 1.0f);
    glm::vec3 scale(2.0f, 2.5f, 3.0f);

    TransformComponent originalTransform(position, rotation, scale);

    auto transformNode = root[TransformComponent::GetName()];
    transformNode << originalTransform;

    ASSERT_TRUE(root.has_child(TransformComponent::GetName()));
    ASSERT_TRUE(transformNode.has_child("Position"));
    ASSERT_TRUE(transformNode.has_child("Rotation"));
    ASSERT_TRUE(transformNode.has_child("Scale"));

    glm::vec3 posValue;
    glm::quat rotValue;
    glm::vec3 scaleValue;
    transformNode["Position"] >> posValue;
    transformNode["Rotation"] >> rotValue;
    transformNode["Scale"] >> scaleValue;

    EXPECT_EQ(posValue, position);
    EXPECT_EQ(rotValue, rotation);
    EXPECT_EQ(scaleValue, scale);

    TransformComponent deserialized{};
    transformNode >> deserialized;

    EXPECT_EQ(deserialized.GetTransation(), position);
    EXPECT_EQ(deserialized.GetRotationQuat(), rotation);
    EXPECT_EQ(deserialized.GetScale(), scale);
}
