#include "common_header.h"

#include "is_divisible_by_n.h"


namespace {

/** Is divisible by 3
 *
 * @reference   Write an Efficient Method to Check if a Number is Multiple of 3
 *              https://www.geeksforgeeks.org/write-an-efficient-method-to-check-if-a-number-is-multiple-of-3/
 * @reference   Check if binary string multiple of 3 using DFA
 *              https://www.geeksforgeeks.org/check-binary-string-multiple-3-using-dfa/
 *
 * There is a pattern in binary representation of the number that can be used to find if
 * number is a multiple of 3. If difference between count of odd set bits (Bits set at
 * odd positions) and even set bits is multiple of 3 then is the number.
 */
constexpr auto isDivisibleBy3(int num) {
    if (num < 0) {
        num = -num;
    }
    if (num == 0) {
        return true;
    }
    if (num == 1) {
        return false;
    }

    int even_odd_diff = 0;
    while (num) {
        if (num & 1) {
            ++even_odd_diff;
        }
        num >>= 1;

        if (num & 1) {
            --even_odd_diff;
        }
        num >>= 1;
    }

    return isDivisibleBy3(even_odd_diff);
}


inline bool isDivisibleBy3_DFA(const std::vector<unsigned> &number) {
    return isDivisibleByN_DFA(number, 3).back();
}

}//namespace


constexpr int LOWER = 2;
constexpr auto UPPER = std::numeric_limits<int>::max();


SIMPLE_BENCHMARK(isDivisibleBy3, Sample1, LOWER);
SIMPLE_BENCHMARK(isDivisibleBy3, Sample2, UPPER);

SIMPLE_TEST(isDivisibleBy3, TestLOWER, false, LOWER);
SIMPLE_TEST(isDivisibleBy3, TestUPPER, false, UPPER);
SIMPLE_TEST(isDivisibleBy3, TestSAMPLE1, true, 612);
SIMPLE_TEST(isDivisibleBy3, TestSAMPLE2, true, 3);
SIMPLE_TEST(isDivisibleBy3, TestSAMPLE3, false, 610);
SIMPLE_TEST(isDivisibleBy3, TestSAMPLE4, true, -612);
SIMPLE_TEST(isDivisibleBy3, TestSAMPLE5, false, -610);


const std::vector<unsigned> SAMPLE1 = {1, 1, 0, 0};
const std::vector<unsigned> SAMPLE2 = {1, 0, 1, 0};


THE_BENCHMARK(isDivisibleBy3_DFA, SAMPLE1);

SIMPLE_TEST(isDivisibleBy3_DFA, TestSAMPLE1, true, SAMPLE1);
SIMPLE_TEST(isDivisibleBy3_DFA, TestSAMPLE2, false, SAMPLE2);
