#pragma once

#include "common_header.h"

#include "mathematics/arithmetics/sum/prefix_sum_array.h"


static inline auto
findCeil(const std::vector<int> &prefixs, const int value) {
    const auto ceil = std::upper_bound(prefixs.cbegin(), prefixs.cend(), value);
    return ceil == prefixs.cend() ? -1 : ceil - prefixs.cbegin();
}

static inline auto
RandomNumberInArbitraryProbability_Ceil(const std::vector<int> &numbers,
                                        std::vector<int> frequencies) {
    assert(numbers.size() == frequencies.size());

    const auto prefixs = PrefixSumArray(std::move(frequencies));

    const auto random_number = Random_Number(1, prefixs.back());

    return numbers[findCeil(prefixs, random_number)];
}
