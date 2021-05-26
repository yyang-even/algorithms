#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** How to check if two given sets are disjoint?
 *
 * @reference   https://www.geeksforgeeks.org/check-two-given-sets-disjoint/
 */
auto AreTwoSetsDisjoint_Hash(const ArrayType &lhs, const ArrayType &rhs) {
    const std::unordered_set lhs_set(lhs.cbegin(), lhs.cend());
    for (const auto element : rhs) {
        if (lhs_set.find(element) != lhs_set.cend()) {
            return false;
        }
    }

    return true;
}


bool AreTwoSetsDisjoint_BinarySearch(const ArrayType &lhs, const ArrayType &rhs) {
    if (lhs.size() > rhs.size()) {
        return AreTwoSetsDisjoint_Hash(rhs, lhs);
    }

    auto sorted_lhs = lhs;
    std::sort(sorted_lhs.begin(), sorted_lhs.end());

    for (const auto element : rhs) {
        if (not std::binary_search(sorted_lhs.cbegin(), sorted_lhs.cend(), element)) {
            return false;
        }
    }

    return true;
}

}//namespace


const ArrayType SAMPLE1_X = {12, 34, 11, 9, 3};
const ArrayType SAMPLE1_Y = {2, 1, 3, 5};

const ArrayType SAMPLE2_Y = {7, 2, 1, 5};

const ArrayType SAMPLE3_X = {10, 5, 3, 4, 6};
const ArrayType SAMPLE3_Y = {8, 7, 9, 3};


THE_BENCHMARK(AreTwoSetsDisjoint_Hash, SAMPLE1_X, SAMPLE1_Y);

SIMPLE_TEST(AreTwoSetsDisjoint_Hash, TestSAMPLE1, false, SAMPLE1_X, SAMPLE1_Y);
SIMPLE_TEST(AreTwoSetsDisjoint_Hash, TestSAMPLE2, true, SAMPLE1_X, SAMPLE2_Y);
SIMPLE_TEST(AreTwoSetsDisjoint_Hash, TestSAMPLE3, false, SAMPLE3_X, SAMPLE3_Y);


THE_BENCHMARK(AreTwoSetsDisjoint_BinarySearch, SAMPLE1_X, SAMPLE1_Y);

SIMPLE_TEST(AreTwoSetsDisjoint_BinarySearch, TestSAMPLE1, false, SAMPLE1_X, SAMPLE1_Y);
SIMPLE_TEST(AreTwoSetsDisjoint_BinarySearch, TestSAMPLE2, true, SAMPLE1_X, SAMPLE2_Y);
SIMPLE_TEST(AreTwoSetsDisjoint_BinarySearch, TestSAMPLE3, false, SAMPLE3_X, SAMPLE3_Y);
