#pragma once


static inline auto
MinDiffPairOf2SortedArrays(const std::vector<int> &one,
                           const std::vector<int> &another) {
    assert(std::is_sorted(one.cbegin(), one.cend()));
    assert(std::is_sorted(another.cbegin(), another.cend()));

    auto result = std::numeric_limits<int>::max();
    auto one_iter = one.cbegin();
    auto another_iter = another.cbegin();
    while (one_iter != one.cend() and another_iter != another.cend()) {
        const auto diff = std::abs(*one_iter - *another_iter);
        if (diff < result) {
            result = diff;
        }

        if (*one_iter < *another_iter) {
            ++one_iter;
        } else {
            ++another_iter;
        }
    }

    return result;
}
