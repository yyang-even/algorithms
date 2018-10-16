#include "common_header.h"

using ArrayType = std::vector<int>;
/** Given two unsorted arrays, find all pairs whose sum is x
 *
 * @reference   https://www.geeksforgeeks.org/given-two-unsorted-arrays-find-pairs-whose-sum-x/
 *
 * Given two unsorted arrays of distinct elements, the task is to find all
 * pairs from both arrays whose sum is equal to x.
 */
auto FindAllPairsSumAsN(const ArrayType &arr1, const ArrayType &arr2, const ArrayType::value_type SUM){
    std::unordered_set<int> array1_set(arr1.cbegin(), arr1.cend());
    std::vector<std::pair<ArrayType::value_type, ArrayType::value_type>> outputs;

    for(const auto elem: arr2){
        const auto pair = SUM - elem;
        if(array1_set.find(pair) != array1_set.cend())
            outputs.emplace_back(pair, elem);
    }

    return outputs;
}


const ArrayType SAMPLE1L = {-1, -2, 4, -6, 5, 7};
const ArrayType SAMPLE1R = {6, 3, 4, 0};
const std::vector<std::pair<ArrayType::value_type, ArrayType::value_type>> EXPECTED1 = {
    std::make_pair(5,3), std::make_pair(4,4)};
const ArrayType SAMPLE2L = {1, 2, 4, 5, 7};
const ArrayType SAMPLE2R = {5, 6, 3, 4, 8};
const std::vector<std::pair<ArrayType::value_type, ArrayType::value_type>> EXPECTED2 = {
    std::make_pair(4,5), std::make_pair(5,4), std::make_pair(1,8)};
const ArrayType SAMPLE3L = {1, 2, 3, 7, 5, 4};
const ArrayType SAMPLE3R = {0, 7, 4, 3, 2, 1};
const std::vector<std::pair<ArrayType::value_type, ArrayType::value_type>> EXPECTED3 = {
    std::make_pair(1,7), std::make_pair(4,4), std::make_pair(5,3), std::make_pair(7,1)};
const ArrayType SAMPLE4L = {1, 0, -4, 7, 6, 4};
const ArrayType SAMPLE4R = {0 ,2, 4, -3, 2, 1};
const std::vector<std::pair<ArrayType::value_type, ArrayType::value_type>> EXPECTED4 = {
    std::make_pair(6,2), std::make_pair(4,4), std::make_pair(6,2), std::make_pair(7,1)};

SIMPLE_BENCHMARK(FindAllPairsSumAsN, SAMPLE1L, SAMPLE1R, 8);

SIMPLE_TEST(FindAllPairsSumAsN, TestSample1, EXPECTED1, SAMPLE1L, SAMPLE1R, 8);
SIMPLE_TEST(FindAllPairsSumAsN, TestSample2, EXPECTED2, SAMPLE2L, SAMPLE2R, 9);
SIMPLE_TEST(FindAllPairsSumAsN, TestSample3, EXPECTED3, SAMPLE3L, SAMPLE3R, 8);
SIMPLE_TEST(FindAllPairsSumAsN, TestSample4, EXPECTED4, SAMPLE4L, SAMPLE4R, 8);
