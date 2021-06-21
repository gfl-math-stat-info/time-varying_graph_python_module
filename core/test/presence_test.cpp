#include "../include/presence.h"
#include "gtest/gtest.h"


class PresenceTest : public ::testing::Test {
    protected:

    PresenceTest() {
        // TODO: Create a presence_function struct
    }

    ~PresenceTest() {
        // TODO: Delete the presence_function struct
    }

    void SetUp() override {
        // Not needed for now.
    }

    void TearDown() override {
        // Not needed for now.
    }
};


TEST_F(PresenceTest, StrToPeriodicPattern) {
    // TODO
}

TEST_F(PresenceTest, IsPresent) {
    // TODO
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}