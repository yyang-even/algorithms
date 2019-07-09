#pragma once

#include <cassert>
#include <climits>
#include <cmath>

#include <chrono>
#include <forward_list>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#ifdef NONIUS_RUNNER
#include "nonius/nonius_single.h++"
#endif
#ifdef WANT_TESTS
#include "gtest/gtest.h"
#endif
#include "3rdParty/cxx-prettyprint/prettyprint.hpp"


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

template <typename T>
inline constexpr auto Bits_Number() {
    return sizeof(T) * CHAR_BIT;
}

template <typename Iterator>
inline bool isThereMoreThanOneElements(const Iterator cbegin, const Iterator cend) {
    return cbegin != cend and std::next(cbegin) != cend;
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
        const auto input = Random_Number<InputType>(lowerBound, upperBound);                    \
        meter.measure([&input]() { return func_name(input); });                                 \
    })                                                                                          \
}
#else
#define SIMPLE_BENCHMARK(func_name, inputs...) namespace {}
#define RANDOM_BENCHMARK(func_name, lowerBound, upperBound) namespace {}
#endif


#ifdef WANT_TESTS
#define SIMPLE_TEST(func_name, testName, expectedValue, inputs...) namespace {                  \
    TEST(func_name##Test, testName) {                                                           \
        EXPECT_EQ(expectedValue, func_name(inputs)) << "Inputs: " << std::make_tuple(inputs);   \
    }                                                                                           \
}
#define SIMPLE_TEST0(func_name, testName, expectedValue) namespace {    \
    TEST(func_name##Test, testName) {                                   \
        EXPECT_EQ(expectedValue, func_name());                          \
    }                                                                   \
}

#define MUTUAL_RANDOM_TEST(func1, func2, lowerBound, upperBound) namespace {                                \
    TEST(MutualRandomTest, func1##vs##func2) {                                                              \
        const auto input = Random_Number<InputType>(lowerBound, upperBound);                                \
        EXPECT_EQ(func1(input), static_cast<decltype(func1(input))>(func2(input))) << "Input: " << input;   \
    }                                                                                                       \
}
#else
#define SIMPLE_TEST(func_name, testName, expectedValue, inputs...) namespace {}
#define SIMPLE_TEST0(func_name, testName, expectedValue) namespace {}
#define MUTUAL_RANDOM_TEST(func1, func2, lowerBound, upperBound) namespace {}
#endif

//Constants
constexpr unsigned LONG_BITS_NUM = Bits_Number<unsigned long>();
const unsigned HYPOTHETIC_MAX_STACK_DEPTH = 4096;

static const std::string DIGIT_CHARS {"0123456789"};
static const std::string LOWERCASE_CHARS {"abcdefghijklmnopqrstuvwxyz"};
static const std::string UPPERCASE_CHARS {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
