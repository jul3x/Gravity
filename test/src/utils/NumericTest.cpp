//
// Created by jprolejko on 17.07.19.
//

#include <gtest/gtest.h>

#include <utils/Numeric.h>

TEST(NumericTest, IsNearlyEqual) {
    EXPECT_TRUE(utils::isNearlyEqual({0.0f, 0.0f}, {0.0f, 0.0f}, 0.01f));
}