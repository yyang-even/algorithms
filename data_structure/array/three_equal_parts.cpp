#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;
using OutputType = std::pair<int, int>;

/** Three Equal Parts
 *
 * @reference   https://leetcode.com/problems/three-equal-parts/
 *
 * You are given an array arr which consists of only zeros and ones, divide the array
 * into three non-empty parts such that all of these parts represent the same binary
 * value. If it is possible, return any [i, j] with i + 1 < j, such that:
 *  arr[0], arr[1], ..., arr[i] is the first part,
 *  arr[i + 1], arr[i + 2], ..., arr[j - 1] is the second part, and
 *  arr[j], arr[j + 1], ..., arr[arr.length - 1] is the third part.
 *  All three parts have equal binary values.
 * If it is not possible, return [-1, -1].
 * Note that the entire part is used when considering what binary value it represents.
 * For example, [1,1,0] represents 6 in decimal, not 3. Also, leading zeros are allowed,
 * so [0,1,1] and [1,1] represent the same value.
 */
const OutputType INVALID = {-1, -1};

OutputType ThreeEqualParts(const ArrayType &elements) {
    ArrayType ones_index;
    for (std::size_t i = 0 ; i < elements.size(); ++i) {
        if (elements[i]) {
            ones_index.push_back(i);
        }
    }

    if (ones_index.size() % 3) {
        return INVALID;
    }

    if (ones_index.empty()) {
        return {0, 2};
    }

    const int part_3_first_1_index = ones_index[ones_index.size() / 3 * 2];
    const int part_size_without_leading_zeros = elements.size() - part_3_first_1_index;
    const int part_1_first_1_index = ones_index[0],
              part_2_first_1_index = ones_index[ones_index.size() / 3];

    for (int i = 0; i < part_size_without_leading_zeros; ++i)
        if (elements[part_1_first_1_index + i] != elements[part_2_first_1_index + i] or
            elements[part_1_first_1_index + i] != elements[part_3_first_1_index + i]) {
            return INVALID;
        }

    return {part_1_first_1_index + part_size_without_leading_zeros - 1,
            part_2_first_1_index + part_size_without_leading_zeros};
}

}//namespace


const ArrayType SAMPLE1 = {1, 0, 1, 0, 1};
const OutputType EXPECTED1 = {0, 3};

const ArrayType SAMPLE2 = {1, 1, 0, 1, 1};

const ArrayType SAMPLE3 = {1, 1, 0, 0, 1};
const OutputType EXPECTED3 = {0, 2};

const ArrayType SAMPLE4 = {0, 0, 0, 0, 0};

const ArrayType SAMPLE5 = {0, 1, 0, 1, 0, 0, 0, 1, 0};
const OutputType EXPECTED5 = {2, 5};


THE_BENCHMARK(ThreeEqualParts, SAMPLE1);

SIMPLE_TEST(ThreeEqualParts, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(ThreeEqualParts, TestSAMPLE2, INVALID, SAMPLE2);
SIMPLE_TEST(ThreeEqualParts, TestSAMPLE3, EXPECTED3, SAMPLE3);
SIMPLE_TEST(ThreeEqualParts, TestSAMPLE4, EXPECTED3, SAMPLE4);
