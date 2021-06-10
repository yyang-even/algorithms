#pragma once

#include "counting_sort.h"


template <typename ArrayType>
static inline constexpr auto RadixSort(ArrayType values,
                                       const typename ArrayType::value_type base = 10) {
    if (values.empty()) {
        return values;
    }

    const auto max_value = *std::max_element(values.cbegin(), values.cend());
    for (typename ArrayType::value_type mask = 1; max_value / mask > 0; mask *= base) {
        values = CountingSort(std::move(values), base, [mask, base](const auto v) {
            return (v / mask) % base;
        });
    }

    return values;
}
