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
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#ifdef WANT_BENCHMARKS
#include "benchmark/benchmark.h"
#endif
#ifdef WANT_TESTS
#include "gtest/gtest.h"
#endif
#include "3rdParty/cxx-prettyprint/prettyprint.hpp"


// Util Functions
/** A function return a random number in range [from, to]
 */
template <typename FromType, typename ToType>
static inline auto Random_Number(const FromType from, const ToType to) {
    static const auto SEED = std::chrono::system_clock::now().time_since_epoch().count();
    static std::default_random_engine generator(SEED);
    std::uniform_int_distribution<std::common_type_t<FromType, ToType>>
            distribution(from, to);
    return distribution(generator);
}


template <typename Iterator>
static constexpr inline bool
isThereMoreThanOneElements(const Iterator cbegin, const Iterator cend) {
    return cbegin != cend and std::next(cbegin) != cend;
}


// Macros
/**
 * @reference   How to remove the enclosing parentheses with macro?
 *              https://stackoverflow.com/questions/24481810/how-to-remove-the-enclosing-parentheses-with-macro
 * @reference   Comma in C/C++ macro
 *              https://stackoverflow.com/questions/13842468/comma-in-c-c-macro
 */
#define STRIP_PARENTHESES(...) __VA_ARGS__


/**
 * @reference   #ifdef inside #define
 *              https://stackoverflow.com/questions/5586429/ifdef-inside-define
 */
#ifdef WANT_BENCHMARKS

#define SIMPLE_BENCHMARK(func_name, case_name, inputs...) namespace {   \
    static void BM_##func_name##_##case_name(benchmark::State& state) { \
        for (auto _ : state)                                            \
            func_name(inputs);                                          \
    }                                                                   \
                                                                        \
    BENCHMARK(BM_##func_name##_##case_name);                            \
}

#else

#define SIMPLE_BENCHMARK(func_name, inputs...) namespace {}

#endif

#define THE_BENCHMARK(func_name, inputs...) SIMPLE_BENCHMARK(func_name, Sample, inputs)
#define SIMPLE_BENCHMARK0(func_name) SIMPLE_BENCHMARK(func_name, Void)


#ifdef WANT_TESTS

#define EXPECT_EQ_AND_PRINT_INPUTS(expectedExpression, func_name, inputs...)                        \
    using ExpectedType = decltype(func_name(inputs));                                               \
    const ExpectedType &fine_type_expected_value = expectedExpression;                              \
    EXPECT_EQ(fine_type_expected_value, func_name(inputs)) << "Inputs: " << std::make_tuple(inputs);

#define SIMPLE_TEST(func_name, testName, expectedValue, inputs...) namespace {              \
    TEST(func_name##Test, testName) {                                                       \
        EXPECT_EQ_AND_PRINT_INPUTS(STRIP_PARENTHESES(expectedValue), func_name, inputs);    \
    }                                                                                       \
}

#define SIMPLE_DOUBLE_TEST(func_name, testName, expectedValue, inputs...) namespace {                           \
    TEST(func_name##Test, testName) {                                                                           \
        using ExpectedType = decltype(func_name(inputs));                                                       \
        ASSERT_TRUE(std::is_floating_point<ExpectedType>::value);                                               \
        const ExpectedType &fine_type_expected_value = expectedValue;                                           \
        EXPECT_DOUBLE_EQ(fine_type_expected_value, func_name(inputs)) << "Inputs: " << std::make_tuple(inputs); \
    }                                                                                                           \
}

#define SIMPLE_TEST0(func_name, testName, expectedValue...) namespace {         \
    TEST(func_name##Test, testName) {                                           \
        const decltype(func_name()) &fine_type_expected_value = expectedValue;  \
        EXPECT_EQ(fine_type_expected_value, func_name());                       \
    }                                                                           \
}

#define MUTUAL_SIMPLE_TEST(func1, func2, testName, inputs...) namespace {   \
    TEST(func1##vs##func2, testName) {                                      \
        EXPECT_EQ_AND_PRINT_INPUTS(func1(inputs), func2, inputs);           \
    }                                                                       \
}

#define MUTUAL_RANDOM_TEST(func1, func2, lowerBound, upperBound) namespace {    \
    TEST(MutualRandomTest, func1##vs##func2) {                                  \
        const auto random_input = Random_Number(lowerBound, upperBound);        \
        EXPECT_EQ_AND_PRINT_INPUTS(func1(random_input), func2, random_input);   \
    }                                                                           \
}

#else

#define SIMPLE_TEST(func_name, testName, expectedValue, inputs...) namespace {}
#define SIMPLE_DOUBLE_TEST(func_name, testName, expectedValue, inputs...) namespace {}
#define SIMPLE_TEST0(func_name, testName, expectedValue...) namespace {}
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


#define ContainerCast(from_container) {std::make_move_iterator(from_container.cbegin()), std::make_move_iterator(from_container.cend())}


//Constants
template <typename T>
static constexpr auto BitsNumber = sizeof(T) * CHAR_BIT;

constexpr auto Void = [](auto &&...) {};
constexpr auto Copy = [](auto v) {
    return v;
};

static constexpr auto LARGE_PRIME = 1000000007;

static constexpr unsigned HYPOTHETIC_MAX_STACK_DEPTH = 4096;

static const std::string DIGIT_CHARS {"0123456789"};
static const std::string LOWERCASE_CHARS {"abcdefghijklmnopqrstuvwxyz"};
static const std::string UPPERCASE_CHARS {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
