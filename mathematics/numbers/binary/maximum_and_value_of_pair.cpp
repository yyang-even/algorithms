#include "common_header.h"


namespace {

using ArrayType = std::vector<unsigned>;

#include "maximum_and_value_of_pair.h"

/** Maximum AND value of a pair in an array
 *
 * @reference   https://www.geeksforgeeks.org/maximum-value-pair-array/
 * @reference   Print pair with maximum AND value in an array
 *              https://www.geeksforgeeks.org/print-pair-with-maximum-and-value-in-an-array/
 *
 * We are given an array of n positive elements. We need to find the maximum AND value
 * generated by any pair of element from the array. AND is bitwise & operator.
 */

auto MaxAndValueOfPair_Pair(const ArrayType &elements) {
    const auto result = MaxAndValueOfPair_Value(elements);

    ArrayType pair(2, 0);
    if (result) {
        auto count = 0;
        for (auto iter = elements.cbegin(); iter != elements.cend() and count < 2; ++iter) {
            if ((*iter & result) == result) {
                pair[count++] = *iter;
            }
        }
    }

    return std::make_pair(pair.front(), pair.back());
}


/** Maximum Bitwise AND pair from given range
 *
 * @reference   https://www.geeksforgeeks.org/maximum-bitwise-and-pair-from-given-range/
 *
 * Given a range [L, R], the task is to find a pair (X, Y) such that L ≤ X < Y ≤ R and
 * X & Y is maximum among all the possible pairs then print the bitwise AND of the found pair.
 */
unsigned MaxAndValueOfRange(const unsigned L, const unsigned R) {
    if (L == R) {
        return 0;
    } else if ((R - L) == 1) {
        return R & L;
    } else {
        const auto result1 = (R - 1) & R;
        const auto result2 = (R - 2) & (R - 1);
        return result1 > result2 ? result1 : result2;
    }
}

}//namespace


const ArrayType VALUES1 = {};
const std::pair<ArrayType::value_type, ArrayType::value_type> EXPECTED0 = {0, 0};
const ArrayType VALUES2 = {1};
const ArrayType VALUES3 = {1, 2};
const ArrayType VALUES4 = {4, 8, 6, 2};
const std::pair<ArrayType::value_type, ArrayType::value_type> EXPECTED4 = {4, 6};
const ArrayType VALUES5 = {4, 8, 12, 16};
const std::pair<ArrayType::value_type, ArrayType::value_type> EXPECTED5 = {8, 12};
const ArrayType VALUES6 = {4, 8, 16, 2};


SIMPLE_BENCHMARK(MaxAndValueOfPair_Value, VALUES5);

SIMPLE_TEST(MaxAndValueOfPair_Value, TestSAMPLE1, 0, VALUES1);
SIMPLE_TEST(MaxAndValueOfPair_Value, TestSAMPLE2, 0, VALUES2);
SIMPLE_TEST(MaxAndValueOfPair_Value, TestSAMPLE3, 0, VALUES3);
SIMPLE_TEST(MaxAndValueOfPair_Value, TestSAMPLE4, 4, VALUES4);
SIMPLE_TEST(MaxAndValueOfPair_Value, TestSAMPLE5, 8, VALUES5);
SIMPLE_TEST(MaxAndValueOfPair_Value, TestSAMPLE6, 0, VALUES6);


SIMPLE_BENCHMARK(MaxAndValueOfPair_Pair, VALUES5);

SIMPLE_TEST(MaxAndValueOfPair_Pair, TestSAMPLE1, EXPECTED0, VALUES1);
SIMPLE_TEST(MaxAndValueOfPair_Pair, TestSAMPLE2, EXPECTED0, VALUES2);
SIMPLE_TEST(MaxAndValueOfPair_Pair, TestSAMPLE3, EXPECTED0, VALUES3);
SIMPLE_TEST(MaxAndValueOfPair_Pair, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(MaxAndValueOfPair_Pair, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(MaxAndValueOfPair_Pair, TestSAMPLE6, EXPECTED0, VALUES6);


SIMPLE_BENCHMARK(MaxAndValueOfRange, 523641, 985624);

SIMPLE_TEST(MaxAndValueOfRange, TestSAMPLE1, 8, 1, 9);
SIMPLE_TEST(MaxAndValueOfRange, TestSAMPLE2, 985622, 523641, 985624);
SIMPLE_TEST(MaxAndValueOfRange, TestSAMPLE3, 630, 1, 632);
SIMPLE_TEST(MaxAndValueOfRange, TestSAMPLE4, 0, 2, 2);
SIMPLE_TEST(MaxAndValueOfRange, TestSAMPLE5, 2, 2, 3);
