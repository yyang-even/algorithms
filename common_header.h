#pragma once

#include <cassert>
#include <climits>
#include <cmath>

#include <limits>
#include <random>
#include <string>

#include "3rdParty/nonius.h++"
#ifdef WANT_TESTS
#include "gtest/gtest.h"
#endif

// Typedefs
typedef int INT_BOOL;
#define TRUE 1
#define FALSE 0

// Util Functions
/** A function return a random number in range [from, to]
 */
template <typename T>
inline auto Random_Number(const T from, const T to) {
    static const auto SEED = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine generator(SEED);
    std::uniform_int_distribution<T> distribution(from, to);
    return distribution(generator);
}

// Macros
#ifdef NONIUS_RUNNER
#define SIMPLE_BENCHMARK(func_name, inputs...) namespace {                      \
    NONIUS_BENCHMARK((std::string(#func_name) + "(" + #inputs + ")"), []() {    \
        return func_name(inputs);                                               \
    })                                                                          \
}

#define RANDOM_BENCHMARK(func_name, lowerBound, upperBound) namespace {                         \
    NONIUS_BENCHMARK((std::string(#func_name) + "(Random)"), [](nonius::chronometer meter) {    \
        auto input = Random_Number<InputType>(lowerBound, upperBound);                          \
        meter.measure([&input]() { return func_name(input); });                                 \
    })                                                                                          \
}
#else
#define SIMPLE_BENCHMARK(func_name, inputs...) namespace {}
#define RANDOM_BENCHMARK(func_name, lowerBound, upperBound) namespace {}
#endif


#ifdef WANT_TESTS
#define SIMPLE_TEST(func_name, testName, expectedValue, inputs...) namespace {  \
    TEST(func_name##Test, testName) {                                           \
        EXPECT_EQ(expectedValue, func_name(inputs)) << "Input: " << inputs;     \
    }                                                                           \
}
#define SIMPLE_TEST0(func_name, testName, expectedValue) namespace {    \
    TEST(func_name##Test, testName) {                                   \
        EXPECT_EQ(expectedValue, func_name());                          \
    }                                                                   \
}

#define MUTUAL_RANDOM_TEST(func1, func2, lowerBound, upperBound) namespace {            \
    TEST(MutualRandomTest, func1##vs##func2) {                                          \
        auto input = Random_Number<InputType>(lowerBound, upperBound);                  \
        EXPECT_EQ(func1(input), func2(input)) << "Input: " << input;                    \
    }                                                                                   \
}
#else
#define SIMPLE_TEST(func_name, testName, expectedValue, inputs...) namespace {}
#define SIMPLE_TEST0(func_name, testName, expectedValue) namespace {}
#define MUTUAL_RANDOM_TEST(func1, func2, lowerBound, upperBound) namespace {}
#endif

//Constants
constexpr unsigned LONG_BITS_NUM = (sizeof(unsigned long) * CHAR_BIT);
const unsigned HYPOTHETIC_MAX_STACK_DEPTH = 4096;
