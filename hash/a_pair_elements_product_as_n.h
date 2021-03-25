#pragma once

template<typename ArrayType>
static inline auto PairElementsProductAsN(const ArrayType &elements,
                                          const typename ArrayType::value_type N,
                                          std::pair<typename ArrayType::value_type,
                                          typename ArrayType::value_type> *output) {
    std::unordered_set<typename ArrayType::value_type> value_set{};

    for (const auto elem : elements) {
        if (elem == 0 and N == 0) {
            if (output) {
                *output = std::pair(elem, elem);
            }
            return true;
        }

        if (N % elem == 0) {
            const auto pair = N / elem;
            if (value_set.find(pair) != value_set.cend()) {
                if (output) {
                    *output = std::pair(pair, elem);
                }
                return true;
            }
            value_set.insert(elem);
        }
    }

    return false;
}
