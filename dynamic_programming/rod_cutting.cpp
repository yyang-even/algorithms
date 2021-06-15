#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Rod cutting
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 15.1.
 * @reference   Cutting a Rod | DP-13
 *              https://www.geeksforgeeks.org/cutting-a-rod-dp-13/
 * @reference   C Program for Cutting a Rod | DP-13
 *              https://www.geeksforgeeks.org/c-program-for-cutting-a-rod-dp-13/
 *
 * Given a rod of length n inches and an array of prices that contains prices of all
 * pieces of size smaller than n. Determine the maximum value obtainable by cutting
 * up the rod and selling the pieces.
 */
auto RodCutting(const ArrayType &prices, const ArrayType::size_type rod_length) {
    ArrayType max_values = {0};
    for (ArrayType::size_type i = 1; i <= rod_length; ++i) {
        auto ith_max_value = std::numeric_limits<ArrayType::value_type>::min();
        for (ArrayType::size_type j = 0; j < i; ++j) {
            ith_max_value = std::max(ith_max_value, prices[j] + max_values[i - j - 1]);
        }
        max_values.push_back(ith_max_value);
    }

    return max_values.back();
}

}//namespace


const ArrayType SAMPLE1 = {1, 5, 8, 9, 10, 17, 17, 20};


THE_BENCHMARK(RodCutting, SAMPLE1, SAMPLE1.size());

SIMPLE_TEST(RodCutting, TestSAMPLE1, 22, SAMPLE1, SAMPLE1.size());
