#include <gtest/gtest.h>

int main (int argc, char* argv[]) {
    testing::InitGoogleTest();
    int code = RUN_ALL_TESTS();
    std::cout << code << '\n';
    return 0;
}