#pragma once

#include <climits>
#include <random>
#include <string>

#include "3rdParty/nonius.h++"
#ifdef WANT_TESTS
#include "gtest/gtest.h"
#endif

#define SIMPLE_BENCHMARK(func_name, input) namespace {    \
    NONIUS_BENCHMARK((std::string(#func_name) + "(" + #input + ")"), []() {    \
        return func_name(input);   \
    })  \
}

std::random_device rd;
std::mt19937 generator(rd());
#define RAMDOM_BENCHMARK(func_name) namespace {  \
    NONIUS_BENCHMARK((std::string(#func_name) + "(Random)"), [](nonius::chronometer meter) {    \
        auto input = distribution(generator);   \
        meter.measure([&input]() { return func_name(input); }); \
    })  \
}

#define BENCHMARK_SUIT(func_name) namespace {   \
    SIMPLE_BENCHMARK(func_name, LOWER);         \
    SIMPLE_BENCHMARK(func_name, UPPER);         \
    SIMPLE_BENCHMARK(func_name, SAMPLE);        \
    RAMDOM_BENCHMARK(func_name);                \
}

constexpr unsigned LONG_BITS_NUM = (sizeof(unsigned long) * CHAR_BIT);

#ifdef WANT_TESTS
#define SIMPLE_TEST(func_name, input, expectedValue) namespace {    \
    TEST(func_name##Test, Test##input) {                            \
        EXPECT_EQ(expectedValue, func_name(input));                 \
    }                                                               \
}
#else
#define SIMPLE_TEST(func_name, input, expectedValue) namespace {}
#endif

#define SIMPLE_TEST_SUIT(func_name, lowerExpect, upperExpect, sampleExpect) namespace { \
    SIMPLE_TEST(func_name, LOWER, lowerExpect);                                         \
    SIMPLE_TEST(func_name, UPPER, upperExpect);                                         \
    SIMPLE_TEST(func_name, SAMPLE, sampleExpect);                                       \
}
