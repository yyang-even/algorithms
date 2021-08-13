#pragma once


static inline auto
RangeSum(const std::vector<int> &prefix_sums, const int left, const int right) {
    if (left == 0) {
        return prefix_sums[right];
    } else {
        return prefix_sums[right] - prefix_sums[left - 1];
    }
}
