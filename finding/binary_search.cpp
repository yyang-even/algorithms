#include "common_header.h"

#include "data_structure/linked_list/singly_list/middle_of_singly_linked_list.h"
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
 * @reference   Binary Search
 *              https://leetcode.com/problems/binary-search/
 */
auto BinarySearch_Recursive(const ArrayType::const_iterator cbegin,
                            const ArrayType::size_type length,
                            const ArrayType::const_iterator cend,
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

inline auto BinarySearch_Recursive(const ArrayType &elements, const ArrayType::value_type x) {
    assert(std::is_sorted(elements.cbegin(), elements.cend()));
    return BinarySearch_Recursive(elements.cbegin(), elements.size(), elements.cend(), x);
}


inline auto BinarySearch_STL_Lower(const ArrayType &elements, const ArrayType::value_type x) {
    return std::lower_bound(elements.cbegin(), elements.cend(), x);
}


inline auto BinarySearch_STL_Upper(const ArrayType &elements, const ArrayType::value_type x) {
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

template<unsigned size>
inline const auto &GetDeltaTable() {
    static const auto delta_table = CreateDeltaTable(size);
    return delta_table;
}

template<unsigned size>
constexpr auto BinarySearch_Uniform(const ArrayType &elements, const ArrayType::value_type x) {
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


/**
 * @reference   Find the index of first 1 in a sorted array of 0's and 1's
 *              https://www.geeksforgeeks.org/find-index-first-1-sorted-array-0s-1s/
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

inline auto BinarySearch_First_Recursive(const ArrayType &elements,
                                         const ArrayType::value_type x) {
    assert(std::is_sorted(elements.cbegin(), elements.cend()));
    return BinarySearch_First_Recursive(elements, elements.cbegin(), elements.size(), x);
}


/** Find first and last positions of an element in a sorted array
 *
 * @reference   https://www.geeksforgeeks.org/find-first-and-last-positions-of-an-element-in-a-sorted-array/
 *
 * Given a sorted array with possibly duplicate elements, the task is to find indexes of first and last
 * occurrences of an element x in the given array.
 *
 * @reference   Find First and Last Position of Element in Sorted Array
 *              https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
 *
 * Given an array of integers nums sorted in non-decreasing order, find the starting and ending position
 * of a given target value.
 * If target is not found in the array, return [-1, -1].
 * You must write an algorithm with O(log n) runtime complexity.
 */
auto EqualRange(const ArrayType &nums, const int x) {
    if (nums.empty()) {
        return std::pair(-1, -1);
    }

    int left = 0;
    int right = nums.size() - 1;

    while (left < right) {
        const auto mid = (left + right) / 2;
        if (nums[mid] < x) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    if (nums[left] != x) {
        return std::pair(-1, -1);
    }
    const auto result_left = left;

    right = nums.size() - 1;
    while (left < right) {
        const auto mid = (left + right) / 2 + 1;
        if (nums[mid] > x) {
            right = mid - 1;
        } else {
            left = mid;
        }
    }

    return std::pair(result_left, right);
}


/**
 * @reference   Variants of Binary Search
 *              https://www.geeksforgeeks.org/variants-of-binary-search/
 */
auto BinarySearch_First_Iterative(const ArrayType &elements, const ArrayType::value_type x) {
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

inline auto BinarySearch_Last_Recursive(const ArrayType &elements,
                                        const ArrayType::value_type x) {
    assert(std::is_sorted(elements.cbegin(), elements.cend()));
    return BinarySearch_Last_Recursive(elements, elements.cbegin(), elements.size(), x);
}


/**
 * @reference   Variants of Binary Search
 *              https://www.geeksforgeeks.org/variants-of-binary-search/
 */
auto BinarSearch_Last_Iterative(const ArrayType &elements, const ArrayType::value_type x) {
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
 * Given a sorted array arr[] of integers and an integer k, the task is to find the count of elements in
 * the array which are greater than k. Note that k may or may not be present in the array.
 *
 * @reference   Count of smaller or equal elements in sorted array
 *              https://www.geeksforgeeks.org/count-smaller-equal-elements-sorted-array/
 *
 * Given an sorted array of size n. Find number of elements which are less than or equal to given
 * element.
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


inline auto UpperBound_STL(const ArrayType &elements, const ArrayType::value_type x) {
    return std::upper_bound(elements.cbegin(), elements.cend(), x);
}


/**
 * @reference   Find Smallest Letter Greater Than Target
 *              https://leetcode.com/problems/find-smallest-letter-greater-than-target/
 *
 * Given a characters array letters that is sorted in non-decreasing order and a character target,
 * return the smallest character in the array that is larger than target.
 * Note that the letters wrap around.
 *  For example, if target == 'z' and letters == ['a', 'b'], the answer is 'a'.
 */
constexpr auto NextGreaterChar(const std::string_view letters, char x) {
    bool seen[26] = {};
    for (const auto c : letters) {
        seen[c - 'a'] = true;
    }

    while (true) {
        if (x == 'z') {
            x = 'a';
        } else {
            ++x;
        }

        if (seen[x - 'a']) {
            return x;
        }
    }
}


/**
 * @reference   Search Insert Position
 *              https://leetcode.com/problems/search-insert-position/
 * @reference   Search insert position of K in a sorted array
 *              https://www.geeksforgeeks.org/search-insert-position-of-k-in-a-sorted-array/
 *
 * Given a sorted array of distinct integers and a target value, return the index if the target is
 * found. If not, return the index where it would be if it were inserted in order. You must write an
 * algorithm with O(log n) runtime complexity.
 */
auto SearchInsertPosition(const ArrayType &elements,
                          const ArrayType::value_type x,
                          const int left,
                          const int right) {
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

inline auto SearchInsertPosition(const ArrayType &elements, const ArrayType::value_type x) {
    return SearchInsertPosition(elements, x, 0, elements.size() - 1);
}


inline ArrayType::size_type SearchInsertPosition_STL(const ArrayType &elements,
                                                     const ArrayType::value_type x) {
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
 * Given a sorted array and a value x, the ceiling of x is the smallest element in array greater than or
 * equal to x, and the floor is the greatest element smaller than or equal to x. Assume that the array
 * is sorted in non-decreasing order. Write efficient functions to find floor and ceiling of x.
 */


/**
 * @reference   Variants of Binary Search
 *              https://www.geeksforgeeks.org/variants-of-binary-search/
 *
 * Find index of last occurrence of greatest element less than key in array.
 */
auto GreatestLesser_BinarySearch(const ArrayType &elements, const ArrayType::value_type x) {
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


inline auto GreatestLesser_STL(const ArrayType &elements, const ArrayType::value_type x) {
    const auto iter = std::lower_bound(elements.cbegin(), elements.cend(), x);
    if (iter == elements.cbegin() or iter == elements.cend()) {
        return elements.cend();
    }
    return std::prev(iter);
}


/**
 * @reference   Floor in a Sorted Array
 *              https://www.geeksforgeeks.org/floor-in-a-sorted-array/
 *
 * Given a sorted array and a value x, the floor of x is the largest element in array smaller than or
 * equal to x. Write efficient functions to find floor of x.
 */


/**
 * @reference   Finding Floor and Ceil of a Sorted Array using C++ STL
 *              https://www.geeksforgeeks.org/finding-floor-and-ceil-of-a-sorted-array-using-stl/
 *
 * Given a sorted array, the task is to find the floor and ceil of given numbers using STL.
 */


/**
 * @reference   Randomized Binary Search Algorithm
 *              https://www.geeksforgeeks.org/randomized-binary-search-algorithm/
 */
auto BinarySearch_Randomized_Iterative(const ArrayType &elements, const ArrayType::value_type x) {
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
auto BinarySearch_SinglyList(const std::forward_list<ArrayType::value_type> &singly_list,
                             const ArrayType::value_type x) {
    assert(std::is_sorted(singly_list.cbegin(), singly_list.cend()));

    auto begin = singly_list.cbegin();
    auto end = singly_list.cend();

    while (begin != end) {
        const auto mid = GetMiddle_TwoPointers_STL(begin, end);
        if (mid == singly_list.cend() or *mid == x) {
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


/**
 * @reference   First Bad Version
 *              https://leetcode.com/problems/first-bad-version/
 *
 * You are a product manager and currently leading a team to develop a new product. Unfortunately, the
 * latest version of your product fails the quality check. Since each version is developed based on the
 * previous version, all the versions after a bad version are also bad.
 * Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes
 * all the following ones to be bad.
 * You are given an API bool isBadVersion(version) which returns whether version is bad. Implement a
 * function to find the first bad version. You should minimize the number of calls to the API.
 */


/**
 * @reference   Guess Number Higher or Lower
 *              https://leetcode.com/problems/guess-number-higher-or-lower/
 *
 * We are playing the Guess Game.
 * The game is as follows: I pick a number from 1 to n. You have to guess which number I picked.  Every
 * time you guess wrong, I will tell you whether the number I picked is higher or lower than your guess.
 * You call a pre-defined API int guess(int num), which returns 3 possible results:
 *  -1: The number I picked is lower than your guess (i.e. pick < num).
 *  1: The number I picked is higher than your guess (i.e. pick > num).
 *  0: The number I picked is equal to your guess (i.e. pick == num).
 * Return the number that I picked.
 */


/**
 * @reference   Guess Number Higher or Lower II
 *              https://leetcode.com/problems/guess-number-higher-or-lower-ii/
 *
 * We are playing the Guessing Game. The game will work as follows:
 *  I pick a number between 1 and n.
 *  You guess a number.
 *  If you guess the right number, you win the game.
 *  If you guess the wrong number, then I will tell you whether the number I picked is higher or lower,
 *      and you will continue guessing.
 *  Every time you guess a wrong number x, you will pay x dollars. If you run out of money, you lose the
 *      game.
 * Given a particular n, return the minimum amount of money you need to guarantee a win regardless of
 * what number I pick.
 */
auto GuessNumber_Memo(const int left, const int right, std::vector<std::vector<int>> &memo) {
    if (left >= right) {
        return 0;
    }
    if (right - left == 1) {
        return left;
    }
    if (memo[left][right] != 0) {
        return memo[left][right];
    }

    int min = INT_MAX;
    for (auto i = left; i <= right; ++i) {
        const auto cost = i + std::max(GuessNumber_Memo(left, i - 1, memo),
                                       GuessNumber_Memo(i + 1, right, memo));
        min = std::min(min, cost);
    }

    memo[left][right] = min;
    return min;
}

inline auto GuessNumber_Memo(const int n) {
    if (n <= 1) {
        return 0;
    }

    std::vector memo(n + 1, std::vector(n + 1, 0));
    return GuessNumber_Memo(1, n, memo);
}


constexpr auto GuessNumber_Dp(const int n) {
    if (n <= 1) {
        return 0;
    }

    int dp[n + 1][n + 1] = {};
    for (int i = 1; i < n; ++i) {
        dp[i][i + 1] = i;
    }

    for (int length = 3; length <= n; ++length) {
        for (int left = 1; left <= n - length + 1; ++left) {
            int cost = INT_MAX;
            const int right = left + length - 1;
            for (int i = left; i <= right; ++i) {
                cost = std::min(cost, i + std::max(dp[left][i - 1], dp[i + 1][right]));
            }
            dp[left][right] = cost;
        }
    }

    return dp[1][n];
}


/**
 * @reference   Maximum Value at a Given Index in a Bounded Array
 *              https://leetcode.com/problems/maximum-value-at-a-given-index-in-a-bounded-array/
 *
 * You are given three positive integers: n, index, and maxSum. You want to construct an array nums
 * (0-indexed) that satisfies the following conditions:
 *  nums.length == n
 *  nums[i] is a positive integer where 0 <= i < n.
 *  abs(nums[i] - nums[i+1]) <= 1 where 0 <= i < n-1.
 *  The sum of all the elements of nums does not exceed maxSum.
 *  nums[index] is maximized.
 * Return nums[index] of the constructed array.
 * Note that abs(x) equals x if x >= 0, and -x otherwise.
 */
constexpr auto getSum(const long index, const long value, const long n) {
    long result = 0;

    // On the left
    if (value > index) {
        result += (value + value - index) * (index + 1) / 2;
    } else {
        result += (value + 1) * value / 2 + index - value + 1;
    };

    // On the right
    if (value >= n - index) {
        result += (value + value - n + 1 + index) * (n - index) / 2;
    } else {
        result += (value + 1) * value / 2 + n - index - value;
    }

    return result - value;
}

constexpr auto MaxValueAt(const int n, const int index, const long maxSum) {
    int left = 1;
    int right = maxSum;
    while (left < right) {
        const auto mid = (left + right + 1) / 2;
        if (getSum(index, mid, n) <= maxSum) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }

    return left;
}

} //namespace


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
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarySearch_Recursive, TestSample1, ARRAY1, 10);
SIMPLE_TEST(BinarySearch_Recursive, TestLast, std::prev(ARRAY1.cend()), ARRAY1, ARRAY1.back());
SIMPLE_TEST(BinarySearch_Recursive, TestNotExist, ARRAY1.cend(), ARRAY1, 999);
SIMPLE_TEST(BinarySearch_Recursive,
            TestUnderflow,
            ARRAY_UNDERFLOW.cend(),
            ARRAY_UNDERFLOW,
            ARRAY_UNDERFLOW.front() - 1);


THE_BENCHMARK(BinarySearch_Iterative, ARRAY1, 10);

SIMPLE_TEST(BinarySearch_Iterative, TestEmpty, ARRAY_EMPTY.cend(), ARRAY_EMPTY, 10);
SIMPLE_TEST(BinarySearch_Iterative, TestBegin, ARRAY1.cbegin(), ARRAY1, ARRAY1.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarySearch_Iterative, TestSample1, ARRAY1, 10);
SIMPLE_TEST(BinarySearch_Iterative, TestLast, std::prev(ARRAY1.cend()), ARRAY1, ARRAY1.back());
SIMPLE_TEST(BinarySearch_Iterative, TestNotExist, ARRAY1.cend(), ARRAY1, 999);
SIMPLE_TEST(BinarySearch_Iterative,
            TestUnderflow,
            ARRAY_UNDERFLOW.cend(),
            ARRAY_UNDERFLOW,
            ARRAY_UNDERFLOW.front() - 1);


THE_BENCHMARK(BinarySearch_Meta, ARRAY1, 10);

SIMPLE_TEST(BinarySearch_Meta, TestBegin, ARRAY1.cbegin(), ARRAY1, ARRAY1.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarySearch_Meta, TestSample1, ARRAY1, 10);
SIMPLE_TEST(BinarySearch_Meta, TestLast, std::prev(ARRAY1.cend()), ARRAY1, ARRAY1.back());
SIMPLE_TEST(BinarySearch_Meta, TestNotExist, ARRAY1.cend(), ARRAY1, 999);
SIMPLE_TEST(BinarySearch_Meta,
            TestUnderflow,
            ARRAY_UNDERFLOW.cend(),
            ARRAY_UNDERFLOW,
            ARRAY_UNDERFLOW.front() - 1);


THE_BENCHMARK(BinarySearch_Uniform5, ARRAY1, 10);

SIMPLE_TEST(BinarySearch_Uniform5, TestBegin, ARRAY1.cbegin(), ARRAY1, ARRAY1.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarySearch_Uniform5, TestSample1, ARRAY1, 10);
SIMPLE_TEST(BinarySearch_Uniform5, TestLast, std::prev(ARRAY1.cend()), ARRAY1, ARRAY1.back());
SIMPLE_TEST(BinarySearch_Uniform5, TestNotExist, ARRAY1.cend(), ARRAY1, 999);
SIMPLE_TEST(BinarySearch_Uniform1,
            TestUnderflow,
            ARRAY_UNDERFLOW.cend(),
            ARRAY_UNDERFLOW,
            ARRAY_UNDERFLOW.front() - 1);


const ArrayType VALUES3 = {2, 3, 3, 5, 5, 5, 6, 6};


THE_BENCHMARK(BinarySearch_First_Iterative, ARRAY1, 10);

SIMPLE_TEST(BinarySearch_First_Iterative, TestEmpty, ARRAY_EMPTY.cend(), ARRAY_EMPTY, 10);
SIMPLE_TEST(BinarySearch_First_Iterative, TestBegin2, ARRAY1.cbegin(), ARRAY1, ARRAY1.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarySearch_First_Iterative, TestSample1, ARRAY1, 10);
SIMPLE_TEST(
    BinarySearch_First_Iterative, TestLast, std::prev(ARRAY1.cend()), ARRAY1, ARRAY1.back());
SIMPLE_TEST(BinarySearch_First_Iterative, TestNotExist, ARRAY1.cend(), ARRAY1, 999);
SIMPLE_TEST(BinarySearch_First_Iterative, TestBegin3, VALUES3.cbegin(), VALUES3, VALUES3.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarySearch_First_Iterative, TestSample2, VALUES3, 5);
SIMPLE_TEST(BinarySearch_First_Iterative,
            TestUnderflow,
            ARRAY_UNDERFLOW.cend(),
            ARRAY_UNDERFLOW,
            ARRAY_UNDERFLOW.front() - 1);


THE_BENCHMARK(BinarySearch_First_Recursive, ARRAY1, 10);

SIMPLE_TEST(BinarySearch_First_Recursive, TestEmpty, ARRAY_EMPTY.cend(), ARRAY_EMPTY, 10);
SIMPLE_TEST(BinarySearch_First_Recursive, TestBegin2, ARRAY1.cbegin(), ARRAY1, ARRAY1.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarySearch_First_Recursive, TestSample1, ARRAY1, 10);
SIMPLE_TEST(
    BinarySearch_First_Recursive, TestLast, std::prev(ARRAY1.cend()), ARRAY1, ARRAY1.back());
SIMPLE_TEST(BinarySearch_First_Recursive, TestNotExist, ARRAY1.cend(), ARRAY1, 999);
SIMPLE_TEST(BinarySearch_First_Recursive, TestBegin3, VALUES3.cbegin(), VALUES3, VALUES3.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarySearch_First_Recursive, TestSample2, VALUES3, 5);
SIMPLE_TEST(BinarySearch_First_Recursive,
            TestUnderflow,
            ARRAY_UNDERFLOW.cend(),
            ARRAY_UNDERFLOW,
            ARRAY_UNDERFLOW.front() - 1);


THE_BENCHMARK(BinarSearch_Last_Iterative, ARRAY1, 10);

SIMPLE_TEST(BinarSearch_Last_Iterative, TestEmpty, ARRAY_EMPTY.cend(), ARRAY_EMPTY, 10);
SIMPLE_TEST(BinarSearch_Last_Iterative, TestBegin2, ARRAY1.cbegin(), ARRAY1, ARRAY1.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarSearch_Last_Iterative, TestSample1, ARRAY1, 10);
SIMPLE_TEST(
    BinarSearch_Last_Iterative, TestLast, std::prev(ARRAY1.cend()), ARRAY1, ARRAY1.back());
SIMPLE_TEST(BinarSearch_Last_Iterative, TestNotExist, ARRAY1.cend(), ARRAY1, 999);
SIMPLE_TEST(
    BinarSearch_Last_Iterative, TestLast3, std::prev(VALUES3.cend()), VALUES3, VALUES3.back());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Upper, BinarSearch_Last_Iterative, TestSample2, VALUES3, 5);
SIMPLE_TEST(BinarSearch_Last_Iterative,
            TestUnderflow,
            ARRAY_UNDERFLOW.cend(),
            ARRAY_UNDERFLOW,
            ARRAY_UNDERFLOW.front() - 1);


THE_BENCHMARK(BinarySearch_Last_Recursive, ARRAY1, 10);

SIMPLE_TEST(BinarySearch_Last_Recursive, TestEmpty, ARRAY_EMPTY.cend(), ARRAY_EMPTY, 10);
SIMPLE_TEST(BinarySearch_Last_Recursive, TestBegin2, ARRAY1.cbegin(), ARRAY1, ARRAY1.front());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Lower, BinarySearch_Last_Recursive, TestSample1, ARRAY1, 10);
SIMPLE_TEST(
    BinarySearch_Last_Recursive, TestLast, std::prev(ARRAY1.cend()), ARRAY1, ARRAY1.back());
SIMPLE_TEST(BinarySearch_Last_Recursive, TestNotExist, ARRAY1.cend(), ARRAY1, 999);
SIMPLE_TEST(
    BinarySearch_Last_Recursive, TestLast3, std::prev(VALUES3.cend()), VALUES3, VALUES3.back());
MUTUAL_SIMPLE_TEST(BinarySearch_STL_Upper, BinarySearch_Last_Recursive, TestSample2, VALUES3, 5);
SIMPLE_TEST(BinarySearch_Last_Recursive,
            TestUnderflow,
            ARRAY_UNDERFLOW.cend(),
            ARRAY_UNDERFLOW,
            ARRAY_UNDERFLOW.front() - 1);


THE_BENCHMARK(UpperBound_BinarySearch, ARRAY1, 10);

SIMPLE_TEST(UpperBound_BinarySearch, TestEmpty, ARRAY_EMPTY.cend(), ARRAY_EMPTY, 10);
SIMPLE_TEST(UpperBound_BinarySearch, TestBegin2, ARRAY1.cbegin(), ARRAY1, ARRAY1.front() - 1);
MUTUAL_SIMPLE_TEST(UpperBound_STL, UpperBound_BinarySearch, TestSample1, ARRAY1, 10);
SIMPLE_TEST(
    UpperBound_BinarySearch, TestLast, std::prev(ARRAY1.cend()), ARRAY1, ARRAY1.back() - 1);
SIMPLE_TEST(UpperBound_BinarySearch, TestNotExist, ARRAY1.cend(), ARRAY1, 999);
SIMPLE_TEST(UpperBound_BinarySearch, TestLast3, VALUES3.cend(), VALUES3, VALUES3.back());
MUTUAL_SIMPLE_TEST(UpperBound_STL, UpperBound_BinarySearch, TestSample2, VALUES3, 5);
SIMPLE_TEST(UpperBound_BinarySearch,
            TestUnderflow,
            ARRAY_UNDERFLOW.cbegin(),
            ARRAY_UNDERFLOW,
            ARRAY_UNDERFLOW.front() - 1);


const ArrayType SAMPLE4 = {1, 3, 5, 6};


THE_BENCHMARK(SearchInsertPosition, ARRAY1, 10);

SIMPLE_TEST(SearchInsertPosition, TestEmpty, 0, ARRAY_EMPTY, 10);
SIMPLE_TEST(SearchInsertPosition, TestBegin2, 0, ARRAY1, ARRAY1.front() - 1);
SIMPLE_TEST(SearchInsertPosition, TestLast, ARRAY1.size() - 1, ARRAY1, ARRAY1.back() - 1);
SIMPLE_TEST(SearchInsertPosition, TestNotExist, ARRAY1.size(), ARRAY1, 999);
SIMPLE_TEST(SearchInsertPosition, TestUnderflow, 0, ARRAY_UNDERFLOW, ARRAY_UNDERFLOW.front() - 1);
SIMPLE_TEST(SearchInsertPosition, TestSample4, 2, SAMPLE4, 5);
SIMPLE_TEST(SearchInsertPosition, TestSample5, 1, SAMPLE4, 2);
SIMPLE_TEST(SearchInsertPosition, TestSample6, 4, SAMPLE4, 7);
SIMPLE_TEST(SearchInsertPosition, TestSample7, 0, SAMPLE4, 0);


THE_BENCHMARK(SearchInsertPosition_STL, ARRAY1, 10);

SIMPLE_TEST(SearchInsertPosition_STL, TestEmpty, 0, ARRAY_EMPTY, 10);
SIMPLE_TEST(SearchInsertPosition_STL, TestBegin2, 0, ARRAY1, ARRAY1.front() - 1);
SIMPLE_TEST(SearchInsertPosition_STL, TestLast, ARRAY1.size() - 1, ARRAY1, ARRAY1.back() - 1);
SIMPLE_TEST(SearchInsertPosition_STL, TestNotExist, ARRAY1.size(), ARRAY1, 999);
SIMPLE_TEST(
    SearchInsertPosition_STL, TestUnderflow, 0, ARRAY_UNDERFLOW, ARRAY_UNDERFLOW.front() - 1);
SIMPLE_TEST(SearchInsertPosition_STL, TestSample4, 2, SAMPLE4, 5);
SIMPLE_TEST(SearchInsertPosition_STL, TestSample5, 1, SAMPLE4, 2);
SIMPLE_TEST(SearchInsertPosition_STL, TestSample6, 4, SAMPLE4, 7);
SIMPLE_TEST(SearchInsertPosition_STL, TestSample7, 0, SAMPLE4, 0);


THE_BENCHMARK(GreatestLesser_BinarySearch, ARRAY1, 10);

SIMPLE_TEST(GreatestLesser_BinarySearch, TestEmpty, ARRAY_EMPTY.cend(), ARRAY_EMPTY, 10);
SIMPLE_TEST(GreatestLesser_BinarySearch, TestBegin2, ARRAY1.cbegin(), ARRAY1, ARRAY1.front() + 1);
MUTUAL_SIMPLE_TEST(GreatestLesser_STL, GreatestLesser_BinarySearch, TestSample1, ARRAY1, 10);
SIMPLE_TEST(
    GreatestLesser_BinarySearch, TestLast, std::prev(ARRAY1.cend()), ARRAY1, ARRAY1.back() + 1);
SIMPLE_TEST(GreatestLesser_BinarySearch, TestNotExist, ARRAY1.cend(), ARRAY1, 0);
SIMPLE_TEST(GreatestLesser_BinarySearch,
            TestLast3,
            std::prev(VALUES3.cend()),
            VALUES3,
            ARRAY1.back() + 1);
MUTUAL_SIMPLE_TEST(GreatestLesser_STL, GreatestLesser_BinarySearch, TestSample2, VALUES3, 5);
SIMPLE_TEST(GreatestLesser_BinarySearch,
            TestUnderflow,
            ARRAY_UNDERFLOW.cend(),
            ARRAY_UNDERFLOW,
            ARRAY_UNDERFLOW.front() - 1);


THE_BENCHMARK(BinarySearch_Randomized_Iterative, ARRAY1, 10);

SIMPLE_TEST(
    BinarySearch_Randomized_Iterative, TestBegin, ARRAY1.cbegin(), ARRAY1, ARRAY1.front());
MUTUAL_SIMPLE_TEST(
    BinarySearch_STL_Lower, BinarySearch_Randomized_Iterative, TestSample1, ARRAY1, 10);
SIMPLE_TEST(
    BinarySearch_Randomized_Iterative, TestLast, std::prev(ARRAY1.cend()), ARRAY1, ARRAY1.back());
SIMPLE_TEST(BinarySearch_Randomized_Iterative, TestNotExist, ARRAY1.cend(), ARRAY1, 999);
SIMPLE_TEST(BinarySearch_Randomized_Iterative,
            TestUnderflow,
            ARRAY_UNDERFLOW.cend(),
            ARRAY_UNDERFLOW,
            ARRAY_UNDERFLOW.front() - 1);


THE_BENCHMARK(BinarySearch_SinglyList, LIST1, 10);

SIMPLE_TEST(BinarySearch_SinglyList, TestEmpty, LIST_EMPTY.cend(), LIST_EMPTY, 10);
SIMPLE_TEST(BinarySearch_SinglyList, TestBegin, LIST1.cbegin(), LIST1, LIST1.front());
SIMPLE_TEST(BinarySearch_SinglyList,
            TestLast,
            std::next(LIST1.cbegin(), ARRAY1.size() - 1),
            LIST1,
            ARRAY1.back());
SIMPLE_TEST(BinarySearch_SinglyList, TestNotExist, LIST1.cend(), LIST1, 999);
SIMPLE_TEST(BinarySearch_SinglyList,
            TestUnderflow,
            LIST_UNDERFLOW.cend(),
            LIST_UNDERFLOW,
            LIST_UNDERFLOW.front() - 1);


THE_BENCHMARK(GuessNumber_Memo, 10);

SIMPLE_TEST(GuessNumber_Memo, TestSample1, 16, 10);
SIMPLE_TEST(GuessNumber_Memo, TestSample2, 0, 1);
SIMPLE_TEST(GuessNumber_Memo, TestSample3, 1, 2);


THE_BENCHMARK(GuessNumber_Dp, 10);

SIMPLE_TEST(GuessNumber_Dp, TestSample1, 16, 10);
SIMPLE_TEST(GuessNumber_Dp, TestSample2, 0, 1);
SIMPLE_TEST(GuessNumber_Dp, TestSample3, 1, 2);


THE_BENCHMARK(NextGreaterChar, "cfj", 'a');

SIMPLE_TEST(NextGreaterChar, TestSample1, 'c', "cfj", 'a');
SIMPLE_TEST(NextGreaterChar, TestSample2, 'f', "cfj", 'c');
SIMPLE_TEST(NextGreaterChar, TestSample3, 'f', "cfj", 'd');
SIMPLE_TEST(NextGreaterChar, TestSample4, 'j', "cfj", 'g');
SIMPLE_TEST(NextGreaterChar, TestSample5, 'c', "cfj", 'j');


const auto EXPECTED0R = std::pair(-1, -1);

const ArrayType SAMPLE1R = {5, 7, 7, 8, 8, 10};
const auto EXPECTED1R = std::pair(3, 4);

const auto EXPECTED4R = std::pair(0, 0);


THE_BENCHMARK(EqualRange, SAMPLE1R, 8);

SIMPLE_TEST(EqualRange, TestSample1, EXPECTED1R, SAMPLE1R, 8);
SIMPLE_TEST(EqualRange, TestSample2, EXPECTED0R, SAMPLE1R, 6);
SIMPLE_TEST(EqualRange, TestSample3, EXPECTED0R, ARRAY_EMPTY, 0);
SIMPLE_TEST(EqualRange, TestSample4, EXPECTED4R, VALUES3, 2);


THE_BENCHMARK(MaxValueAt, 4, 2, 6);

SIMPLE_TEST(MaxValueAt, TestSample1, 2, 4, 2, 6);
SIMPLE_TEST(MaxValueAt, TestSample2, 3, 6, 1, 10);
SIMPLE_TEST(MaxValueAt, TestSample3, 155230825, 6, 2, 931384943);
