#include "common_header.h"

#include "hash.h"


namespace {

using ArrayType = std::vector<int>;

/** Fair Candy Swap
 *
 * @reference   https://leetcode.com/problems/fair-candy-swap/
 *
 * Alice and Bob have a different total number of candies. You are given two integer
 * arrays aliceSizes and bobSizes where aliceSizes[i] is the number of candies of the
 * ith box of candy that Alice has and bobSizes[j] is the number of candies of the jth
 * box of candy that Bob has. Since they are friends, they would like to exchange one
 * candy box each so that after the exchange, they both have the same total amount of
 * candy. The total amount of candy a person has is the sum of the number of candies in
 * each box they have. Return an integer array answer where answer[0] is the number of
 * candies in the box that Alice must exchange, and answer[1] is the number of candies
 * in the box that Bob must exchange. If there are multiple answers, you may return any
 * one of them. It is guaranteed that at least one answer exists.
 */
auto FairCandySwap(const ArrayType &alice_sizes, const ArrayType &bob_sizes) {
    const auto alice_total = std::accumulate(alice_sizes.cbegin(), alice_sizes.cend(), 0);
    const auto bob_total = std::accumulate(bob_sizes.cbegin(), bob_sizes.cend(), 0);
    const int delta = (bob_total - alice_total) / 2;

    const auto bob_set = ToUnorderedSet(bob_sizes);

    for (const auto s : alice_sizes) {
        const auto the_other = s + delta;
        if (bob_set.find(the_other) != bob_set.cend()) {
            return std::pair(s, the_other);
        }
    }

    return std::pair(0, 0);
}

}//namespace


const ArrayType SAMPLE1A = {1, 1};
const ArrayType SAMPLE1B = {2, 2};
const std::pair EXPECTED1 = {1, 2};

const ArrayType SAMPLE2A = {1, 2};
const ArrayType SAMPLE2B = {2, 3};
const std::pair EXPECTED2 = {1, 2};

const ArrayType SAMPLE3A = {2};
const ArrayType SAMPLE3B = {1, 3};
const std::pair EXPECTED3 = {2, 3};

const ArrayType SAMPLE4A = {1, 2, 5};
const ArrayType SAMPLE4B = {2, 4};
const std::pair EXPECTED4 = {5, 4};


THE_BENCHMARK(FairCandySwap, SAMPLE1A, SAMPLE1B);

SIMPLE_TEST(FairCandySwap, TestSAMPLE1, EXPECTED1, SAMPLE1A, SAMPLE1B);
SIMPLE_TEST(FairCandySwap, TestSAMPLE2, EXPECTED2, SAMPLE2A, SAMPLE2B);
SIMPLE_TEST(FairCandySwap, TestSAMPLE3, EXPECTED3, SAMPLE3A, SAMPLE3B);
SIMPLE_TEST(FairCandySwap, TestSAMPLE4, EXPECTED4, SAMPLE4A, SAMPLE4B);
