#include <gtest/gtest.h>

TEST(HelloTest, BasicAssertions) {
    // Expect two strings to be equal.
    EXPECT_EQ("hello", "hello");
}