#include "common_header.h"

#include "data_structure/linked_list/middle_of_singly_linked_list.h"
#include "mathematics/numbers/binary/count_total_bits.h"


namespace {

using ArrayType = std::vector<int>;

/** Binary Search
 *
 * @reference   https://www.geeksforgeeks.org/binary-search/
 * @reference   C Program for Binary Search (Recursive and Iterative)
 *              https://www.geeksforgeeks.org/c-program-for-binary-search-recursive-and-iterative/
 * @reference   Linear Search vs Binary Search
 *              https://www.geeksforgeeks.org/linear-search-vs-binary-search/
 * @reference   Binary Search a String
 *              https://www.geeksforgeeks.org/binary-search-a-string/
 * @reference   Complexity Analysis of Binary Search
 *              https://www.geeksforgeeks.org/complexity-analysis-of-binary-search/
 * @reference   The Ubiquitous Binary Search | Set 1
 *              https://www.geeksforgeeks.org/the-ubiquitous-binary-search-set-1/
 * @reference   A Problem in Many Binary Search Implementations
 *              https://www.geeksforgeeks.org/problem-binary-search-implementations/
 * @reference   Binary Search
 *              http://locklessinc.com/articles/binary_search/
 * @reference   Extra, Extra - Read All About It: Nearly All Binary Searches and Mergesorts are Broken
 *              https://ai.googleblog.com/2006/06/extra-extra-read-all-about-it-nearly.html
 * @reference   Why is Binary Search preferred over Ternary Search?
 *              https://www.geeksforgeeks.org/binary-search-preferred-ternary-search/
 * @reference   Binary search in sorted vector of pairs
 *              https://www.geeksforgeeks.org/binary-search-sorted-vector-pairs/
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 7.
 */
auto BinarySearch_Recursive(const ArrayType::const_iterator cbegin,
                            const ArrayType::size_type length, const ArrayType::const_iterator cend,
                            const ArrayType::value_type x) {
    if (length) {
        const auto half = length / 2;
        const auto mid = cbegin + half;

        if (*mid == x) {
            return mid;
        }
        if (*mid > x) {
            return BinarySearch_Recursive(cbegin, half, cend, x);
        }
        return BinarySearch_Recursive(std::next(mid), length - half - 1, cend, x);
    }

    return cend;
}

inline auto
BinarySearch_Recursive(const ArrayType &elements, const ArrayType::value_type x) {
    assert(std::is_sorted(elements.cbegin(), elements.cend()));
    return BinarySearch_Recursive(elements.cbegin(), elements.size(), elements.cend(), x);
}


inline auto
BinarySearch_STL_Lower(const ArrayType &elements, const ArrayType::value_type x) {
    return std::lower_bound(elements.cbegin(), elements.cend(), x);
}


inline auto
BinarySearch_STL_Upper(const ArrayType &elements, const ArrayType::value_type x) {
    const auto iter = std::upper_bound(elements.cbegin(), elements.cend(), x);
    if (iter != elements.cend()) {
        return std::prev(iter);
    }
    return iter;
}


auto BinarySearch_Iterative(const ArrayType &elements, const ArrayType::value_type x) {
    assert(std::is_sorted(elements.cbegin(), elements.cend()));

    auto cbegin = elements.cbegin();
    auto length = elements.size();
    while (length) {
        const auto half = length / 2;
        const auto mid = cbegin + half;

        if (*mid == x) {
            return mid;
        }
        if (*mid > x) {
            length = half;
        } else {
            cbegin = std::next(mid);
            length -= (half + 1);
        }
    }

    return elements.cend();
}


/**
 * @reference   Meta Binary Search | One-Sided Binary Search
 *              https://www.geeksforgeeks.org/meta-binary-search-one-sided-binary-search/
 * @reference   What is meta binary search?
 *              https://www.quora.com/What-is-meta-binary-search
 */
auto BinarySearch_Meta(const ArrayType &elements, const ArrayType::value_type x) {
    assert(std::is_sorted(elements.cbegin(), elements.cend()));
    assert(not elements.empty());

    if (x == elements.front()) {
        return elements.cbegin();
    }

    const auto max_index_bits = CountTotalBits_Log(elements.size() - 1);
    ArrayType::size_type i = 0;
    for (int shift = max_index_bits - 1; shift >= 0; --shift) {
        const auto index_candidate = i + (1 << shift);

        if (index_candidate >= elements.size()) {
            continue;
        }
        if (elements[index_candidate] == x) {
            return elements.cbegin() + index_candidate;
        }
        if (elements[index_candidate] < x) {
            i = index_candidate;
        }
    }

    return elements.cend();
}


/**
 * @reference   Uniform Binary Search
 *              https://www.geeksforgeeks.org/uniform-binary-search/
 */
auto CreateDeltaTable(const ArrayType::size_type size) {
    std::vector<ArrayType::size_type> delta_table(CountTotalBits_Log(size) + 1);

    unsigned power = 1;
    int i = 0;
    do {
        const auto half = power;
        power <<= 1;
        delta_table[i] = (size + half) / power;
    } while (delta_table[i++] != 0);

    return delta_table;
}

template <unsigned size>
inline const auto &GetDeltaTable() {
    static const auto delta_table = CreateDeltaTable(size);
    return delta_table;
}

template <unsigned size>
constexpr auto
BinarySearch_Uniform(const ArrayType &elements, const ArrayType::value_type x) {
    assert(size == elements.size());
    assert(not elements.empty());
    assert(std::is_sorted(elements.cbegin(), elements.cend()));

    const auto &delta_table = GetDeltaTable<size>();
    auto delta = 0;
    for (auto i = delta_table[delta] - 1; delta_table[delta];) {
        if (x == elements[i]) {
            return elements.cbegin() + i;
        }
        if (x < elements[i]) {
            i -= delta_table[++delta];
        } else {
            i += delta_table[++delta];
        }
    }

    return elements.cend();
}

const auto BinarySearch_Uniform5 = BinarySearch_Uniform<5>;
const auto BinarySearch_Uniform1 = BinarySearch_Uniform<1>;


/** Find first and last positions of an element in a sorted array
 *
 * @reference   https://www.geeksforgeeks.org/find-first-and-last-positions-of-an-element-in-a-sorted-array/
 *
 * Given a sorted array with possibly duplicate elements, the task is to find indexes of
 * first and last occurrences of an element x in the given array.
 *
 * @reference   Find the index of first 1 in a sorted array of 0's and 1's
 *              https://www.geeksforgeeks.org/find-index-first-1-sorted-array-0s-1s/
 *
 * @reference   Check for Majority Element in a sorted array
 *              https://www.geeksforgeeks.org/check-for-majority-element-in-a-sorted-array/
 *
 * Write a C function to find if a given integer x appears more than n/2 times in a
 * sorted array of n integers.
 */
auto BinarySearch_First_Recursive(const ArrayType &elements,
                                  const ArrayType::const_iterator cbegin,
                                  const ArrayType::size_type length,
                                  const ArrayType::value_type x) {
    if (length) {
        const auto half = length / 2;
        const auto mid = cbegin + half;

        if (*mid == x and (mid == elements.cbegin() or x > *std::prev(mid))) {
            return mid;
        }
        if (*mid < x) {
            return BinarySearch_First_Recursive(elements, std::next(mid), length - half - 1, x);
        }
        return BinarySearch_First_Recursive(elements, cbegin, half, x);
    }

    return elements.cend();
}

inline auto
BinarySearch_First_Recursive(const ArrayType &elements,
                             const ArrayType::value_type x) {
    assert(std::is_sorted(elements.cbegin(), elements.cend()));
    return BinarySearch_First_Recursive(elements, elements.cbegin(), elements.size(), x);
}


/**
 * @reference   Variants of Binary Search
 *              https://www.geeksforgeeks.org/variants-of-binary-search/
 */
auto BinarySearch_First_Iterative(const ArrayType &elements,
                                  const ArrayType::value_type x) {
    assert(std::is_sorted(elements.cbegin(), elements.cend()));

    auto cbegin = elements.cbegin();
    auto length = elements.size();
    auto output = elements.cend();

    while (length) {
        const auto half = length / 2;
        const auto mid = cbegin + half;

        if (*mid < x) {
            cbegin = std::next(mid);
            length -= (half + 1);
        } else {
            if (*mid == x) {
                output = mid;
            }
            length = half;
        }
    }

    return output;
}


auto BinarySearch_Last_Recursive(const ArrayType &elements,
                                 const ArrayType::const_iterator cbegin,
                                 const ArrayType::size_type length,
                                 const ArrayType::value_type x) {
    if (length) {
        const auto half = length / 2;
        const auto mid = cbegin + half;
        const auto mid_next = std::next(mid);

        if (*mid == x and (mid_next == elements.cend() or x < *mid_next)) {
            return mid;
        }
        if (*mid > x) {
            return BinarySearch_Last_Recursive(elements, cbegin, half, x);
        }
        return BinarySearch_Last_Recursive(elements, mid_next, length - half - 1, x);
    }

    return elements.cend();
}

inline auto
BinarySearch_Last_Recursive(const ArrayType &elements,
                            const ArrayType::value_type x) {
    assert(std::is_sorted(elements.cbegin(), elements.cend()));
    return BinarySearch_Last_Recursive(elements, elements.cbegin(), elements.size(), x);
}


/**
 * @reference   Variants of Binary Search
 *              https://www.geeksforgeeks.org/variants-of-binary-search/
 */
auto BinarSearch_Last_Iterative(const ArrayType &elements,
                                const ArrayType::value_type x) {
    assert(std::is_sorted(elements.cbegin(), elements.cend()));

    auto cbegin = elements.cbegin();
    auto length = elements.size();
    auto output = elements.cend();

    while (length) {
        const auto half = length / 2;
        const auto mid = cbegin + half;

        if (*mid > x) {
            length = half;
        } else {
            if (*mid == x) {
                output = mid;
            }
            cbegin = std::next(mid);
            length -= (half + 1);
        }
    }

    return output;
}


/**
 * @reference   Variants of Binary Search
 *              https://www.geeksforgeeks.org/variants-of-binary-search/
 *
 * Find index of first occurrence of least element greater than key in array
 *
 * @reference   Count smaller elements in sorted array in C++
 *              https://www.geeksforgeeks.org/count-smaller-elements-in-sorted-array-in-cpp/
 *
 * Given a sorted array and a number x, count smaller elements than x in the given array.
 *
 * @reference   Find the number of elements greater than k in a sorted array
 *              https://www.geeksforgeeks.org/find-the-number-of-elements-greater-than-k-in-a-sorted-array/
 *
 * Given a sorted array arr[] of integers and an integer k, the task is to find the count
 * of elements in the array which are greater than k. Note that k may or may not be present
 * in the array.
 *
 * @reference   Count of smaller or equal elements in sorted array
 *              https://www.geeksforgeeks.org/count-smaller-equal-elements-sorted-array/
 *
 * Given an sorted array of size n. Find number of elements which are less than or equal
 * to given element.
 */
auto UpperBound_BinarySearch(const ArrayType &elements, const ArrayType::value_type x) {
    assert(std::is_sorted(elements.cbegin(), elements.cend()));

    auto cbegin = elements.cbegin();
    auto length = elements.size();
    auto output = elements.cend();

    while (length) {
        const auto half = length / 2;
        const auto mid = cbegin + half;

        if (*mid > x) {
            output = mid;
            length = half;
        } else {
            cbegin = std::next(mid);
            length -= (half + 1);
        }
    }

    return output;
}


inline auto
UpperBound_STL(const ArrayType &elements, const ArrayType::value_type x) {
    return std::upper_bound(elements.cbegin(), elements.cend(), x);
}


/**
 * @reference   Search Insert Position
 *              https://leetcode.com/problems/search-insert-position/
 * @reference   Search insert position of K in a sorted array
 *              https://www.geeksforgeeks.org/search-insert-position-of-k-in-a-sorted-array/
 *
 * Given a sorted array of distinct integers and a target value, return the index if the
 * target is found. If not, return the index where it would be if it were inserted in
 * order. You must write an algorithm with O(log n) runtime complexity.
 */
auto SearchInsertPosition(const ArrayType &elements, const ArrayType::value_type x,
                          const int left, const int right) {
    if (left > right) {
        return left;
    }

    const auto mid = (left + right) / 2;

    if (elements[mid] == x) {
        return mid;
    } else if (elements[mid] < x) {
        return SearchInsertPosition(elements, x, mid + 1, right);
    } else {
        return SearchInsertPosition(elements, x, left, mid - 1);
    }
}

inline auto
SearchInsertPosition(const ArrayType &elements, const ArrayType::value_type x) {
    return SearchInsertPosition(elements, x, 0, elements.size() - 1);
}


inline ArrayType::size_type
SearchInsertPosition_STL(const ArrayType &elements, const ArrayType::value_type x) {
    const auto lower = std::lower_bound(elements.cbegin(), elements.cend(), x);
    if (lower == elements.cend()) {
        return elements.size();
    }
    return lower - elements.cbegin();
}


/**
 * @reference   Ceiling in a sorted array
 *              https://www.geeksforgeeks.org/ceiling-in-a-sorted-array/
 *
 * Given a sorted array and a value x, the ceiling of x is the smallest element in array
 * greater than or equal to x, and the floor is the greatest element smaller than or
 * equal to x. Assume that the array is sorted in non-decreasing order. Write efficient
 * functions to find floor and ceiling of x.
 */


/**
 * @reference   Variants of Binary Search
 *              https://www.geeksforgeeks.org/variants-of-binary-search/
 *
 * Find index of last occurrence of greatest element less than key in array.
 */
auto
GreatestLesser_BinarySearch(const ArrayType &elements, const ArrayType::value_type x) {
    assert(std::is_sorted(elements.cbegin(), elements.cend()));

    auto cbegin = elements.cbegin();
    auto length = elements.size();
    auto output = elements.cend();

    while (length) {
        const auto half = length / 2;
        const auto mid = cbegin + half;

        if (*mid < x) {
            output = mid;
            cbegin = std::next(mid);
            length -= (half + 1);
        } else {
            length = half;
        }
    }

    return output;
}


inline auto
GreatestLesser_STL(const ArrayType &elements, const ArrayType::value_type x) {
    const auto iter = std::lower_bound(elements.cbegin(), elements.cend(), x);
    if (iter == elements.cbegin() or iter == elements.cend()) {
        elements.cend();
    }
    return std::prev(iter);
}


/**
 * @reference   Floor in a Sorted Array
 *              https://www.geeksforgeeks.org/floor-in-a-sorted-array/
 *
 * Given a sorted array and a value x, the floor of x is the largest element in array
 * smaller than or equal to x. Write efficient functions to find floor of x.
 */


/**
 * @reference   Finding Floor and Ceil of a Sorted Array using C++ STL
 *              https://www.geeksforgeeks.org/finding-floor-and-ceil-of-a-sorted-array-using-stl/
 *
 * Given a sorted array, the task is to find the floor and ceil of given numbers using
 * STL.
 */


/**
 * @reference   Randomized Binary Search Algorithm
 *              https://www.geeksforgeeks.org/randomized-binary-search-algorithm/
 */
auto BinarySearch_Randomized_Iterative(const ArrayType &elements,
                                       const ArrayType::value_type x) {
    assert(not elements.empty());
    assert(std::is_sorted(elements.cbegin(), elements.cend()));

    long low = 0;
    long high = elements.size() - 1;

    while (low <= high) {
        const auto mid = Random_Number(low, high);
        if (elements[mid] == x) {
            return elements.cbegin() + mid;
        }

        if (elements[mid] < x) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return elements.cend();
}


/** Binary Search on Singly Linked List
 *
 * @reference   https://www.geeksforgeeks.org/binary-search-on-singly-linked-list/
 */
auto BinarySearch_SinglyList(
    const std::forward_list<ArrayType::value_type> &singly_list,
    const ArrayType::value_type x) {
    assert(std::is_sorted(singly_list.cbegin(), singly_list.cend()));

    auto begin = singly_list.cbegin();
    auto end = singly_list.cend();

    while (begin != end) {
        const auto mid = GetMiddle_TwoPointers_STL(begin, end);
        if (mid == singly_list.cend()
            or * mid == x) {
            return mid;
        }

        if (*mid < x) {
            begin = std::next(mid);
        } else {
            end = mid;
        }
    }

    return singly_list.cend();
}

}//namespace


using InitializerType = std::initializer_list<ArrayType::value_type>;

constexpr InitializerType INITIALIZER_EMPTY = {};
constexpr InitializerType INITIALIZER1 = {2, 3, 4, 10, 40};
constexpr InitializerType INITIALIZER_UNDERFLOW = {2};

const ArrayType ARRAY_EMPTY = INITIALIZER_EMPTY;
const ArrayType ARRAY1 = INITIALIZER1;
const ArrayType ARRAY_UNDERFLOW = INITIALIZER_UNDERFLOW;

const std::forward_list<ArrayType::value_type> LIST_EMPTY = INITIALIZER_EMPTY;
const std::forward_list<ArrayType::value_type> LIST1 = INITIALIZER1;
const std::forward_list<ArrayType::value_type> LIST_UNDERFLOW = INITIALIZER_UNDERFLOW;


THE_BENCHMARK(BinarySearch_Recursive, ARRAY1, 10);

SIMPLE_TEST(BinarySearch_Recursive, TestEmpty, ARRAY_EMPTY.cend(), ARRAY_EMPTY, 10);
SIMPLE_TEST(BinarySearch_Recursive, TestBegin, ARRAY1.cbegin(), ARRAY1, ARRAY1.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarySearch_Recursive, TestSample1,
                   ARRAY1, 10);
SIMPLE_TEST(BinarySearch_Recursive, TestLast, std::prev(ARRAY1.cend()),
            ARRAY1, ARRAY1.back());
SIMPLE_TEST(BinarySearch_Recursive, TestNotExist, ARRAY1.cend(), ARRAY1, 999);
SIMPLE_TEST(BinarySearch_Recursive, TestUnderflow, ARRAY_UNDERFLOW.cend(),
            ARRAY_UNDERFLOW, ARRAY_UNDERFLOW.front() - 1);


THE_BENCHMARK(BinarySearch_Iterative, ARRAY1, 10);

SIMPLE_TEST(BinarySearch_Iterative, TestEmpty, ARRAY_EMPTY.cend(), ARRAY_EMPTY, 10);
SIMPLE_TEST(BinarySearch_Iterative, TestBegin, ARRAY1.cbegin(), ARRAY1, ARRAY1.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarySearch_Iterative, TestSample1,
                   ARRAY1, 10);
SIMPLE_TEST(BinarySearch_Iterative, TestLast, std::prev(ARRAY1.cend()),
            ARRAY1, ARRAY1.back());
SIMPLE_TEST(BinarySearch_Iterative, TestNotExist, ARRAY1.cend(), ARRAY1, 999);
SIMPLE_TEST(BinarySearch_Iterative, TestUnderflow, ARRAY_UNDERFLOW.cend(),
            ARRAY_UNDERFLOW, ARRAY_UNDERFLOW.front() - 1);


THE_BENCHMARK(BinarySearch_Meta, ARRAY1, 10);

SIMPLE_TEST(BinarySearch_Meta, TestBegin, ARRAY1.cbegin(), ARRAY1, ARRAY1.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarySearch_Meta, TestSample1, ARRAY1, 10);
SIMPLE_TEST(BinarySearch_Meta, TestLast, std::prev(ARRAY1.cend()),
            ARRAY1, ARRAY1.back());
SIMPLE_TEST(BinarySearch_Meta, TestNotExist, ARRAY1.cend(), ARRAY1, 999);
SIMPLE_TEST(BinarySearch_Meta, TestUnderflow, ARRAY_UNDERFLOW.cend(),
            ARRAY_UNDERFLOW, ARRAY_UNDERFLOW.front() - 1);


THE_BENCHMARK(BinarySearch_Uniform5, ARRAY1, 10);

SIMPLE_TEST(BinarySearch_Uniform5, TestBegin, ARRAY1.cbegin(), ARRAY1, ARRAY1.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarySearch_Uniform5, TestSample1,
                   ARRAY1, 10);
SIMPLE_TEST(BinarySearch_Uniform5, TestLast, std::prev(ARRAY1.cend()),
            ARRAY1, ARRAY1.back());
SIMPLE_TEST(BinarySearch_Uniform5, TestNotExist, ARRAY1.cend(), ARRAY1, 999);
SIMPLE_TEST(BinarySearch_Uniform1, TestUnderflow, ARRAY_UNDERFLOW.cend(),
            ARRAY_UNDERFLOW, ARRAY_UNDERFLOW.front() - 1);


const ArrayType VALUES3 = {2, 3, 3, 5, 5, 5, 6, 6};


THE_BENCHMARK(BinarySearch_First_Iterative, ARRAY1, 10);

SIMPLE_TEST(BinarySearch_First_Iterative, TestEmpty, ARRAY_EMPTY.cend(),
            ARRAY_EMPTY, 10);
SIMPLE_TEST(BinarySearch_First_Iterative, TestBegin2, ARRAY1.cbegin(),
            ARRAY1, ARRAY1.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarySearch_First_Iterative, TestSample1,
                   ARRAY1, 10);
SIMPLE_TEST(BinarySearch_First_Iterative, TestLast, std::prev(ARRAY1.cend()),
            ARRAY1, ARRAY1.back());
SIMPLE_TEST(BinarySearch_First_Iterative, TestNotExist, ARRAY1.cend(), ARRAY1, 999);
SIMPLE_TEST(BinarySearch_First_Iterative, TestBegin3, VALUES3.cbegin(),
            VALUES3, VALUES3.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarySearch_First_Iterative, TestSample2,
                   VALUES3, 5);
SIMPLE_TEST(BinarySearch_First_Iterative, TestUnderflow, ARRAY_UNDERFLOW.cend(),
            ARRAY_UNDERFLOW, ARRAY_UNDERFLOW.front() - 1);


THE_BENCHMARK(BinarySearch_First_Recursive, ARRAY1, 10);

SIMPLE_TEST(BinarySearch_First_Recursive, TestEmpty, ARRAY_EMPTY.cend(),
            ARRAY_EMPTY, 10);
SIMPLE_TEST(BinarySearch_First_Recursive, TestBegin2, ARRAY1.cbegin(),
            ARRAY1, ARRAY1.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarySearch_First_Recursive, TestSample1,
                   ARRAY1, 10);
SIMPLE_TEST(BinarySearch_First_Recursive, TestLast, std::prev(ARRAY1.cend()),
            ARRAY1, ARRAY1.back());
SIMPLE_TEST(BinarySearch_First_Recursive, TestNotExist, ARRAY1.cend(), ARRAY1, 999);
SIMPLE_TEST(BinarySearch_First_Recursive, TestBegin3, VALUES3.cbegin(),
            VALUES3, VALUES3.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarySearch_First_Recursive, TestSample2,
                   VALUES3, 5);
SIMPLE_TEST(BinarySearch_First_Recursive, TestUnderflow, ARRAY_UNDERFLOW.cend(),
            ARRAY_UNDERFLOW, ARRAY_UNDERFLOW.front() - 1);


THE_BENCHMARK(BinarSearch_Last_Iterative, ARRAY1, 10);

SIMPLE_TEST(BinarSearch_Last_Iterative, TestEmpty, ARRAY_EMPTY.cend(), ARRAY_EMPTY, 10);
SIMPLE_TEST(BinarSearch_Last_Iterative, TestBegin2, ARRAY1.cbegin(),
            ARRAY1, ARRAY1.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarSearch_Last_Iterative, TestSample1,
                   ARRAY1, 10);
SIMPLE_TEST(BinarSearch_Last_Iterative, TestLast, std::prev(ARRAY1.cend()),
            ARRAY1, ARRAY1.back());
SIMPLE_TEST(BinarSearch_Last_Iterative, TestNotExist, ARRAY1.cend(), ARRAY1, 999);
SIMPLE_TEST(BinarSearch_Last_Iterative, TestLast3, std::prev(VALUES3.cend()),
            VALUES3, VALUES3.back());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Upper, BinarSearch_Last_Iterative, TestSample2,
                   VALUES3, 5);
SIMPLE_TEST(BinarSearch_Last_Iterative, TestUnderflow, ARRAY_UNDERFLOW.cend(),
            ARRAY_UNDERFLOW, ARRAY_UNDERFLOW.front() - 1);


THE_BENCHMARK(BinarySearch_Last_Recursive, ARRAY1, 10);

SIMPLE_TEST(BinarySearch_Last_Recursive, TestEmpty, ARRAY_EMPTY.cend(),
            ARRAY_EMPTY, 10);
SIMPLE_TEST(BinarySearch_Last_Recursive, TestBegin2, ARRAY1.cbegin(),
            ARRAY1, ARRAY1.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarySearch_Last_Recursive, TestSample1,
                   ARRAY1, 10);
SIMPLE_TEST(BinarySearch_Last_Recursive, TestLast, std::prev(ARRAY1.cend()),
            ARRAY1, ARRAY1.back());
SIMPLE_TEST(BinarySearch_Last_Recursive, TestNotExist, ARRAY1.cend(), ARRAY1, 999);
SIMPLE_TEST(BinarySearch_Last_Recursive, TestLast3, std::prev(VALUES3.cend()),
            VALUES3, VALUES3.back());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Upper, BinarySearch_Last_Recursive, TestSample2,
                   VALUES3, 5);
SIMPLE_TEST(BinarySearch_Last_Recursive, TestUnderflow, ARRAY_UNDERFLOW.cend(),
            ARRAY_UNDERFLOW, ARRAY_UNDERFLOW.front() - 1);


THE_BENCHMARK(UpperBound_BinarySearch, ARRAY1, 10);

SIMPLE_TEST(UpperBound_BinarySearch, TestEmpty, ARRAY_EMPTY.cend(), ARRAY_EMPTY, 10);
SIMPLE_TEST(UpperBound_BinarySearch, TestBegin2, ARRAY1.cbegin(),
            ARRAY1, ARRAY1.front() - 1);
MUTUAL_SIMPLE_TEST(UpperBound_STL, UpperBound_BinarySearch, TestSample1, ARRAY1, 10);
SIMPLE_TEST(UpperBound_BinarySearch, TestLast, std::prev(ARRAY1.cend()),
            ARRAY1, ARRAY1.back() - 1);
SIMPLE_TEST(UpperBound_BinarySearch, TestNotExist, ARRAY1.cend(), ARRAY1, 999);
SIMPLE_TEST(UpperBound_BinarySearch, TestLast3, VALUES3.cend(),
            VALUES3, VALUES3.back());
MUTUAL_SIMPLE_TEST(UpperBound_STL, UpperBound_BinarySearch, TestSample2, VALUES3, 5);
SIMPLE_TEST(UpperBound_BinarySearch, TestUnderflow, ARRAY_UNDERFLOW.cbegin(),
            ARRAY_UNDERFLOW, ARRAY_UNDERFLOW.front() - 1);


const ArrayType SAMPLE4 = {1, 3, 5, 6};


THE_BENCHMARK(SearchInsertPosition, ARRAY1, 10);

SIMPLE_TEST(SearchInsertPosition, TestEmpty, 0, ARRAY_EMPTY, 10);
SIMPLE_TEST(SearchInsertPosition, TestBegin2, 0, ARRAY1, ARRAY1.front() - 1);
SIMPLE_TEST(SearchInsertPosition, TestLast, ARRAY1.size() - 1,
            ARRAY1, ARRAY1.back() - 1);
SIMPLE_TEST(SearchInsertPosition, TestNotExist, ARRAY1.size(), ARRAY1, 999);
SIMPLE_TEST(SearchInsertPosition, TestUnderflow, 0,
            ARRAY_UNDERFLOW, ARRAY_UNDERFLOW.front() - 1);
SIMPLE_TEST(SearchInsertPosition, TestSample4, 2, SAMPLE4, 5);
SIMPLE_TEST(SearchInsertPosition, TestSample5, 1, SAMPLE4, 2);
SIMPLE_TEST(SearchInsertPosition, TestSample6, 4, SAMPLE4, 7);
SIMPLE_TEST(SearchInsertPosition, TestSample7, 0, SAMPLE4, 0);


THE_BENCHMARK(SearchInsertPosition_STL, ARRAY1, 10);

SIMPLE_TEST(SearchInsertPosition_STL, TestEmpty, 0, ARRAY_EMPTY, 10);
SIMPLE_TEST(SearchInsertPosition_STL, TestBegin2, 0, ARRAY1, ARRAY1.front() - 1);
SIMPLE_TEST(SearchInsertPosition_STL, TestLast, ARRAY1.size() - 1,
            ARRAY1, ARRAY1.back() - 1);
SIMPLE_TEST(SearchInsertPosition_STL, TestNotExist, ARRAY1.size(), ARRAY1, 999);
SIMPLE_TEST(SearchInsertPosition_STL, TestUnderflow, 0,
            ARRAY_UNDERFLOW, ARRAY_UNDERFLOW.front() - 1);
SIMPLE_TEST(SearchInsertPosition_STL, TestSample4, 2, SAMPLE4, 5);
SIMPLE_TEST(SearchInsertPosition_STL, TestSample5, 1, SAMPLE4, 2);
SIMPLE_TEST(SearchInsertPosition_STL, TestSample6, 4, SAMPLE4, 7);
SIMPLE_TEST(SearchInsertPosition_STL, TestSample7, 0, SAMPLE4, 0);


THE_BENCHMARK(GreatestLesser_BinarySearch, ARRAY1, 10);

SIMPLE_TEST(GreatestLesser_BinarySearch, TestEmpty, ARRAY_EMPTY.cend(),
            ARRAY_EMPTY, 10);
SIMPLE_TEST(GreatestLesser_BinarySearch, TestBegin2, ARRAY1.cbegin(),
            ARRAY1, ARRAY1.front() + 1);
MUTUAL_SIMPLE_TEST(GreatestLesser_STL, GreatestLesser_BinarySearch, TestSample1,
                   ARRAY1, 10);
SIMPLE_TEST(GreatestLesser_BinarySearch, TestLast, std::prev(ARRAY1.cend()),
            ARRAY1, ARRAY1.back() + 1);
SIMPLE_TEST(GreatestLesser_BinarySearch, TestNotExist, ARRAY1.cend(), ARRAY1, 0);
SIMPLE_TEST(GreatestLesser_BinarySearch, TestLast3, std::prev(VALUES3.cend()),
            VALUES3, ARRAY1.back() + 1);
MUTUAL_SIMPLE_TEST(GreatestLesser_STL, GreatestLesser_BinarySearch, TestSample2,
                   VALUES3, 5);
SIMPLE_TEST(GreatestLesser_BinarySearch, TestUnderflow, ARRAY_UNDERFLOW.cend(),
            ARRAY_UNDERFLOW, ARRAY_UNDERFLOW.front() - 1);


THE_BENCHMARK(BinarySearch_Randomized_Iterative, ARRAY1, 10);

SIMPLE_TEST(BinarySearch_Randomized_Iterative, TestBegin, ARRAY1.cbegin(),
            ARRAY1, ARRAY1.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarySearch_Randomized_Iterative,
                   TestSample1, ARRAY1, 10);
SIMPLE_TEST(BinarySearch_Randomized_Iterative, TestLast, std::prev(ARRAY1.cend()),
            ARRAY1, ARRAY1.back());
SIMPLE_TEST(BinarySearch_Randomized_Iterative, TestNotExist, ARRAY1.cend(),
            ARRAY1, 999);
SIMPLE_TEST(BinarySearch_Randomized_Iterative, TestUnderflow, ARRAY_UNDERFLOW.cend(),
            ARRAY_UNDERFLOW, ARRAY_UNDERFLOW.front() - 1);


THE_BENCHMARK(BinarySearch_SinglyList, LIST1, 10);

SIMPLE_TEST(BinarySearch_SinglyList, TestEmpty, LIST_EMPTY.cend(), LIST_EMPTY, 10);
SIMPLE_TEST(BinarySearch_SinglyList, TestBegin, LIST1.cbegin(), LIST1, LIST1.front());
SIMPLE_TEST(BinarySearch_SinglyList, TestLast,
            std::next(LIST1.cbegin(), ARRAY1.size() - 1), LIST1, ARRAY1.back());
SIMPLE_TEST(BinarySearch_SinglyList, TestNotExist, LIST1.cend(), LIST1, 999);
SIMPLE_TEST(BinarySearch_SinglyList, TestUnderflow, LIST_UNDERFLOW.cend(),
            LIST_UNDERFLOW, LIST_UNDERFLOW.front() - 1);
