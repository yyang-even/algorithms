#pragma once


static inline double Median_QuickSelect(std::vector<int> &elements) {
    assert(not elements.empty());

    if (elements.size() % 2 == 0) {
        const auto mid_right = elements.begin() + elements.size() / 2;
        std::nth_element(elements.begin(), mid_right, elements.end());
        const auto mid_left = std::prev(mid_right);
        std::nth_element(elements.begin(), mid_left, mid_right);
        return (*mid_left + *mid_right) / 2.0;
    } else {
        const auto mid = elements.begin() + elements.size() / 2;
        std::nth_element(elements.begin(), mid, elements.end());
        return *mid;
    }
}

static inline auto Median_Unsorted_QuickSelect(std::vector<int> elements) {
    return Median_QuickSelect(elements);
}


static inline double Median_Sorted(const std::vector<int>::const_iterator cbegin,
                                   const std::vector<int>::size_type length) {
    const auto mid = std::next(cbegin, length / 2);
    if (length % 2 == 0) {
        return (*std::prev(mid) + *mid) / 2.0;
    }
    return *mid;
}
