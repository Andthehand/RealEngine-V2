#include <gtest/gtest.h>

#include "RealEngine/Core/LayerStack.h"
#include "RealEngine/Core/Layer.h"

#include <string>
#include <vector>

using namespace RealEngine;

// Mock layer to track lifecycle callbacks and destruction.
class MockLayer : public Layer {
public:
    explicit MockLayer(const std::string& name) : Layer(name) {}

    ~MockLayer() override { ++s_destroyCount; }

    void OnAttach() override {
        ++s_totalAttach;
        ++attachCalls;
        attached = true;
    }

    void OnDetach() override {
        ++s_totalDetach;
        ++detachCalls;
        attached = false;
    }

    static void ResetStatics() {
        s_destroyCount = 0;
        s_totalAttach = 0;
        s_totalDetach = 0;
    }

    static int DestroyCount() { return s_destroyCount; }
    static int TotalAttach() { return s_totalAttach; }
    static int TotalDetach() { return s_totalDetach; }

    int attachCalls = 0;
    int detachCalls = 0;
    bool attached = false;

private:
    static inline int s_destroyCount = 0;
    static inline int s_totalAttach = 0;
    static inline int s_totalDetach = 0;
};

TEST(LayerStackTests, PushOrderAndCallbacks) {
    MockLayer::ResetStatics();

    LayerStack stack;
    auto* l1 = new MockLayer("L1");
    auto* l2 = new MockLayer("L2");
    auto* o1 = new MockLayer("O1");
    auto* o2 = new MockLayer("O2");

    stack.PushLayer(l1);
    stack.PushLayer(l2);
    stack.PushOverlay(o1);
    stack.PushOverlay(o2);

    EXPECT_EQ(l1->attachCalls, 1);
    EXPECT_EQ(l2->attachCalls, 1);
    EXPECT_EQ(o1->attachCalls, 1);
    EXPECT_EQ(o2->attachCalls, 1);
    EXPECT_EQ(MockLayer::TotalAttach(), 4);

    std::vector<std::string> names;
    for (auto* lyr : stack) names.emplace_back(lyr->GetName());
    ASSERT_EQ(names.size(), 4u);
    EXPECT_EQ(names[0], "L1");
    EXPECT_EQ(names[1], "L2");
    EXPECT_EQ(names[2], "O1");
    EXPECT_EQ(names[3], "O2");

    // Clear should detach all and delete all
    stack.Clear();
    EXPECT_EQ(MockLayer::TotalDetach(), 4);
    EXPECT_EQ(MockLayer::DestroyCount(), 4);
}

TEST(LayerStackTests, PopLayerAdjustsInsertIndexAndOrder) {
    MockLayer::ResetStatics();

    LayerStack stack;
    auto* l1 = new MockLayer("L1");
    auto* o1 = new MockLayer("O1");
    auto* l2 = new MockLayer("L2");

    stack.PushLayer(l1);
    stack.PushOverlay(o1);
    EXPECT_EQ(MockLayer::TotalAttach(), 2);

    // PopLayer must detach but does not delete (caller owns pointer)
    stack.PopLayer(l1);
    EXPECT_EQ(l1->detachCalls, 1);
    EXPECT_EQ(MockLayer::TotalDetach(), 1);
    delete l1; // caller responsibility after PopLayer
    EXPECT_EQ(MockLayer::DestroyCount(), 1);

    // Pushing a new layer should insert before overlays
    stack.PushLayer(l2);

    std::vector<std::string> names;
    for (auto* lyr : stack) names.emplace_back(lyr->GetName());
    ASSERT_EQ(names.size(), 2u);
    EXPECT_EQ(names[0], "L2");
    EXPECT_EQ(names[1], "O1");

    // PopOverlay must detach but does not delete
    stack.PopOverlay(o1);
    EXPECT_EQ(o1->detachCalls, 1);
    EXPECT_EQ(MockLayer::TotalDetach(), 2);
    delete o1; // caller responsibility after PopOverlay
    EXPECT_EQ(MockLayer::DestroyCount(), 2);

    // Clear remaining (l2 should be deleted by Clear)
    stack.Clear();
    EXPECT_EQ(MockLayer::DestroyCount(), 3);
}

TEST(LayerStackTests, DestructorClearsAndDeletes) {
    MockLayer::ResetStatics();
    {
        LayerStack stack;
        stack.PushLayer(new MockLayer("A"));
        stack.PushOverlay(new MockLayer("B"));
        EXPECT_EQ(MockLayer::TotalAttach(), 2);
        // Leaving scope should Clear() and delete both
    }
    EXPECT_EQ(MockLayer::TotalDetach(), 2);
    EXPECT_EQ(MockLayer::DestroyCount(), 2);
}
