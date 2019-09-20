#include "common_header.h"


#define RandomNumberTest(testName, from, to) namespace {                        \
    TEST(Random_NumberTest, testName) {                                         \
        const auto random_number = Random_Number(from, to);                     \
                                                                                \
        EXPECT_LE(static_cast<decltype(random_number)>(from), random_number);   \
        EXPECT_GE(static_cast<decltype(random_number)>(to), random_number);     \
    }                                                                           \
}

RandomNumberTest(TestSameType, 0, 20);
RandomNumberTest(TestDiffType, 0, 20u);
