#include "common_header.h"

#include "find_the_element_helper.h"
#include "clear_all_bits_except_the_last_set_bit.h"


namespace {

using ArrayType = std::vector<unsigned>;

/** Find the repeating and the missing | Added 3 new methods
 *
 * @reference   https://www.geeksforgeeks.org/find-a-repeating-and-a-missing-number/
 *
 * Given an unsorted array of size n. Array elements are in range from 1 to n. One number
 * from set {1, 2, ..., n} is missing and one number occurs twice in array. Find these
 * two numbers.
 *
 * @reference   Set Mismatch
 *              https://leetcode.com/problems/set-mismatch/
 *
 * You have a set of integers s, which originally contains all the numbers from 1 to n.
 * Unfortunately, due to some error, one of the numbers in s got duplicated to another
 * number in the set, which results in repetition of one number and loss of another
 * number. You are given an integer array nums representing the data status of this set
 * after the error. Find the number that occurs twice and the number that is missing and
 * return them in the form of an array.
 */
auto FindTheRepeatingAndMissing_Xor(const ArrayType &elements) {
    assert(not elements.empty());

    const auto N = elements.size();
    ArrayType::value_type xor_of_all = N;
    ArrayType::value_type x = 0;
    ArrayType::value_type y = 0;

    for (ArrayType::size_type i = 0; i < N; ++i) {
        xor_of_all ^= (i ^ elements[i]);
    }

    const auto last_set_bit = ClearAllBitsExceptTheLastSetBit(xor_of_all);

    for (ArrayType::size_type i = 0; i < N; ++i) {
        divideElement<ArrayType::value_type>(i, last_set_bit, x, y);
        divideElement<ArrayType::value_type>(elements[i], last_set_bit, x, y);
    }
    divideElement<ArrayType::value_type>(N, last_set_bit, x, y);

    for (const auto elem : elements) {
        if (elem == x) {
            return std::pair(x, y);
        }
    }
    return std::pair(y, x);
}


auto FindTheRepeatingAndMissing_Hash(const ArrayType &nums) {
    int counts[nums.size() + 1] = {};

    for (const auto n : nums) {
        ++counts[n];
    }

    int duplicate = 0;
    int missing = 0;
    for (std::size_t i = 1; i <= nums.size(); ++i) {
        if (counts[i] == 0) {
            missing = i;
        } else if (counts[i] == 2) {
            duplicate = i;
        }
    }

    return std::pair(duplicate, missing);
}

}//namespace


const ArrayType SAMPLE1 = {3, 1, 3};
const ArrayType SAMPLE2 = {4, 3, 6, 2, 1, 1};
const ArrayType SAMPLE3 = {1, 2, 2, 4};
const ArrayType SAMPLE4 = {1, 1};


THE_BENCHMARK(FindTheRepeatingAndMissing_Xor, SAMPLE1);

SIMPLE_TEST(FindTheRepeatingAndMissing_Xor, TestSample1, std::pair(3u, 2u), SAMPLE1);
SIMPLE_TEST(FindTheRepeatingAndMissing_Xor, TestSample2, std::pair(1u, 5u), SAMPLE2);
SIMPLE_TEST(FindTheRepeatingAndMissing_Xor, TestSample3, std::pair(2u, 3u), SAMPLE3);
SIMPLE_TEST(FindTheRepeatingAndMissing_Xor, TestSample4, std::pair(1u, 2u), SAMPLE4);


THE_BENCHMARK(FindTheRepeatingAndMissing_Hash, SAMPLE1);

SIMPLE_TEST(FindTheRepeatingAndMissing_Hash, TestSample1, std::pair(3u, 2u), SAMPLE1);
SIMPLE_TEST(FindTheRepeatingAndMissing_Hash, TestSample2, std::pair(1u, 5u), SAMPLE2);
SIMPLE_TEST(FindTheRepeatingAndMissing_Hash, TestSample3, std::pair(2u, 3u), SAMPLE3);
SIMPLE_TEST(FindTheRepeatingAndMissing_Hash, TestSample4, std::pair(1u, 2u), SAMPLE4);
