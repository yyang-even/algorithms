#pragma once


template <typename ArrayType>
static constexpr inline void
TransformToInplaceCounterArray(ArrayType &values, typename ArrayType::value_type base) {
    for (const auto elem : values) {
        values[elem % base] += base;
    }
}
