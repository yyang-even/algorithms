#include "common_header.h"

#include "hash/hash.h"


namespace {

using ArrayType = std::vector<unsigned>;

/** Find pair with greatest product in array
 *
 * @reference   https://www.geeksforgeeks.org/find-pair-with-greatest-product-in-array/
 *
 * Given an array of n elements, the task is to find the greatest number such that it is
 * product of two elements of given array. If no such element exists, print -1. Elements
 * are within the range of 1 to 10^5.
 */
int GreatestNumberInArrayAsProductOfTwoArrayElements(ArrayType elements) {
    const auto counters = ToFrequencyHashTable(elements);

    std::sort(elements.begin(), elements.end());

    for (auto product_iter = elements.crbegin();
         product_iter != elements.crend();
         ++product_iter) {
        ArrayType::value_type elem_sqrt = sqrt(*product_iter);
        for (auto factor_iter = elements.cbegin();
             factor_iter != elements.cend() and * factor_iter <= elem_sqrt; ++factor_iter) {
            if (*product_iter % *factor_iter == 0) {
                const auto the_other_factor = *product_iter / *factor_iter;
                const auto the_other_factor_iter = counters.find(the_other_factor);
                if (the_other_factor_iter != counters.cend() and
                    the_other_factor_iter->second > (the_other_factor == *factor_iter)) {
                    return *product_iter;
                }
            }
        }
    }

    return -1;
}

}//namespace


const ArrayType SAMPLE1 = {10, 3, 5, 30, 35};
const ArrayType SAMPLE2 = {2, 5, 7, 8};
const ArrayType SAMPLE3 = {10, 2, 4, 30, 35};
const ArrayType SAMPLE4 = {10, 2, 2, 4, 30, 35};
const ArrayType SAMPLE5 = {17, 2, 1, 15, 30};
const ArrayType SAMPLE6 = {30, 10, 9, 3, 35};
const ArrayType SAMPLE7 = {30, 10, 9, 5, 25};


THE_BENCHMARK(GreatestNumberInArrayAsProductOfTwoArrayElements, SAMPLE1);

SIMPLE_TEST(GreatestNumberInArrayAsProductOfTwoArrayElements, TestSAMPLE1, 30, SAMPLE1);
SIMPLE_TEST(GreatestNumberInArrayAsProductOfTwoArrayElements, TestSAMPLE2, -1, SAMPLE2);
SIMPLE_TEST(GreatestNumberInArrayAsProductOfTwoArrayElements, TestSAMPLE3, -1, SAMPLE3);
SIMPLE_TEST(GreatestNumberInArrayAsProductOfTwoArrayElements, TestSAMPLE4, 4, SAMPLE4);
SIMPLE_TEST(GreatestNumberInArrayAsProductOfTwoArrayElements, TestSAMPLE5, 30, SAMPLE5);
SIMPLE_TEST(GreatestNumberInArrayAsProductOfTwoArrayElements, TestSAMPLE6, 30, SAMPLE6);
SIMPLE_TEST(GreatestNumberInArrayAsProductOfTwoArrayElements, TestSAMPLE7, -1, SAMPLE7);
