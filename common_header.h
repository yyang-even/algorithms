#pragma once

#include <climits>
#include <cmath>

#include <random>
#include <string>

#include "3rdParty/nonius.h++"
#ifdef WANT_TESTS
#include "gtest/gtest.h"
#endif

#define SIMPLE_BENCHMARK(func_name, inputs...) namespace {                      \
    NONIUS_BENCHMARK((std::string(#func_name) + "(" + #inputs + ")"), []() {    \
        return func_name(inputs);                                               \
    })                                                                          \
}

std::random_device rd;
std::mt19937 generator(rd());
#define RANDOM_BENCHMARK(func_name, lowerBound, upperBound) namespace {                         \
    NONIUS_BENCHMARK((std::string(#func_name) + "(Random)"), [](nonius::chronometer meter) {    \
        std::uniform_int_distribution<InputType> distribution(lowerBound, upperBound);          \
        auto input = distribution(generator);                                                   \
        meter.measure([&input]() { return func_name(input); });                                 \
    })                                                                                          \
}

constexpr unsigned LONG_BITS_NUM = (sizeof(unsigned long) * CHAR_BIT);
const unsigned HYPOTHETIC_MAX_STACK_DEPTH = 4096;

#ifdef WANT_TESTS
#define SIMPLE_TEST(func_name, testName, expectedValue, inputs...) namespace {  \
    TEST(func_name##Test, testName) {                                           \
        EXPECT_EQ(expectedValue, func_name(inputs)) << "Input: " << inputs;     \
    }                                                                           \
}
#else
#define SIMPLE_TEST(func_name, testName, expectedValue, inputs...) namespace {}
#endif

#ifdef WANT_TESTS
#define MUTUAL_RANDOM_TEST(func1, func2, lowerBound, upperBound) namespace {            \
    TEST(MutualRandomTest, func1##vs##func2) {                                          \
        std::uniform_int_distribution<InputType> distribution(lowerBound, upperBound);  \
        auto input = distribution(generator);                                           \
        EXPECT_EQ(func1(input), func2(input)) << "Input: " << input;                    \
    }                                                                                   \
}
#else
#define MUTUAL_RANDOM_TEST(func1, func2, lowerBound, upperBound) namespace {}
#endif
