#pragma once


template<typename ArrayType>
auto PairOfElementsSumAsNHashmap(const ArrayType &values, const typename ArrayType::value_type target,
        std::pair<typename ArrayType::value_type, typename ArrayType::value_type> *output) {
    std::unordered_set<typename ArrayType::value_type> value_set {};

    for (const auto element : values) {
        auto pair = target - element;
        if (value_set.find(pair) != value_set.cend()) {
            if(output)
            *output = std::make_pair(pair, element);
            return true;
        }
        value_set.insert(element);
    }

    return false;
}
