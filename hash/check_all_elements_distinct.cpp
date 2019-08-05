#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Check if all array elements are distinct
 *
 * @reference   https://www.geeksforgeeks.org/check-if-all-array-elements-are-distinct/
 *
 * Given an array, check whether all elements in an array are distinct or not.
 */
auto CheckIfAllElementsDistinct(const ArrayType &elements) {
    std::unordered_map<ArrayType::value_type, ArrayType::size_type> counters;

    for (const auto elem : elements) {
        if (++counters[elem] > 1) {
            return false;
        }
    }

    return true;
}

}//namespace


const ArrayType SAMPLE1 = {12, 10, 9, 45, 2, 10, 10, 45};
const ArrayType SAMPLE2 = {2, 1, 9, 5};


SIMPLE_BENCHMARK(CheckIfAllElementsDistinct, SAMPLE1);

SIMPLE_TEST(CheckIfAllElementsDistinct, TestSAMPLE1, false, SAMPLE1);
SIMPLE_TEST(CheckIfAllElementsDistinct, TestSAMPLE2, true, SAMPLE2);
