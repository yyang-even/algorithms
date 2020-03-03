#include "common_header.h"

#include "count_frequencies_of_all_elements.h"

#include "ordering/count_occurrences_in_sorted_array.h"

namespace {

using ArrayType = std::vector<int>;

/** Count frequencies of all elements in array in O(1) extra space and O(n) time
 *
 * @reference   https://www.geeksforgeeks.org/count-frequencies-elements-array-o1-extra-space-time/
 *
 * Given an unsorted array of n integers which can contain integers from 1 to n. Some elements can
 * be repeated multiple times and some other elements can be absent from the array. Count frequency
 * of all elements that are present and print the missing elements.
 *
 * @reference   Counting frequencies of array elements
 *              https://www.geeksforgeeks.org/counting-frequencies-of-array-elements/
 */
auto CountFrequenciesOfAllElements_InPlace_Sign(ArrayType elements) {
    for (auto iter = elements.begin(); iter != elements.end();) {
        auto &elem = *iter;
        if (elem > 0) {
            const auto index = elem - 1;
            auto &count = elements[index];
            if (count > 0) {
                elem = count;
                count = -1;
            } else {
                --count;
                elem = 0;
                ++iter;
            }
        } else {
            ++iter;
        }
    }

    std::map<ArrayType::value_type, ArrayType::size_type> output;
    for (ArrayType::size_type i = 0; i < elements.size(); ++i) {
        output.emplace(i + 1, abs(elements[i]));
    }

    return output;
}


auto CountFrequenciesOfAllElements_STL(const ArrayType &elements) {
    std::map<ArrayType::value_type, ArrayType::size_type> output;
    for (ArrayType::size_type i = 0; i < elements.size(); ++i) {
        ++output[elements[i]];
        output[i + 1];
    }

    return output;
}


auto CountFrequenciesOfAllElements_InPlace_Mod(ArrayType elements) {
    std::transform(elements.cbegin(), elements.cend(), elements.begin(), [](const auto elem) {
        return elem - 1;
    });

    TransformToInplaceCounterArray(elements, elements.size());

    std::map<ArrayType::value_type, ArrayType::size_type> output;
    for (ArrayType::size_type i = 0; i < elements.size(); ++i) {
        output.emplace(i + 1, (elements[i] / elements.size()));
    }

    return output;
}


/** Print numbers in descending order along with their frequencies
 *
 * @reference   https://www.geeksforgeeks.org/print-numbers-in-descending-order-along-with-their-frequencies/
 * @reference   Print 2-D co-ordinate points in ascending order followed by their frequencies
 *              https://www.geeksforgeeks.org/print-2-d-co-ordinate-points-in-ascending-order-followed-by-their-frequencies/
 * @reference   Descending order in Map and Multimap of C++ STL
 *              https://www.geeksforgeeks.org/descending-order-map-multimap-c-stl/
 */
using ValueCountPair = std::pair<ArrayType::value_type, ArrayType::size_type>;

auto SortAndCount(ArrayType values) {
    std::sort(values.begin(), values.end(), std::greater<ArrayType::value_type> {});
    return CountAllOccurrencesInSortedArray_STL(values, std::greater<ArrayType::value_type> {});
}


auto SortAndCount_BucketSort(const ArrayType &values) {
    std::map<ArrayType::value_type, ArrayType::size_type, std::greater<ArrayType::value_type>> buckets;
    for (const auto v : values) {
        ++buckets[v];
    }

    std::vector<ValueCountPair> outputs;
    for (const auto &value_count_pair : buckets) {
        outputs.emplace_back(value_count_pair);
    }

    return outputs;
}


/**
 * @reference   Print characters in decreasing order of frequency
 *              https://www.geeksforgeeks.org/print-characters-in-decreasing-order-of-frequency/
 *
 * Given a string str, the task is to print the characters in decreasing order of their frequency.
 * If the frequency of two characters is same then sort them in descending order alphabetically.
 */


/**
 * @reference   Print characters and their frequencies in order of occurrence
 *              https://www.geeksforgeeks.org/print-characters-frequencies-order-occurrence/
 *
 * Given a string str containing only lowercase characters. The problem is to print the characters
 * along with their frequency in the order of their occurrence and in the given format explained
 * in the examples below.
 */

}//namespace


const ArrayType SAMPLE1 = {2, 3, 3, 2, 5};
const ArrayType SAMPLE2 = {1};
const ArrayType SAMPLE3 = {4, 4, 4, 4};
const ArrayType SAMPLE4 = {1, 3, 5, 7, 9, 1, 3, 5, 7, 9, 1};
const ArrayType SAMPLE5 = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
const ArrayType SAMPLE6 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
const ArrayType SAMPLE7 = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};


SIMPLE_BENCHMARK(CountFrequenciesOfAllElements_InPlace_Sign, SAMPLE1);

MUTUAL_SIMPLE_TEST(CountFrequenciesOfAllElements_STL, CountFrequenciesOfAllElements_InPlace_Sign,
                   TestSAMPLE1, SAMPLE1);
MUTUAL_SIMPLE_TEST(CountFrequenciesOfAllElements_STL, CountFrequenciesOfAllElements_InPlace_Sign,
                   TestSAMPLE2, SAMPLE2);
MUTUAL_SIMPLE_TEST(CountFrequenciesOfAllElements_STL, CountFrequenciesOfAllElements_InPlace_Sign,
                   TestSAMPLE3, SAMPLE3);
MUTUAL_SIMPLE_TEST(CountFrequenciesOfAllElements_STL, CountFrequenciesOfAllElements_InPlace_Sign,
                   TestSAMPLE4, SAMPLE4);
MUTUAL_SIMPLE_TEST(CountFrequenciesOfAllElements_STL, CountFrequenciesOfAllElements_InPlace_Sign,
                   TestSAMPLE5, SAMPLE5);
MUTUAL_SIMPLE_TEST(CountFrequenciesOfAllElements_STL, CountFrequenciesOfAllElements_InPlace_Sign,
                   TestSAMPLE6, SAMPLE6);
MUTUAL_SIMPLE_TEST(CountFrequenciesOfAllElements_STL, CountFrequenciesOfAllElements_InPlace_Sign,
                   TestSAMPLE7, SAMPLE7);


SIMPLE_BENCHMARK(CountFrequenciesOfAllElements_STL, SAMPLE1);


SIMPLE_BENCHMARK(CountFrequenciesOfAllElements_InPlace_Mod, SAMPLE1);

MUTUAL_SIMPLE_TEST(CountFrequenciesOfAllElements_STL, CountFrequenciesOfAllElements_InPlace_Mod,
                   TestSAMPLE1, SAMPLE1);
MUTUAL_SIMPLE_TEST(CountFrequenciesOfAllElements_STL, CountFrequenciesOfAllElements_InPlace_Mod,
                   TestSAMPLE2, SAMPLE2);
MUTUAL_SIMPLE_TEST(CountFrequenciesOfAllElements_STL, CountFrequenciesOfAllElements_InPlace_Mod,
                   TestSAMPLE3, SAMPLE3);
MUTUAL_SIMPLE_TEST(CountFrequenciesOfAllElements_STL, CountFrequenciesOfAllElements_InPlace_Mod,
                   TestSAMPLE4, SAMPLE4);
MUTUAL_SIMPLE_TEST(CountFrequenciesOfAllElements_STL, CountFrequenciesOfAllElements_InPlace_Mod,
                   TestSAMPLE5, SAMPLE5);
MUTUAL_SIMPLE_TEST(CountFrequenciesOfAllElements_STL, CountFrequenciesOfAllElements_InPlace_Mod,
                   TestSAMPLE6, SAMPLE6);
MUTUAL_SIMPLE_TEST(CountFrequenciesOfAllElements_STL, CountFrequenciesOfAllElements_InPlace_Mod,
                   TestSAMPLE7, SAMPLE7);


const ArrayType VALUES1 = {1, 1, 2, 2, 2, 2, 3};
const std::vector<ValueCountPair> EXPECTED1 = {{3, 1}, {2, 4}, {1, 2}};
const ArrayType VALUES2 = {1, 3, 3, 3, 4, 4, 5};
const std::vector<ValueCountPair> EXPECTED2 = {{5, 1}, {4, 2}, {3, 3}, {1, 1}};
const ArrayType VALUES3 = {1, 1, 1, 2, 3, 4, 9, 9, 10};
const std::vector<ValueCountPair> EXPECTED3 = {{10, 1}, {9, 2}, {4, 1}, {3, 1}, {2, 1}, {1, 3}};


SIMPLE_BENCHMARK(SortAndCount, VALUES1);

SIMPLE_TEST(SortAndCount, TestSAMPLE1, EXPECTED1, VALUES1);
SIMPLE_TEST(SortAndCount, TestSAMPLE2, EXPECTED2, VALUES2);
SIMPLE_TEST(SortAndCount, TestSAMPLE3, EXPECTED3, VALUES3);


SIMPLE_BENCHMARK(SortAndCount_BucketSort, VALUES1);

SIMPLE_TEST(SortAndCount_BucketSort, TestSAMPLE1, EXPECTED1, VALUES1);
SIMPLE_TEST(SortAndCount_BucketSort, TestSAMPLE2, EXPECTED2, VALUES2);
SIMPLE_TEST(SortAndCount_BucketSort, TestSAMPLE3, EXPECTED3, VALUES3);
