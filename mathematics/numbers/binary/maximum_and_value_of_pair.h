#pragma once


static inline auto MaxAndValueOfPair_Value(const ArrayType &elements) {
    ArrayType::value_type result = 0;

    for (int bit_position = BitsNumber<ArrayType::value_type> - 1; bit_position >= 0;
         --bit_position) {
        const auto pattern = result | (1 << bit_position);
        const auto count = std::count_if(elements.cbegin(), elements.cend(),
        [pattern](const auto & v) {
            return (pattern & v) == pattern;
        });

        if (count >= 2) {
            result = pattern;
        }
    }

    return result;
}
