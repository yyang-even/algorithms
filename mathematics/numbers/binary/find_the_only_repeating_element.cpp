#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Find the only repetitive element between 1 to n-1
 *
 * @reference   https://www.geeksforgeeks.org/find-repetitive-element-1-n-1/
 *
 * We are given an array arr[] of size n. Numbers are from 1 to (n-1) in random order.
 * The array has only one repetitive element. We need to find the repetitive element.
 */
inline auto FindTheOnlyRepeatingElement_Sum(const ArrayType &elements) {
    const auto sum = std::accumulate(elements.cbegin(), elements.cend(), 0u);
    return sum - (elements.size() - 1) * elements.size() / 2;
}


auto FindTheOnlyRepeatingElement_Hash(const ArrayType &elements) {
    std::vector<bool> counters(elements.size(), false);
    for (const auto elem : elements) {
        if (counters[elem]) {
            return elem;
        }
        counters[elem] = true;
    }

    return 0;
}


auto FindTheOnlyRepeatingElement_Xor(const ArrayType &elements) {
    ArrayType::value_type result = 0;
    for (unsigned i = 0; i < elements.size() - 1; ++i) {
        result ^= ((i + 1) ^ elements[i]);
    }

    return result ^ elements.back();
}


auto FindTheOnlyRepeatingElement_InPlace(ArrayType elements) {
    for (const auto elem : elements) {
        const auto absolute_element = std::abs(elem);
        auto &counter = elements[absolute_element];
        if (counter < 0) {
            return absolute_element;
        }
        counter = -counter;
    }

    return 0;
}


/** Find the only repeating element in a sorted array of size n
 *
 * @reference   https://www.geeksforgeeks.org/find-repeating-element-sorted-array-size-n/
 *
 * Given a sorted array of n elements containing elements in range from 1 to n-1 i.e.
 * One element occurs twice, the task is to find the repeating element in an array.
 */
ArrayType::value_type FindTheOnlyRepeatingElement_Sorted_BinarySearch(
    const ArrayType &elements,
    const ArrayType::size_type low,
    const ArrayType::size_type high) {
    if (low > high) {
        return 0;
    }

    const auto mid = (low + high) / 2;
    if (elements[mid] - mid != 1) {
        if (mid > 0 and elements[mid] == elements[mid - 1]) {
            return mid;
        }
        return FindTheOnlyRepeatingElement_Sorted_BinarySearch(elements, low, mid - 1);
    }

    return FindTheOnlyRepeatingElement_Sorted_BinarySearch(elements, mid + 1, high);
}

inline auto
FindTheOnlyRepeatingElement_Sorted_BinarySearch(const ArrayType &elements) {
    return FindTheOnlyRepeatingElement_Sorted_BinarySearch(
               elements, 0, elements.size() - 1);
}

}//namespace


const ArrayType SAMPLE1 = {1, 3, 2, 3, 4};
const ArrayType SAMPLE2 = {1, 5, 1, 2, 3, 4};
const ArrayType SAMPLE3 = {9, 8, 2, 6, 1, 8, 5, 3, 4, 7};


THE_BENCHMARK(FindTheOnlyRepeatingElement_Sum, SAMPLE1);

SIMPLE_TEST(FindTheOnlyRepeatingElement_Sum, TestSample1, 3, SAMPLE1);
SIMPLE_TEST(FindTheOnlyRepeatingElement_Sum, TestSample2, 1, SAMPLE2);
SIMPLE_TEST(FindTheOnlyRepeatingElement_Sum, TestSample3, 8, SAMPLE3);


THE_BENCHMARK(FindTheOnlyRepeatingElement_Hash, SAMPLE1);

SIMPLE_TEST(FindTheOnlyRepeatingElement_Hash, TestSample1, 3, SAMPLE1);
SIMPLE_TEST(FindTheOnlyRepeatingElement_Hash, TestSample2, 1, SAMPLE2);
SIMPLE_TEST(FindTheOnlyRepeatingElement_Hash, TestSample3, 8, SAMPLE3);


THE_BENCHMARK(FindTheOnlyRepeatingElement_Xor, SAMPLE1);

SIMPLE_TEST(FindTheOnlyRepeatingElement_Xor, TestSample1, 3, SAMPLE1);
SIMPLE_TEST(FindTheOnlyRepeatingElement_Xor, TestSample2, 1, SAMPLE2);
SIMPLE_TEST(FindTheOnlyRepeatingElement_Xor, TestSample3, 8, SAMPLE3);


THE_BENCHMARK(FindTheOnlyRepeatingElement_InPlace, SAMPLE1);

SIMPLE_TEST(FindTheOnlyRepeatingElement_InPlace, TestSample1, 3, SAMPLE1);
SIMPLE_TEST(FindTheOnlyRepeatingElement_InPlace, TestSample2, 1, SAMPLE2);
SIMPLE_TEST(FindTheOnlyRepeatingElement_InPlace, TestSample3, 8, SAMPLE3);


const ArrayType SAMPLE4 = {1, 1, 2, 3, 4};
const ArrayType SAMPLE5 = {1, 2, 3, 4, 4};
const ArrayType SAMPLE6 = {1, 2, 3, 3, 4};


THE_BENCHMARK(FindTheOnlyRepeatingElement_Sorted_BinarySearch, SAMPLE6);

SIMPLE_TEST(FindTheOnlyRepeatingElement_Sorted_BinarySearch, TestFront, SAMPLE4.front(),
            SAMPLE4);
SIMPLE_TEST(FindTheOnlyRepeatingElement_Sorted_BinarySearch, TestBack, SAMPLE5.back(),
            SAMPLE5);
SIMPLE_TEST(FindTheOnlyRepeatingElement_Sorted_BinarySearch, TestSample6, 3, SAMPLE6);
