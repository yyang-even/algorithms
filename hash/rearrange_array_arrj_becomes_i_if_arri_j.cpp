#include "common_header.h"


namespace {

using ArrayType = std::vector<unsigned>;

/** Rearrange an array such that 'arr[j]' becomes 'i' if 'arr[i]' is 'j' | Set 1
 *
 * @reference   https://www.geeksforgeeks.org/rearrange-array-arrj-becomes-arri-j/
 *
 * Given an array of size n where all elements are distinct and in range from 0 to n-1,
 * change contents of arr[] so that arr[i] = j is changed to arr[j] = i.
 */
auto RearrangeArraySimple(const ArrayType &elements) {
    auto output = elements;

    for (ArrayType::size_type i = 0; i < elements.size(); ++i) {
        const auto j = elements[i];
        output[j] = i;
    }

    return output;
}


auto RearrangeArrayInPlace(ArrayType elements) {
    const auto N = elements.size();
    for (ArrayType::size_type i = 0; i < N; ++i) {
        elements[elements[i] % N] += i * N;
    }

    std::transform(elements.cbegin(), elements.cend(),
    elements.begin(), [&elements](const auto v) {
        return v / elements.size();
    });

    return elements;
}

}//namespace


const ArrayType SAMPLE1 = {1, 3, 0, 2};
const ArrayType EXPECTED1 = {2, 0, 3, 1};

const ArrayType SAMPLE2 = {2, 0, 1, 4, 5, 3};
const ArrayType EXPECTED2 = {1, 2, 0, 5, 3, 4};

const ArrayType SAMPLE3 = {0, 1, 2, 3};
const ArrayType EXPECTED3 = {0, 1, 2, 3};

const ArrayType SAMPLE4 = {3, 2, 1, 0};
const ArrayType EXPECTED4 = {3, 2, 1, 0};


THE_BENCHMARK(RearrangeArraySimple, SAMPLE1);

SIMPLE_TEST(RearrangeArraySimple, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(RearrangeArraySimple, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(RearrangeArraySimple, TestSAMPLE3, EXPECTED3, SAMPLE3);
SIMPLE_TEST(RearrangeArraySimple, TestSAMPLE4, EXPECTED4, SAMPLE4);


THE_BENCHMARK(RearrangeArrayInPlace, SAMPLE1);

SIMPLE_TEST(RearrangeArrayInPlace, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(RearrangeArrayInPlace, TestSAMPLE2, EXPECTED2, SAMPLE2);
SIMPLE_TEST(RearrangeArrayInPlace, TestSAMPLE3, EXPECTED3, SAMPLE3);
SIMPLE_TEST(RearrangeArrayInPlace, TestSAMPLE4, EXPECTED4, SAMPLE4);
