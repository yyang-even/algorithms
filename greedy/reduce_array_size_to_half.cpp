#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Reduce Array Size to The Half
 *
 * @reference   https://leetcode.com/problems/reduce-array-size-to-the-half/
 *
 * Given an array arr.  You can choose a set of integers and remove all the occurrences
 * of these integers in the array. Return the minimum size of the set so that at least
 * half of the integers of the array are removed.
 *  1 <= arr.length <= 10^5
 *  arr.length is even.
 *  1 <= arr[i] <= 10^5
 */
auto ReduceArraySizeToHalf_Sort(const ArrayType &elements) {
    std::unordered_map<ArrayType::value_type, int> counter;
    for (const auto a_number : elements) {
        ++counter[a_number];
    }

    ArrayType frequencies;
    for (const auto [_, a_frequency] : counter) {
        frequencies.push_back(a_frequency);
    }

    std::sort(frequencies.begin(), frequencies.end(), std::greater<ArrayType::value_type> {});

    int expected = elements.size() / 2;
    int result = 0;
    for (const auto a_frequency : frequencies) {
        expected -= a_frequency;
        ++result;
        if (expected <= 0) {
            break;
        }
    }

    return result;
}


auto ReduceArraySizeToHalf_Bucket(const ArrayType &elements) {
    std::unordered_map<ArrayType::value_type, int> counter;
    for (const auto a_number : elements) {
        ++counter[a_number];
    }

    int buckets[elements.size() + 1] = {};
    for (const auto [_, a_frequency] : counter) {
        ++buckets[a_frequency];
    }

    int expected = elements.size() / 2;
    int result = 0;
    for (int i = elements.size(); i >= 1; --i) {
        for (int size = buckets[i]; size; --size) {
            expected -= i;
            ++result;
            if (expected <= 0) {
                return result;
            }
        }
    }

    return result;
}

}//namespace


const ArrayType SAMPLE1 = {3, 3, 3, 3, 5, 5, 5, 2, 2, 7};
const ArrayType SAMPLE2 = {7, 7, 7, 7, 7, 7};
const ArrayType SAMPLE3 = {1, 9};
const ArrayType SAMPLE4 = {1000, 1000, 3, 7};
const ArrayType SAMPLE5 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};


THE_BENCHMARK(ReduceArraySizeToHalf_Sort, SAMPLE1);

SIMPLE_TEST(ReduceArraySizeToHalf_Sort, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(ReduceArraySizeToHalf_Sort, TestSAMPLE2, 1, SAMPLE2);
SIMPLE_TEST(ReduceArraySizeToHalf_Sort, TestSAMPLE3, 1, SAMPLE3);
SIMPLE_TEST(ReduceArraySizeToHalf_Sort, TestSAMPLE4, 1, SAMPLE4);
SIMPLE_TEST(ReduceArraySizeToHalf_Sort, TestSAMPLE5, 5, SAMPLE5);


THE_BENCHMARK(ReduceArraySizeToHalf_Bucket, SAMPLE1);

SIMPLE_TEST(ReduceArraySizeToHalf_Bucket, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(ReduceArraySizeToHalf_Bucket, TestSAMPLE2, 1, SAMPLE2);
SIMPLE_TEST(ReduceArraySizeToHalf_Bucket, TestSAMPLE3, 1, SAMPLE3);
SIMPLE_TEST(ReduceArraySizeToHalf_Bucket, TestSAMPLE4, 1, SAMPLE4);
SIMPLE_TEST(ReduceArraySizeToHalf_Bucket, TestSAMPLE5, 5, SAMPLE5);
