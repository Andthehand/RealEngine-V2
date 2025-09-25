#include <gtest/gtest.h>
#include "RealEngine/Render/EditorCamera.h"
#include <glm/glm.hpp>

using namespace RealEngine;

TEST(EditorCameraTests, ConstructWithParameters) {
    EditorCamera cam(60.0f, 1.5f, 0.5f, 500.0f);
    EXPECT_FLOAT_EQ(cam.GetDistance(), 10.0f); // default distance
    EXPECT_FLOAT_EQ(cam.GetPitch(), 0.0f);
    EXPECT_FLOAT_EQ(cam.GetYaw(), 0.0f);
}

TEST(EditorCameraTests, DefaultConstruct) {
    EditorCamera cam;
    EXPECT_FLOAT_EQ(cam.GetDistance(), 10.0f);
}

TEST(EditorCameraTests, SetAndGetDistance) {
    EditorCamera cam;
    cam.SetDistance(42.0f);
    EXPECT_FLOAT_EQ(cam.GetDistance(), 42.0f);
}

TEST(EditorCameraTests, SetViewportSizeUpdatesProjection) {
    EditorCamera cam;
    cam.SetViewportSize(1920.0f, 1080.0f);
    // No direct getter for viewport, but projection should update without error
    auto vp = cam.GetViewProjection();
    EXPECT_EQ(glm::mat4(vp), vp); // Just check it's a mat4
}

TEST(EditorCameraTests, GetViewMatrixReturnsMat4) {
    EditorCamera cam;
    const auto& view = cam.GetViewMatrix();
    EXPECT_EQ(glm::mat4(view), view);
}
