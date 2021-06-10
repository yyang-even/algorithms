#include "common_header.h"


namespace {

using ArrayType = std::vector<unsigned>;

/** Print numbers having first and last bits as the only set bits
 *
 * @reference   https://www.geeksforgeeks.org/print-numbers-first-last-bits-set-bits/
 *
 * Given a positive integer n. The problem is to print numbers in the range 1 to n having
 * first and last bits as the only set bits.
 */
auto NumbersHavingFirstAndLastBitsSet(const ArrayType::value_type N) {
    ArrayType output = {1};

    ArrayType::value_type power_of_2 = 1;
    while (true) {
        power_of_2 <<= 1;
        const auto number = power_of_2 ^ 1;
        if (number > N) {
            break;
        }
        output.push_back(number);
    }

    return output;
}

}//namespace


const ArrayType EXPECTED1 = {1};
const ArrayType EXPECTED2 = {1, 3, 5, 9};


THE_BENCHMARK(NumbersHavingFirstAndLastBitsSet,
              std::numeric_limits<ArrayType::value_type>::max());

SIMPLE_TEST(NumbersHavingFirstAndLastBitsSet, TestSample1, EXPECTED1, 1);
SIMPLE_TEST(NumbersHavingFirstAndLastBitsSet, TestSample2, EXPECTED2, 10);
