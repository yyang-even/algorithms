#include "common_header.h"

#include "random_number_generator_in_arbitrary_probability.h"


namespace {

/** Make a fair coin from a biased coin
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 5.1. Exercise 5.1-3.
 *
 *              https://www.geeksforgeeks.org/print-0-and-1-with-50-probability/
 *
 * You are given a function foo() that represents a biased coin.
 * When foo() is called, it returns 0 with 60% probability, and
 * 1 with 40% probability. Write a new function that returns 0
 * and 1 with 50% probability each. Your function should use only
 * foo(), no other library method.
 */
inline bool foo() {
    return RandomNumberInArbitraryProbability_Ceil({0, 1}, {6, 4});
}
auto MakeFairCoinfromBiasedCoin() {
    const bool coin1 = foo();
    const bool coin2 = foo();
    if (coin1 ^ coin2) {
        return coin2;
    } else {
        return MakeFairCoinfromBiasedCoin();
    }
}

inline auto TestMakeFairCoinfromBiasedCoin() {
    static const int SAMPLE_SIZE = 2000000;
    static const int HALF_SAMPLE_SIZE = SAMPLE_SIZE / 2;
    static const double ERROR_RATE = 0.01;
    static const int TOLERATION = SAMPLE_SIZE * ERROR_RATE;

    int counter = 0;
    for (int i = 0; i < SAMPLE_SIZE; ++i) {
        counter += MakeFairCoinfromBiasedCoin();
    }

    return (HALF_SAMPLE_SIZE - TOLERATION) <= counter and (HALF_SAMPLE_SIZE + TOLERATION) >= counter;
}

}//namespace


SIMPLE_BENCHMARK(MakeFairCoinfromBiasedCoin);

SIMPLE_TEST0(TestMakeFairCoinfromBiasedCoin, TestSample, true);
