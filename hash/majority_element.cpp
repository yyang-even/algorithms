#include "common_header.h"

#include "hash/hash.h"


namespace {

using ArrayType = std::vector<int>;
constexpr ArrayType::value_type NO_MAJORITY = -1;

/** Majority Element
 *
 * @reference   https://www.geeksforgeeks.org/majority-element/
 * @reference   Majority Element | Set-2 (Hashing)
 *              https://www.geeksforgeeks.org/majority-element-set-2-hashing/
 * @reference   Majority element in a linked list
 *              https://www.geeksforgeeks.org/majority-element-in-a-linked-list/
 * @reference   Check if an array has a majority element
 *              https://www.geeksforgeeks.org/check-array-majority-element/
 *
 * Given an array of size N, find the majority element. The majority element is the
 * element that appears more than n/2 times in the given array.
 *
 * @reference   Majority Element
 *              https://leetcode.com/problems/majority-element/
 *
 * Given an array nums of size n, return the majority element. The majority element is
 * the element that appears more than ⌊n / 2⌋ times. You may assume that the majority
 * element always exists in the array.
 * Follow-up: Could you solve the problem in linear time and in O(1) space?
 */
auto MajorityElement_Map(const ArrayType &elements) {
    std::unordered_map<ArrayType::value_type, ArrayType::size_type> counters;
    for (const auto an_element : elements) {
        if (++(counters[an_element]) > elements.size() / 2) {
            return an_element;
        }
    }
    return NO_MAJORITY;
}


inline auto MajorityElement_Sort(ArrayType elements) {
    assert(not elements.empty());
    std::sort(elements.begin(), elements.end());
    return elements[elements.size() / 2];
}


auto MajorityCandidate_MooreVoting(const ArrayType &elements) {
    assert(not elements.empty());

    ArrayType::value_type candidate = -1;
    int count = 0;
    for (const auto an_element : elements) {
        if (count == 0) {
            candidate = an_element;
            count = 1;
        } else if (candidate == an_element) {
            ++count;
        } else {
            --count;
        }
    }

    return candidate;
}

auto MajorityElement_MooreVoting(const ArrayType &elements) {
    const auto candidate = MajorityCandidate_MooreVoting(elements);

    std::size_t count = 0;
    for (const auto an_element : elements) {
        if (candidate == an_element) {
            ++count;
        }
    }

    if (count > elements.size() / 2) {
        return candidate;
    }
    return NO_MAJORITY;
}


/**
 * @reference   Find the Majority Element | Set 3 (Bit Magic)
 *              https://www.geeksforgeeks.org/find-the-majority-element-set-3-bit-magic/
 */
auto MajorityCandidate_Bit(const ArrayType &elements) {
    ArrayType::value_type candidate = 0;
    for (unsigned i = 0; i < BitsNumber<int>; ++i) {
        std::size_t count = 0;
        for (const auto a_number : elements) {
            if (a_number & (1 << i)) {
                ++count;
            }
        }
        if (count > (elements.size() / 2)) {
            candidate += (1 << i);
        }
    }

    return candidate;
}

auto MajorityElement_Bit(const ArrayType &elements) {
    const auto candidate = MajorityCandidate_Bit(elements);

    std::size_t count = 0;
    for (const auto a_number : elements)
        if (a_number == candidate) {
            ++count;
        }

    if (count > elements.size() / 2) {
        return candidate;
    }
    return NO_MAJORITY;
}


/**
 * @reference   Majority Element II
 *              https://leetcode.com/problems/majority-element-ii/
 *
 * Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋
 * times. Follow-up: Could you solve the problem in linear time and in O(1) space?
 */
auto MajorityElements(const ArrayType &elements) {
    ArrayType::value_type first_candidate = 0;
    std::size_t first_count = 0;
    ArrayType::value_type second_candidate = 0;
    std::size_t second_count = 0;

    for (const auto a_number : elements) {
        // The order of the if statements matters
        if (a_number == first_candidate) {
            ++first_count;
        } else if (a_number == second_candidate) {
            ++second_count;
        } else if (first_count == 0) {
            first_candidate = a_number;
            first_count = 1;
        } else if (second_count == 0) {
            second_candidate = a_number;
            second_count = 1;
        } else {
            --first_count;
            --second_count;
        }
    }

    first_count = 0;
    second_count = 0;
    for (const auto a_number : elements) {
        if (a_number == first_candidate) {
            ++first_count;
        } else if (a_number == second_candidate) {
            ++second_count;
        }
    }

    ArrayType results;
    if (first_count > elements.size() / 3) {
        results.push_back(first_candidate);
    }

    if (second_count > elements.size() / 3) {
        results.push_back(second_candidate);
    }

    return results;
}


/**
 * @reference   N-Repeated Element in Size 2N Array
 *              https://leetcode.com/problems/n-repeated-element-in-size-2n-array/
 *
 * You are given an integer array nums with the following properties:
 *  nums.length == 2 * n.
 *  nums contains n + 1 unique elements.
 *  Exactly one element of nums is repeated n times.
 * Return the element that is repeated n times.
 */
auto HalfRepeatedElement_Set(const ArrayType &nums) {
    std::unordered_set<int> s;
    for (const auto n : nums) {
        if (not s.insert(n).second) {
            return n;
        }
    }
    return 0;
}


auto HalfRepeatedElement_Compare(const ArrayType &nums) {
    for (std::size_t i = 2; i < nums.size(); ++i)
        if (nums[i] == nums[i - 1] or nums[i] == nums[i - 2]) {
            return nums[i];
        }
    return nums.front();
}


/**
 * @reference   Check for Majority Element in a sorted array
 *              https://www.geeksforgeeks.org/check-for-majority-element-in-a-sorted-array/
 *
 * Write a C function to find if a given integer x appears more than n/2 times in a
 * sorted array of n integers.
 *
 * @reference   Check If a Number Is Majority Element in a Sorted Array
 *              https://github.com/geemaple/leetcode/blob/master/leetcode/1150.check-if-a-number-is-majority-element-in-a-sorted-array.py
 *
 * Given an array nums sorted in non-decreasing order, and a number target, return True
 * if and only if target is a majority element. A majority element is an element that
 * appears more than N/2 times in an array of length N.
 */
auto MajorityElement_Sorted(const ArrayType &nums, const int x) {
    assert(std::is_sorted(nums.cbegin(), nums.cend()));

    if (nums.empty() or nums[nums.size() / 2] != x) {
        return false;
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

    return left + nums.size() / 2 < nums.size() and nums[left + nums.size() / 2] == x;
}

inline auto testMajorityElement_Sorted(ArrayType nums, const int x) {
    std::sort(nums.begin(), nums.end());
    return MajorityElement_Sorted(nums, x);
}

}//namespace


const ArrayType SAMPLE1 = {3, 3, 4, 2, 4, 4, 2, 4, 4};
const ArrayType SAMPLE2 = {3, 3, 4, 2, 4, 4, 2, 4};


THE_BENCHMARK(MajorityElement_Map, SAMPLE1);

SIMPLE_TEST(MajorityElement_Map, TestSAMPLE1, 4, SAMPLE1);
SIMPLE_TEST(MajorityElement_Map, TestSAMPLE2, NO_MAJORITY, SAMPLE2);


THE_BENCHMARK(MajorityElement_MooreVoting, SAMPLE1);

SIMPLE_TEST(MajorityElement_MooreVoting, TestSAMPLE1, 4, SAMPLE1);
SIMPLE_TEST(MajorityElement_MooreVoting, TestSAMPLE2, NO_MAJORITY, SAMPLE2);


THE_BENCHMARK(MajorityElement_Sort, SAMPLE1);

SIMPLE_TEST(MajorityElement_Sort, TestSAMPLE1, 4, SAMPLE1);


THE_BENCHMARK(MajorityElement_Bit, SAMPLE1);

SIMPLE_TEST(MajorityElement_Bit, TestSAMPLE1, 4, SAMPLE1);
SIMPLE_TEST(MajorityElement_Bit, TestSAMPLE2, NO_MAJORITY, SAMPLE2);


const ArrayType SAMPLE3 = {3, 2, 3};
const ArrayType EXPECTED3 = {3};

const ArrayType SAMPLE4 = {1};

const ArrayType SAMPLE5 = {1, 2};

const ArrayType SAMPLE6 = {2, 1, 1, 3, 1, 4, 5, 6};
const ArrayType EXPECTED6 = {1};


THE_BENCHMARK(MajorityElements, SAMPLE3);

SIMPLE_TEST(MajorityElements, TestSAMPLE3, EXPECTED3, SAMPLE3);
SIMPLE_TEST(MajorityElements, TestSAMPLE4, SAMPLE4, SAMPLE4);
SIMPLE_TEST(MajorityElements, TestSAMPLE5, SAMPLE5, SAMPLE5);
SIMPLE_TEST(MajorityElements, TestSAMPLE6, EXPECTED6, SAMPLE6);


const ArrayType SAMPLE1H = {1, 2, 3, 3};
const ArrayType SAMPLE2H = {2, 1, 2, 5, 3, 2};
const ArrayType SAMPLE3H = {5, 1, 5, 2, 5, 3, 5, 4};


THE_BENCHMARK(HalfRepeatedElement_Set, SAMPLE1H);

SIMPLE_TEST(HalfRepeatedElement_Set, TestSAMPLE1, 3, SAMPLE1H);
SIMPLE_TEST(HalfRepeatedElement_Set, TestSAMPLE2, 2, SAMPLE2H);
SIMPLE_TEST(HalfRepeatedElement_Set, TestSAMPLE3, 5, SAMPLE3H);


THE_BENCHMARK(HalfRepeatedElement_Compare, SAMPLE1H);

SIMPLE_TEST(HalfRepeatedElement_Compare, TestSAMPLE1, 3, SAMPLE1H);
SIMPLE_TEST(HalfRepeatedElement_Compare, TestSAMPLE2, 2, SAMPLE2H);
SIMPLE_TEST(HalfRepeatedElement_Compare, TestSAMPLE3, 5, SAMPLE3H);


THE_BENCHMARK(testMajorityElement_Sorted, SAMPLE1, 4);

SIMPLE_TEST(testMajorityElement_Sorted, TestSAMPLE1, true, SAMPLE1, 4);
SIMPLE_TEST(testMajorityElement_Sorted, TestSAMPLE2, false, SAMPLE1, 1);
SIMPLE_TEST(testMajorityElement_Sorted, TestSAMPLE3, false, SAMPLE1, 2);
