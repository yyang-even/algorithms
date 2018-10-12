#pragma once


template <typename ArrayType>
void TransformToInplaceCounterArray(ArrayType &values, typename ArrayType::value_type base) {
    for (const auto elem : values) {
        values[elem % base] += base;
    }
}
