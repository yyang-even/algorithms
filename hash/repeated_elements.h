#pragma once


template <typename ArrayType>
auto TransformToInplaceCounterArray(ArrayType values, typename ArrayType::value_type base) {
    for (const auto elem : values) {
        values[elem % base] += base;
    }

    return values;
}
