#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Finding 3-Digit Even Numbers
 *
 * @reference   https://leetcode.com/problems/finding-3-digit-even-numbers/
 *
 * You are given an integer array digits, where each element is a digit. The array may
 * contain duplicates.
 * You need to find all the unique integers that follow the given requirements:
 *  The integer consists of the concatenation of three elements from digits in any
 *      arbitrary order.
 *  The integer does not have leading zeros.
 *  The integer is even.
 * For example, if the given digits were [1, 2, 3], integers 132 and 312 follow the
 * requirements.
 * Return a sorted array of the unique integers.
 */
auto ThreeDigitEvenNumbers(const ArrayType &digits) {
    ArrayType result;

    int counts[10] = {};
    for (const auto d : digits) {
        ++counts[d];
    }

    for (int i = 1; i < 10; ++i) {
        for (int j = 0; counts[i] > 0 and j < 10; ++j) {
            for (int k = 0; counts[j] > (i == j) and k < 10; k += 2) {
                if (counts[k] > (k == i) + (k == j)) {
                    result.push_back(i * 100 + j * 10 + k);
                }
            }
        }
    }

    return result;
}

}//namespace


const ArrayType SAMPLE1 = {2, 1, 3, 0};
const ArrayType EXPECTED1 = {102, 120, 130, 132, 210, 230, 302, 310, 312, 320};

const ArrayType SAMPLE2 = {2, 2, 8, 8, 2};
const ArrayType EXPECTED2 = {222, 228, 282, 288, 822, 828, 882};

const ArrayType SAMPLE3 = {3, 7, 5};
const ArrayType EXPECTED3 = {};


THE_BENCHMARK(ThreeDigitEvenNumbers, SAMPLE1);

SIMPLE_TEST(ThreeDigitEvenNumbers, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(ThreeDigitEvenNumbers, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(ThreeDigitEvenNumbers, TestSAMPLE3, EXPECTED3, SAMPLE3);
