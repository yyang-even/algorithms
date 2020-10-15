#include "common_header.h"


namespace {

using ArrayType = std::vector<unsigned>;

/** Find the Missing Number
 *
 * @reference   https://www.geeksforgeeks.org/find-the-missing-number/
 *
 * You are given a list of n-1 integers and these integers are in the range of 1 to n.
 * There are no duplicates in list. One of the integers is missing in the list.
 * Write an efficient code to find the missing integer.
 *
 * @complexity  O(n)
 */
auto FindTheMissingNumber_Sum(const ArrayType &integers) {
    assert(not integers.empty());

    const auto N = integers.size() + 1u;
    const auto sum = N * (N + 1) / 2;
    return std::accumulate(integers.cbegin(), integers.cend(), sum,
                           std::minus<ArrayType::value_type> {});
}


auto FindTheMissingNumber_Xor(const ArrayType &integers,
                              ArrayType::value_type min = 1) {
    assert(not integers.empty());

    const ArrayType::value_type N = integers.size() + min;
    auto xor_of_all = integers[0] ^ min++;
    for (ArrayType::size_type i = 1ul; i < integers.size(); ++i) {
        xor_of_all ^= (min++ ^ integers[i]);
    }

    return xor_of_all ^ N;
}


/** Find the one missing number in range
 *
 * @reference   https://www.geeksforgeeks.org/find-one-missing-number-range/
 *
 * Given an array of size n. It is also given that range of numbers is from smallestNumber
 * to smallestNumber + n where smallestNumber is the smallest number in array. The array
 * contains number in this range but one number is missing so the task is to find this
 * missing number.
 */
auto FindTheMissingNumberRange_Xor(const ArrayType &integers) {
    const auto min = std::min_element(integers.cbegin(), integers.cend());

    return FindTheMissingNumber_Xor(integers, *min);
}


/** Find missing element in a sorted array of consecutive numbers
 *
 * @reference   https://www.geeksforgeeks.org/find-missing-element-in-a-sorted-array-of-consecutive-numbers/
 *
 * Given an array arr[] of n distinct integers. Elements are placed sequentially in
 * ascending order with one element missing. The task is to find the missing element.
 */
int FindTheMissingNumber_SortedRange_BinarySearch(const ArrayType &values) {
    assert(not values.empty());
    assert(std::is_sorted(values.cbegin(), values.cend()));

    ArrayType::size_type low = 0;
    auto high = values.size() - 1;

    while (high > low) {
        const auto mid = (low + high) / 2;

        if (values[mid] - mid == values.front()) {
            if (values[mid + 1] - values[mid] > 1) {
                return values[mid] + 1;
            }
            low = mid + 1;
        } else {
            if (values[mid] - values[mid - 1] > 1) {
                return values[mid] - 1;
            }
            high = mid - 1;
        }
    }

    return -1;
}


/** Find the Missing Number in a sorted array
 *
 * @reference   https://www.geeksforgeeks.org/find-the-missing-number-in-a-sorted-array/
 *
 * Given a list of n-1 integers and these integers are in the range of 1 to n. There
 * are no duplicates in list. One of the integers is missing in the list. Write an
 * efficient code to find the missing integer.
 *
 * @reference   Find the missing number in a sorted array of limited range
 *              https://www.geeksforgeeks.org/find-missing-number-sorted-array-limited-range/
 *
 * Given a sorted array of size n and given that there are numbers from 1 to n+1 with
 * one missing, the missing number is to be found. It may be assumed that array has
 * distinct elements.
 */
int FindTheMissingNumber_Sorted_BinarySearch(const ArrayType &values) {
    assert(not values.empty());
    assert(std::is_sorted(values.cbegin(), values.cend()));

    ArrayType::size_type low = 0;
    const auto last = values.size() - 1;
    auto high = last;

    while (high >= low) {
        const auto mid = (low + high) / 2;
        if (values[mid] - mid == 1) {
            if (mid == last or values[mid + 1] - values[mid] > 1) {
                return values[mid] + 1;
            }
            low = mid + 1;
        } else {
            if (mid == 0 or values[mid] - values[mid - 1] > 1) {
                return values[mid] - 1;
            }
            high = mid - 1;
        }
    }

    return -1;
}


/**
 * @reference   Find the only missing number in a sorted array
 *              https://www.geeksforgeeks.org/find-the-only-missing-number-in-a-sorted-array/
 */
int FindTheMissingNumber_Sorted_BinaryLast(const ArrayType &values) {
    assert(not values.empty());
    assert(std::is_sorted(values.cbegin(), values.cend()));

    if (values.front() != 1) {
        return 1;
    }
    if (values.back() != values.size() + 1) {
        return values.size() + 1;
    }

    ArrayType::size_type low = 0;
    auto high = values.size() - 1;

    while (high >= low) {
        const auto mid = (low + high) / 2;
        if (values[mid] != mid + 1) {
            if (values[mid - 1] == mid) {
                return mid + 1;
            }
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return -1;
}

}//namespace


const ArrayType SAMPLE1 = {1, 2, 4, 6, 3, 7, 8};
const ArrayType SAMPLE2 = {1, 2, 4, 5, 6};


SIMPLE_BENCHMARK(FindTheMissingNumber_Sum, Sample1, SAMPLE1);

SIMPLE_TEST(FindTheMissingNumber_Sum, TestSample1, 5u, SAMPLE1);
SIMPLE_TEST(FindTheMissingNumber_Sum, TestSample2, 3u, SAMPLE2);


SIMPLE_BENCHMARK(FindTheMissingNumber_Xor, Sample1, SAMPLE1);

SIMPLE_TEST(FindTheMissingNumber_Xor, TestSample1, 5u, SAMPLE1);
SIMPLE_TEST(FindTheMissingNumber_Xor, TestSample2, 3u, SAMPLE2);


const ArrayType SAMPLE3 = {13, 12, 11, 15};
const ArrayType SAMPLE4 = {33, 36, 35, 34};


SIMPLE_BENCHMARK(FindTheMissingNumberRange_Xor, Sample1, SAMPLE1);

SIMPLE_TEST(FindTheMissingNumberRange_Xor, TestSample1, 5u, SAMPLE1);
SIMPLE_TEST(FindTheMissingNumberRange_Xor, TestSample2, 3u, SAMPLE2);
SIMPLE_TEST(FindTheMissingNumberRange_Xor, TestSample3, 14u, SAMPLE3);
SIMPLE_TEST(FindTheMissingNumberRange_Xor, TestSample4, 37u, SAMPLE4);


SIMPLE_BENCHMARK(FindTheMissingNumber_SortedRange_BinarySearch, Sample1, SAMPLE2);

SIMPLE_TEST(FindTheMissingNumber_SortedRange_BinarySearch, TestSample2, 3, SAMPLE2);


const ArrayType SAMPLE5 = {2, 3, 4, 5, 6};
const ArrayType SAMPLE6 = {1, 2, 3, 4, 5};


SIMPLE_BENCHMARK(FindTheMissingNumber_Sorted_BinarySearch, Sample1, SAMPLE2);

SIMPLE_TEST(FindTheMissingNumber_Sorted_BinarySearch, TestSample2, 3, SAMPLE2);
SIMPLE_TEST(FindTheMissingNumber_Sorted_BinarySearch, TestBegin, 1, SAMPLE5);
SIMPLE_TEST(FindTheMissingNumber_Sorted_BinarySearch, TestLast, SAMPLE6.size() + 1,
            SAMPLE6);


SIMPLE_BENCHMARK(FindTheMissingNumber_Sorted_BinaryLast, Sample1, SAMPLE2);

SIMPLE_TEST(FindTheMissingNumber_Sorted_BinaryLast, TestSample2, 3, SAMPLE2);
SIMPLE_TEST(FindTheMissingNumber_Sorted_BinaryLast, TestBegin, 1, SAMPLE5);
SIMPLE_TEST(FindTheMissingNumber_Sorted_BinaryLast, TestLast, SAMPLE6.size() + 1,
            SAMPLE6);
