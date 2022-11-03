#include "gtest/gtest.h"
#include "../MyArray.h"

TEST(ArrayTest, sampleTest) {

    MyArray<int> a;
    for (int i = 0; i < 10; ++i) {
        a.insert(i + 1);
    }
    for (int i = 0; i < a.size(); ++i)
        a[i] *= 2;
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ((i + 1) * 2, a[i]);
    }
}



TEST(ArrayTest, stringSampleTest) {

    MyArray<std::string> a;
    for (int i = 0; i < 10; ++i) {
        a.insert( std::to_string(i + 1));
    }

    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(std::to_string(i + 1), a[i]);
    }
}




