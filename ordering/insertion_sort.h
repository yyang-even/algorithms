#pragma once

template <typename ArrayType>
auto InsertionSort(ArrayType values,
                   const std::function<bool(const typename ArrayType::value_type,
                                            const typename ArrayType::value_type)> compare) {
    for (typename ArrayType::size_type j = 1; j < values.size(); ++j) {
        auto key_value = std::move(values[j]);
        int i = j - 1;
        for (; (i >= 0) and compare(values[i], key_value); --i) {
            values[i + 1] = std::move(values[i]);
        }
        values[i + 1] = std::move(key_value);
    }
    return values;
}
