// Pseudocode plan:
// - Include GTest and the Event system header.
// - Define two lightweight test event types (TestEventA, TestEventB) using EVENT_CLASS_TYPE.
// - Test cases:
//   1) Matching dispatch sets Handled to true when handler returns true, returns true, and invokes handler exactly once.
//   2) Matching dispatch sets Handled to false when handler returns false, returns true, and invokes handler exactly once.
//   3) Mismatched dispatch returns false, does not invoke handler, and does not modify Handled.
//   4) Sequence: first mismatched (no change), then matched (changes), verifying return values and final Handled state.

#include <gtest/gtest.h>
#include "RealEngine/Events/Event.h"

using namespace RealEngine;

class TestEventA : public Event {
public:
    EVENT_CLASS_TYPE(TestEventA)
};

class TestEventB : public Event {
public:
    EVENT_CLASS_TYPE(TestEventB)
};

TEST(EventDispatcherTests, DispatchesMatchingTypeAndMarksHandledTrue) {
    TestEventA e;
    Event& base = e;
    EventDispatcher dispatcher(base);

    bool invoked = false;
    const bool dispatched = dispatcher.Dispatch<TestEventA>([&](TestEventA& ev) {
        invoked = true;
        EXPECT_EQ(&ev, &e);
        return true;
    });

    EXPECT_TRUE(dispatched);
    EXPECT_TRUE(invoked);
    EXPECT_TRUE(base.Handled);
}

TEST(EventDispatcherTests, DispatchesMatchingTypeAndMarksHandledFalse) {
    TestEventA e;
    e.Handled = true; // pre-set to true to confirm it can be set to false by handler
    Event& base = e;
    EventDispatcher dispatcher(base);

    int invoke_count = 0;
    const bool dispatched = dispatcher.Dispatch<TestEventA>([&](TestEventA&) {
        ++invoke_count;
        return false;
    });

    EXPECT_TRUE(dispatched);
    EXPECT_EQ(invoke_count, 1);
    EXPECT_FALSE(base.Handled);
}

TEST(EventDispatcherTests, DoesNotDispatchMismatchedType) {
    TestEventA e;
    Event& base = e;
    base.Handled = false;
    EventDispatcher dispatcher(base);

    int invoke_count = 0;
    const bool dispatched = dispatcher.Dispatch<TestEventB>([&](TestEventB&) {
        ++invoke_count;
        return true; // should never be called
    });

    EXPECT_FALSE(dispatched);
    EXPECT_EQ(invoke_count, 0);
    EXPECT_FALSE(base.Handled);
}

TEST(EventDispatcherTests, MismatchThenMatchSequence) {
    TestEventA e;
    Event& base = e;
    base.Handled = false;
    EventDispatcher dispatcher(base);

    int mismatch_count = 0;
    int match_count = 0;

    const bool first = dispatcher.Dispatch<TestEventB>([&](TestEventB&) {
        ++mismatch_count;
        return true;
    });
    const bool second = dispatcher.Dispatch<TestEventA>([&](TestEventA&) {
        ++match_count;
        return true;
    });

    EXPECT_FALSE(first);
    EXPECT_TRUE(second);
    EXPECT_EQ(mismatch_count, 0);
    EXPECT_EQ(match_count, 1);
    EXPECT_TRUE(base.Handled);
}
