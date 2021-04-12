#include "common_header.h"


namespace {

/** Generate integer from 1 to 7 with equal probability
 *
 * @reference   https://www.geeksforgeeks.org/generate-integer-from-1-to-7-with-equal-probability/
 *
 * Given a function foo() that returns integers from 1 to 5 with equal probability, write
 * a function that returns integers from 1 to 7 with equal probability using foo() only.
 * Minimize the number of calls to foo() method. Also, use of any other library function
 * is not allowed and no floating point arithmetic allowed.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 17.11.
 */
inline auto foo() {
    return Random_Number(1, 5);
}

auto RandomNumber1to7() {
    const auto i = foo() * 5 + foo() - 5;
    if (i < 22) {
        return i % 7 + 1;
    }
    return RandomNumber1to7();
}


/** Implement random-0-6-Generator using the given random-0-1-Generator
 *
 * @reference   https://www.geeksforgeeks.org/implement-random-0-6-generator-using-the-given-random-0-1-generator/
 *
 * Given a function random01Generator() that gives you randomly either 0 or 1, implement a
 * function that utilizes this function and generate numbers between 0 and 6(both inclusive).
 * All numbers should have same probabilities of occurrence.
 */
inline auto boo() {
    return Random_Number(0, 1);
}

auto RandomNumber0to6() {
    const auto i = boo() * 2 * 2 + boo() * 2 + boo();
    if (i < 7) {
        return i;
    }
    return RandomNumber0to6();
}


#ifdef WANT_TESTS
TEST(RandomNumber1to7Test, TestSanity) {
    static const auto SAMPLE_SIZE = 7000000;
    static const auto AVERAGE_SAMPLE_SIZE = SAMPLE_SIZE / 7;
    static const double ERROR_RATE = 0.01;
    static const int TOLERATION = AVERAGE_SAMPLE_SIZE * ERROR_RATE;

    std::array<int, 8> counters {};
    for (int i = 0; i < SAMPLE_SIZE; ++i) {
        ++counters[RandomNumber1to7()];
    }

    bool result = true;
    for (auto iter = counters.cbegin() + 1; iter != counters.cend(); ++iter) {
        if (AVERAGE_SAMPLE_SIZE - TOLERATION > *iter or
            AVERAGE_SAMPLE_SIZE + TOLERATION < *iter) {
            result = false;
        }
    }

    EXPECT_TRUE(result);
}


TEST(RandomNumber0to6Test, TestSanity) {
    static const auto SAMPLE_SIZE = 7000000;
    static const auto AVERAGE_SAMPLE_SIZE = SAMPLE_SIZE / 7;
    static const double ERROR_RATE = 0.01;
    static const int TOLERATION = AVERAGE_SAMPLE_SIZE * ERROR_RATE;

    std::array<int, 7> counters {};
    for (int i = 0; i < SAMPLE_SIZE; ++i) {
        ++counters[RandomNumber0to6()];
    }

    bool result = true;
    for (auto iter = counters.cbegin(); iter != counters.cend(); ++iter) {
        if (AVERAGE_SAMPLE_SIZE - TOLERATION > *iter or
            AVERAGE_SAMPLE_SIZE + TOLERATION < *iter) {
            result = false;
        }
    }

    EXPECT_TRUE(result);
}
#endif

}//namespace


SIMPLE_BENCHMARK0(RandomNumber1to7);


SIMPLE_BENCHMARK0(RandomNumber0to6);
