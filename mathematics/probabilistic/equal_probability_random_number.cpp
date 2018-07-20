#include "common_header.h"

/** Generate integer from 1 to 7 with equal probability
 *
 * @reference   https://www.geeksforgeeks.org/?p=22539
 *
 * Given a function foo() that returns integers from 1 to 5 with equal probability,
 * write a function that returns integers from 1 to 7 with equal probability using
 * foo() only. Minimize the number of calls to foo() method. Also, use of any other
 * library function is not allowed and no floating point arithmetic allowed.
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

auto testRandomNumber1to7() {
    static const auto SAMPLE_SIZE = 7000000;
    static const auto AVERAGE_SAMPLE_SIZE = SAMPLE_SIZE / 7;
    static const double ERROR_RATE = 0.01;
    static const int TOLERATION = AVERAGE_SAMPLE_SIZE * ERROR_RATE;

    std::array<int, 8> counters {};
    for (int i = 0; i < SAMPLE_SIZE; ++i) {
        ++counters[RandomNumber1to7()];
    }

    for (auto iter = counters.cbegin() + 1; iter != counters.cend(); ++iter) {
        std::cout << *iter << std::endl;
        if (AVERAGE_SAMPLE_SIZE - TOLERATION > *iter or AVERAGE_SAMPLE_SIZE + TOLERATION < *iter) {
            return false;
        }
    }
    return true;
}


SIMPLE_BENCHMARK(RandomNumber1to7);

SIMPLE_TEST0(testRandomNumber1to7, TestSample, true);
