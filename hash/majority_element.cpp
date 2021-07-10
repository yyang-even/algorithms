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
