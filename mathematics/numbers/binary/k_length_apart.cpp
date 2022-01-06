#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Check If All 1's Are at Least Length K Places Away
 *
 * @reference   https://leetcode.com/problems/check-if-all-1s-are-at-least-length-k-places-away/
 *
 * Given an binary array nums and an integer k, return true if all 1's are at least k
 * places away from each other, otherwise return false.
 */
auto KLengthApart(const ArrayType &nums, const int K) {
    auto length = K;
    for (const auto n : nums) {
        if (n == 0) {
            ++length;
        } else {
            if (length < K) {
                return false;
            }
            length = 0;
        }
    }

    return true;
}


constexpr auto KLengthApart_Bit(unsigned x, const int K) {
    if (x == 0 or K == 0) {
        return true;
    }

    while ((x & 1) == 0) {
        x >>= 1;
    }

    while (x != 1) {
        x >>= 1;

        int count = 0;
        while ((x & 1) == 0) {
            x >>= 1;
            ++count;
        }

        if (count < K) {
            return false;
        }
    }

    return true;
}

}//namespace


const ArrayType SAMPLE1 = {1, 0, 0, 0, 1, 0, 0, 1};
const ArrayType SAMPLE2 = {1, 0, 0, 1, 0, 1};


THE_BENCHMARK(KLengthApart, SAMPLE1, 2);

SIMPLE_TEST(KLengthApart, TestSAMPLE1, true, SAMPLE1, 2);
SIMPLE_TEST(KLengthApart, TestSAMPLE2, false, SAMPLE2, 2);


THE_BENCHMARK(KLengthApart_Bit, 0b10001001, 2);

SIMPLE_TEST(KLengthApart_Bit, TestSAMPLE1, true, 0b10001001, 2);
SIMPLE_TEST(KLengthApart_Bit, TestSAMPLE2, false, 0b100101, 2);
