#include "common_header.h"


namespace {

using ArrayType = std::vector<unsigned>;

/** Add minimum number to an array so that the sum becomes even
 *
 * @reference   https://www.geeksforgeeks.org/add-minimum-number-to-an-array-so-that-the-sum-becomes-even/
 *
 * Given an array, write a program to add the minimum number(should be greater than 0)
 * to the array so that the sum of array becomes even.
 *
 * @complexity  O(n)
 */
auto AddMinimumNumberToEvenSum(const ArrayType &numbers) {
    auto isOdd = false;

    for (const auto num : numbers) {
        if (num % 2) {
            isOdd = !isOdd;
        }
    }

    return isOdd ? 1 : 2;
}

}//namespace


const ArrayType SAMPLE1 = {1, 2, 3, 4, 5, 6, 7, 8};
const ArrayType SAMPLE2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};


THE_BENCHMARK(AddMinimumNumberToEvenSum, SAMPLE1);

SIMPLE_TEST(AddMinimumNumberToEvenSum, TestSample1, 2, SAMPLE1);
SIMPLE_TEST(AddMinimumNumberToEvenSum, TestSample2, 1, SAMPLE2);
