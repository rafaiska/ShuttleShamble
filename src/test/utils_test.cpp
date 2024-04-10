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

TEST_F(UtilsTest, test_vector_operators)
{
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

TEST_F(UtilsTest, test_rect_operators)
{
    GMRect rectB = rectA;

    ASSERT_EQ(rectB.x, 10);
    ASSERT_EQ(rectB.y, 5);
    ASSERT_EQ(rectB.h, 8);
    ASSERT_EQ(rectB.w, 8);
}

TEST_F(UtilsTest, test_get_position_from_rect)
{
    get_position_from_rect(rectA, vectorA);

    ASSERT_EQ(vectorA.x, 10);
    ASSERT_EQ(vectorA.y, 5);
}

TEST_F(UtilsTest, test_set_rect_position)
{
    set_rect_position(rectA, vectorA);

    ASSERT_EQ(rectA.x, 11);
    ASSERT_EQ(rectA.y, 7);
}

TEST_F(UtilsTest, test_distance_between)
{
    GMVector vectorB(15, 7);
    
    ASSERT_EQ(distance_between(vectorA, vectorB), 4.0);
}

TEST_F(UtilsTest, test_center_of_mass)
{
    GMVector com = center_of_mass(rectA);

    ASSERT_EQ(com.x, 14);
    ASSERT_EQ(com.y, 9);
}

TEST_F(UtilsTest, test_rect_intersection)
{
    GMRect rectB(10, 5, 8, 8);
    ASSERT_EQ(rect_intersection(rectA, rectB), GMRect(10, 5, 8, 8));

    rectB = GMRect(20, 5, 8, 8);
    ASSERT_EQ(rect_intersection(rectA, rectB), GMRect(0, 0, 0, 0));
}