#include "common_header.h"

#include "count_frequencies_of_all_elements.h"


namespace {

using ArrayType = std::vector<int>;

/** Count frequencies of all elements in array in O(1) extra space and O(n) time
 *
 * @reference   https://www.geeksforgeeks.org/count-frequencies-elements-array-o1-extra-space-time/
 *
 * Given an unsorted array of n integers which can contain integers from 1 to n. Some elements can
 * be repeated multiple times and some other elements can be absent from the array. Count frequency
 * of all elements that are present and print the missing elements.
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
