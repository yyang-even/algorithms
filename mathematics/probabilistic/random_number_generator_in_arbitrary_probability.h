#pragma once

#include "common_header.h"


auto findCeil(const std::vector<int> &prefixs, const int value) {
    const auto ceil = std::upper_bound(prefixs.cbegin(), prefixs.cend(), value);
    return ceil == prefixs.cend() ? -1 : ceil - prefixs.cbegin();
}

auto RandomNumberInArbitraryProbability_Ceil(const std::vector<int> &numbers,
        const std::vector<int> &frequencies) {
    assert(numbers.size() == frequencies.size());

    std::vector<int> prefixs = {frequencies.front()};
    for (auto iter = frequencies.cbegin() + 1; iter < frequencies.cend(); ++iter) {
        prefixs.push_back(prefixs.back() + *iter);
    }

    const auto random_number = Random_Number(1, prefixs.back());
    return numbers[findCeil(prefixs, random_number)];
}
