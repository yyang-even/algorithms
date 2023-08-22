#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Lexicographical Numbers
 *
 * @reference   https://leetcode.com/problems/lexicographical-numbers/
 *
 * Given an integer n, return all the numbers in the range [1, n] sorted in lexicographical order.
 * You must write an algorithm that runs in O(n) time and uses O(1) extra space.
 */
auto LexicographicalNumbers_Iterative(const int n) {
    std::vector<int> result;

    int curr = 1;
    for (int i = 1; i <= n; ++i) {
        result.push_back(curr);
        if (curr * 10 <= n) {
            curr *= 10;
        } else if (curr % 10 != 9 and curr + 1 <= n) {
            ++curr;
        } else {
            while ((curr / 10) % 10 == 9) {
                curr /= 10;
            }
            curr = curr / 10 + 1;
        }
    }

    return result;
}


void LexicographicalNumbers(const int n, const int prev, ArrayType &result) {
    result.push_back(prev);
    for (auto i = 0; i < 10; ++i) {
        const auto curr = prev * 10 + i;
        if (curr <= n) {
            LexicographicalNumbers(n, curr, result);
        }
    }
}

auto LexicographicalNumbers(const int n) {
    std::vector<int> result;
    for (int i = 1; i < 10; ++i) {
        if (i <= n) {
            LexicographicalNumbers(n, i, result);
        }
    }

    return result;
}

} //namespace


const std::vector EXPECTED1 = {1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9};
const std::vector EXPECTED2 = {1, 2};


THE_BENCHMARK(LexicographicalNumbers_Iterative, 13);

SIMPLE_TEST(LexicographicalNumbers_Iterative, TestSAMPLE1, EXPECTED1, 13);
SIMPLE_TEST(LexicographicalNumbers_Iterative, TestSAMPLE2, EXPECTED2, 2);


THE_BENCHMARK(LexicographicalNumbers, 13);

SIMPLE_TEST(LexicographicalNumbers, TestSAMPLE1, EXPECTED1, 13);
SIMPLE_TEST(LexicographicalNumbers, TestSAMPLE2, EXPECTED2, 2);
