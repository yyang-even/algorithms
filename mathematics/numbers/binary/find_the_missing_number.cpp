#include "common_header.h"

#include "is_bit_set.h"


namespace {

using ArrayType = std::vector<int>;

/** Find the Missing Number
 *
 * @reference   https://www.geeksforgeeks.org/find-the-missing-number/
 *
 * You are given a list of n-1 integers and these integers are in the range of 1 to n.
 * There are no duplicates in list. One of the integers is missing in the list. Write an
 * efficient code to find the missing integer.
 *
 * @reference   Missing Number
 *              https://leetcode.com/problems/missing-number/
 *
 * Given an array nums containing n distinct numbers in the range [0, n], return the
 * only number in the range that is missing from the array.
 * Follow up: Could you implement a solution using only O(1) extra space complexity and
 * O(n) runtime complexity?
 *
 * @complexity  O(n)
 */
inline auto FindTheMissingNumber_Sum(const ArrayType &integers) {
    assert(not integers.empty());

    const auto N = integers.size() + 1;
    const auto sum = N * (N + 1) / 2;
    return std::accumulate(integers.cbegin(), integers.cend(), sum,
                           std::minus<ArrayType::value_type> {});
}


auto FindTheMissingNumber_Xor(const ArrayType &integers,
                              ArrayType::value_type min = 1) {
    assert(not integers.empty());

    const ArrayType::value_type N = integers.size() + min;
    auto xor_of_all = integers[0] ^ min++;
    for (ArrayType::size_type i = 1; i < integers.size(); ++i) {
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
inline auto FindTheMissingNumberRange_Xor(const ArrayType &integers) {
    const auto min = std::min_element(integers.cbegin(), integers.cend());

    return FindTheMissingNumber_Xor(integers, *min);
}


/**
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 5.7.
 *
 * An array A contains all the integers from 0 through n, except for one number which is
 * missing. In this problem, we cannot access an entire integer in A with a single
 * operation. The elements of A are represented in binary, and the only operation we can
 * use to access them is "fetch the jth bit of A[i]," which takes constant time. Write
 * code to find the missing integer. Can you do it in 0(n) time?
 */
unsigned FindTheMissingNumber_Partition_Helper(const ArrayType::iterator begin,
                                               const ArrayType::iterator end,
                                               const unsigned column = 0) {
    if (column >= BitsNumber<ArrayType::value_type>) {
        return 0;
    }

    const auto zeros_begin = std::partition(begin, end, [column](const auto n) {
        return IsBitSet(n, column);
    });

    const auto ones_size = std::distance(begin, zeros_begin);
    const auto zeros_size = std::distance(zeros_begin, end);

    if (zeros_size <= ones_size) {
        const auto result = FindTheMissingNumber_Partition_Helper(zeros_begin, end, column + 1);
        return (result << 1) | 0;
    } else {
        const auto result = FindTheMissingNumber_Partition_Helper(begin, zeros_begin,
                                                                  column + 1);
        return (result << 1) | 1;
    }
}

inline auto FindTheMissingNumber_Partition(ArrayType integers) {
    return FindTheMissingNumber_Partition_Helper(integers.begin(), integers.end());
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

    int low = 0;
    int high = values.size() - 1;

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
 * Given a list of n-1 integers and these integers are in the range of 1 to n. There are
 * no duplicates in list. One of the integers is missing in the list. Write an efficient
 * code to find the missing integer.
 *
 * @reference   Find the missing number in a sorted array of limited range
 *              https://www.geeksforgeeks.org/find-missing-number-sorted-array-limited-range/
 *
 * Given a sorted array of size n and given that there are numbers from 1 to n+1 with one
 * missing, the missing number is to be found. It may be assumed that array has distinct
 * elements.
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
    if (values.back() != static_cast<int>(values.size() + 1)) {
        return values.size() + 1;
    }

    int low = 0;
    int high = values.size() - 1;

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


/**
 * @reference   Find the smallest positive number missing from an unsorted array : Hashing Implementation
 *              https://www.geeksforgeeks.org/find-the-smallest-positive-number-missing-from-an-unsorted-array-hashing-implementation/
 * @reference   Find the smallest positive number missing from an unsorted array | Set 3
 *              https://www.geeksforgeeks.org/find-the-smallest-positive-number-missing-from-an-unsorted-array-set-3/
 *
 * Given an unsorted array with both positive and negative elements including 0. The task
 * is to find the smallest positive number missing from the array in O(N) time.
 */
auto FindTheSmallestPositiveMissingNumber_Hash(const ArrayType &elements) {
    std::unordered_set<ArrayType::value_type> counter;

    for (const auto n : elements) {
        if (n > 0) {
            counter.insert(n);
        }
    }

    int result = 1;
    for (; counter.find(result) != counter.cend(); ++result);

    return result;
}


/**
 * @reference   Find the smallest positive number missing from an unsorted array | Set 1
 *              https://www.geeksforgeeks.org/find-the-smallest-positive-number-missing-from-an-unsorted-array/
 * @reference   Find the smallest positive number missing from an unsorted array | Set 2
 *              https://www.geeksforgeeks.org/find-the-smallest-positive-number-missing-from-an-unsorted-array-set-2/
 *
 * You are given an unsorted array with both positive and negative elements. You have to
 * find the smallest positive number missing from the array in O(n) time using constant
 * extra space. You can modify the original array.
 */
int FindTheSmallestPositiveMissingNumber_InPlace(ArrayType elements) {
    const int SIZE = elements.size();
    for (const auto n : elements) {
        for (auto current_value = n;
             n > 0 and n <= SIZE and elements[current_value - 1] != current_value;) {
            std::swap(current_value, elements[current_value - 1]);
        }
    }

    for (int i = 0; i < SIZE; ++i) {
        if (elements[i] != i + 1) {
            return i + 1;
        }
    }

    return SIZE + 1;
}


/**
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 10.3.
 *
 * Given an input file with four billion non-negative integers, provide and algorithm to
 * generate an integer which is not contained in the file. Assume you have 1GB of memory
 * available for this task.
 *
 * @hint    Use std::vector<bool>
 *
 * What if you have only 10MB of memory? Assume that all the values are distinct and we
 * now have no more than one billion non-negative integers.
 *
 * @hint    Divide up the integers into blocks of some size.
 */


/**
 * @reference   Decode XORed Array
 *              https://leetcode.com/problems/decode-xored-array/
 *
 * There is a hidden integer array arr that consists of n non-negative integers.
 * It was encoded into another integer array encoded of length n - 1, such that
 * encoded[i] = arr[i] XOR arr[i + 1]. For example, if arr = [1,0,2,1], then
 * encoded = [1,2,3].
 * You are given the encoded array. You are also given an integer first, that is the
 * first element of arr, i.e. arr[0].
 * Return the original array arr. It can be proved that the answer exists and is unique.
 */

}//namespace


const ArrayType SAMPLE1 = {1, 2, 4, 6, 3, 7, 8};
const ArrayType SAMPLE2 = {1, 2, 4, 5, 6};


THE_BENCHMARK(FindTheMissingNumber_Sum, SAMPLE1);

SIMPLE_TEST(FindTheMissingNumber_Sum, TestSample1, 5, SAMPLE1);
SIMPLE_TEST(FindTheMissingNumber_Sum, TestSample2, 3, SAMPLE2);


THE_BENCHMARK(FindTheMissingNumber_Xor, SAMPLE1);

SIMPLE_TEST(FindTheMissingNumber_Xor, TestSample1, 5, SAMPLE1);
SIMPLE_TEST(FindTheMissingNumber_Xor, TestSample2, 3, SAMPLE2);


THE_BENCHMARK(FindTheMissingNumber_Partition, SAMPLE1);

SIMPLE_TEST(FindTheMissingNumber_Partition, TestSample1, 5, SAMPLE1);
SIMPLE_TEST(FindTheMissingNumber_Partition, TestSample2, 3, SAMPLE2);


const ArrayType SAMPLE3 = {13, 12, 11, 15};
const ArrayType SAMPLE4 = {33, 36, 35, 34};


THE_BENCHMARK(FindTheMissingNumberRange_Xor, SAMPLE1);

SIMPLE_TEST(FindTheMissingNumberRange_Xor, TestSample1, 5, SAMPLE1);
SIMPLE_TEST(FindTheMissingNumberRange_Xor, TestSample2, 3, SAMPLE2);
SIMPLE_TEST(FindTheMissingNumberRange_Xor, TestSample3, 14, SAMPLE3);
SIMPLE_TEST(FindTheMissingNumberRange_Xor, TestSample4, 37, SAMPLE4);


THE_BENCHMARK(FindTheMissingNumber_SortedRange_BinarySearch, SAMPLE2);

SIMPLE_TEST(FindTheMissingNumber_SortedRange_BinarySearch, TestSample2, 3, SAMPLE2);


const ArrayType SAMPLE5 = {2, 3, 4, 5, 6};
const ArrayType SAMPLE6 = {1, 2, 3, 4, 5};


THE_BENCHMARK(FindTheMissingNumber_Sorted_BinarySearch, SAMPLE2);

SIMPLE_TEST(FindTheMissingNumber_Sorted_BinarySearch, TestSample2, 3, SAMPLE2);
SIMPLE_TEST(FindTheMissingNumber_Sorted_BinarySearch, TestBegin, 1, SAMPLE5);
SIMPLE_TEST(FindTheMissingNumber_Sorted_BinarySearch, TestLast,
            SAMPLE6.size() + 1, SAMPLE6);


THE_BENCHMARK(FindTheMissingNumber_Sorted_BinaryLast, SAMPLE2);

SIMPLE_TEST(FindTheMissingNumber_Sorted_BinaryLast, TestSample2, 3, SAMPLE2);
SIMPLE_TEST(FindTheMissingNumber_Sorted_BinaryLast, TestBegin, 1, SAMPLE5);
SIMPLE_TEST(FindTheMissingNumber_Sorted_BinaryLast, TestLast,
            SAMPLE6.size() + 1, SAMPLE6);


const ArrayType SAMPLE7 = {-5, 2, 0, -1, -10, 15};
const ArrayType SAMPLE8 = {1, 1, 1, 0, -1, -2};


THE_BENCHMARK(FindTheSmallestPositiveMissingNumber_Hash, SAMPLE7);

SIMPLE_TEST(FindTheSmallestPositiveMissingNumber_Hash, TestSample6, 6, SAMPLE6);
SIMPLE_TEST(FindTheSmallestPositiveMissingNumber_Hash, TestSample7, 1, SAMPLE7);
SIMPLE_TEST(FindTheSmallestPositiveMissingNumber_Hash, TestSample8, 2, SAMPLE8);


THE_BENCHMARK(FindTheSmallestPositiveMissingNumber_InPlace, SAMPLE7);

SIMPLE_TEST(FindTheSmallestPositiveMissingNumber_InPlace, TestSample6, 6, SAMPLE6);
SIMPLE_TEST(FindTheSmallestPositiveMissingNumber_InPlace, TestSample7, 1, SAMPLE7);
SIMPLE_TEST(FindTheSmallestPositiveMissingNumber_InPlace, TestSample8, 2, SAMPLE8);
