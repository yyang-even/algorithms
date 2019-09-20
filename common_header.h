#pragma once

#include <cassert>
#include <climits>
#include <cmath>
#include <cstring>

#include <algorithm>
#include <bitset>
#include <chrono>
#include <forward_list>
#include <functional>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#ifdef NONIUS_RUNNER
#include "nonius/nonius_single.h++"
#endif
#ifdef WANT_TESTS
#include "gtest/gtest.h"
#endif
#include "3rdParty/cxx-prettyprint/prettyprint.hpp"


// Util Functions
/** A function return a random number in range [from, to]
 */
template <typename FromType, typename ToType>
inline auto Random_Number(const FromType from, const ToType to) {
    static const auto SEED = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine generator(SEED);
    std::uniform_int_distribution<std::common_type_t<FromType, ToType>> distribution(from, to);
    return distribution(generator);
}


template <typename Iterator>
inline bool isThereMoreThanOneElements(const Iterator cbegin, const Iterator cend) {
    return cbegin != cend and std::next(cbegin) != cend;
}


#define ContainerCast(from_container) {std::make_move_iterator(from_container.cbegin()), std::make_move_iterator(from_container.cend())}

template<typename Container, typename Function, typename... Args>
std::remove_reference_t<Container>
ContainerTestHelper(const Function func, Container &&elements, Args &&... args) {
    auto other_container = func(ContainerCast(elements), std::forward<Args> (args)...);
    return ContainerCast(other_container);
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

#define MUTUAL_SIMPLE_TEST(func1, func2, testName, inputs...) namespace {                                                       \
    TEST(func1##vs##func2, testName) {                                                                                          \
        EXPECT_EQ(func1(inputs), static_cast<decltype(func1(inputs))>(func2(inputs))) << "Inputs: " << std::make_tuple(inputs); \
    }                                                                                                                           \
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
#define MUTUAL_SIMPLE_TEST(func1, func2, testName, inputs...) namespace {}
#define MUTUAL_RANDOM_TEST(func1, func2, lowerBound, upperBound) namespace {}

#endif


/**
 * @reference   Functions in std
 *              https://en.cppreference.com/w/cpp/algorithm/stable_partition
 */
#define ToLambda(F) [](auto&&... args)                              \
    noexcept(noexcept(F(std::forward<decltype(args)>(args)...)))    \
    -> decltype(F(std::forward<decltype(args)>(args)...)) {         \
        return F(std::forward<decltype(args)>(args)...);            \
    }

#define ToNegationLambda(F) [](auto&&... args)                      \
    noexcept(noexcept(F(std::forward<decltype(args)>(args)...)))    \
    -> decltype(F(std::forward<decltype(args)>(args)...)) {         \
        return not F(std::forward<decltype(args)>(args)...);        \
    }


//Constants
template <typename T>
constexpr auto BitsNumber = sizeof(T) * CHAR_BIT;

constexpr auto LONG_BITS_NUM = BitsNumber<long>;
constexpr auto INT_BITS_NUM = BitsNumber<int>;

const unsigned HYPOTHETIC_MAX_STACK_DEPTH = 4096;

static const std::string DIGIT_CHARS {"0123456789"};
static const std::string LOWERCASE_CHARS {"abcdefghijklmnopqrstuvwxyz"};
static const std::string UPPERCASE_CHARS {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};