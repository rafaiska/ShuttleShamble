#include <gtest/gtest.h>

#include "utils.hpp"

class UtilsTest : public testing::Test {
    protected:
        GMRect rectA;
        GMVector vectorA;

        UtilsTest(){}

        void SetUp() override {
            rectA.x = 10;
            rectA.y = 5;
            rectA.h = 8;
            rectA.w = 8;

            vectorA.x = 11;
            vectorA.y = 7;
        }
};

TEST_F(UtilsTest, test_vector_operators) {
    GMVector vectorB(1, 5);
    GMVector vectorC = vectorA + vectorB + GMVector(3, 3);

    ASSERT_EQ(vectorC.x, 15);
    ASSERT_EQ(vectorC.y, 15);

    vectorC = vectorC * 2;

    ASSERT_EQ(vectorC.x, 30);
    ASSERT_EQ(vectorC.y, 30);

    vectorC = 0.5 * vectorC;

    ASSERT_EQ(vectorC.x, 15);
    ASSERT_EQ(vectorC.y, 15);
}