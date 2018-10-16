#pragma once

template <typename ArrayType>
const auto AllSubarraysWithGivenSum(const ArrayType &integers,
                                    const typename ArrayType::value_type SUM) {
    std::unordered_multimap<typename ArrayType::value_type,
        typename ArrayType::size_type> sum_index_map;
    typename ArrayType::value_type current_sum = 0;
    std::vector<std::pair<int, int>> outputs;

    for (typename ArrayType::size_type i = 0ul; i < integers.size(); ++i) {
        current_sum += integers[i];

        if (current_sum == SUM) {
            outputs.emplace_back(0, i);
        }

        const auto expected_subarray_sum = current_sum - SUM;
        const auto range = sum_index_map.equal_range(expected_subarray_sum);
        if (range.first != sum_index_map.cend()) {
            for (auto iter = range.first; iter != range.second; ++iter) {
                outputs.emplace_back(iter->second + 1, i);
            }
        }

        sum_index_map.emplace(current_sum, i);
    }

    return outputs;
}
