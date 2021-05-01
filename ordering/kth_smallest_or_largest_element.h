#pragma once


static inline auto
KthSmallest_QuickSelect(const ArrayType::iterator begin,
                        const ArrayType::iterator end,
                        const ArrayType::const_iterator target) {
    const auto pivot = std::prev(end);
    const auto partition_point = std::partition(begin, pivot, [pivot](const auto v) {
        return v <= *pivot;
    });
    std::iter_swap(pivot, partition_point);

    if (target == partition_point) {
        return partition_point;
    } else if (partition_point > target) {
        return KthSmallest_QuickSelect(begin, partition_point, target);
    } else {
        return KthSmallest_QuickSelect(std::next(partition_point), end, target);
    }
}
