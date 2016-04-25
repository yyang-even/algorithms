#pragma once

#include <random>
#include <string>

#include "3rdParty/nonius.h++"

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

#define BENCHMARK_SUIT(func_name) namespace {    \
    SIMPLE_BENCHMARK(func_name, LOWER_BOUND);    \
    SIMPLE_BENCHMARK(func_name, UPPER_BOUND);    \
    SIMPLE_BENCHMARK(func_name, SAMPLE);         \
    RAMDOM_BENCHMARK(func_name);                 \
}

constexpr unsigned LONG_BITS_NUM = (sizeof(unsigned long) << 2);
