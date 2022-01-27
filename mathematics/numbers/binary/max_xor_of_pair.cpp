#include "common_header.h"


namespace {

using ArrayType = std::vector<unsigned>;

/** Maximum XOR of Two Numbers in an Array
 *
 * @reference   https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/
 *
 * Given an integer array nums, return the maximum result of nums[i] XOR nums[j], where
 * 0 <= i <= j < n.
 */
auto MaxXorPair(const ArrayType &nums) {
    unsigned result = 0, mask = 0;
    for (int i = 31; i >= 0; --i) {
        mask |= 1 << i;
        std::unordered_set<unsigned> all_patterns;
        for (const auto n : nums) {
            all_patterns.insert(n & mask);
        }

        const auto trial = result | (1 << i);
        for (const auto one : all_patterns) {
            if (all_patterns.find(trial ^ one) != all_patterns.cend()) {
                result = trial;
                break;
            }
        }
    }

    return result;
}

}//namespace


const ArrayType SAMPLE1 = {3, 10, 5, 25, 2, 8};
const ArrayType SAMPLE2 = {14, 70, 53, 83, 49, 91, 36, 80, 92, 51, 66, 70};


THE_BENCHMARK(MaxXorPair, SAMPLE1);

SIMPLE_TEST(MaxXorPair, TestSAMPLE1, 28, SAMPLE1);
SIMPLE_TEST(MaxXorPair, TestSAMPLE2, 127, SAMPLE2);
