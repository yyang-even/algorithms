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
 */
auto MajorityElement_Map(const ArrayType &elements) {
    std::unordered_map<ArrayType::value_type, ArrayType::size_type> counters;
    for (const auto &an_element : elements) {
        if (++(counters[an_element]) > elements.size() / 2) {
            return an_element;
        }
    }
    return NO_MAJORITY;
}


auto MajorityCandidate_MooreVoting(const ArrayType &elements) {
    assert(not elements.empty());

    auto major = elements.front();
    int count = 1;
    for (const auto an_element : elements) {
        if (major == an_element) {
            ++count;
        } else {
            --count;
        }

        if (count == 0) {
            major = an_element;
            count = 1;
        }
    }

    return major;
}

auto MajorityElement_MooreVoting(const ArrayType &elements) {
    const auto candidate = MajorityCandidate_MooreVoting(elements);

    unsigned count = 0;
    for (const auto an_element : elements) {
        if (candidate == an_element) {
            ++count;
        }
        if (count > elements.size() / 2) {
            return candidate;
        }
    }

    return NO_MAJORITY;
}


/**
 * @reference   Find the Majority Element | Set 3 (Bit Magic)
 *              https://www.geeksforgeeks.org/find-the-majority-element-set-3-bit-magic/
 */

}//namespace


const ArrayType SAMPLE1 = {3, 3, 4, 2, 4, 4, 2, 4, 4};
const ArrayType SAMPLE2 = {3, 3, 4, 2, 4, 4, 2, 4};


THE_BENCHMARK(MajorityElement_Map, SAMPLE1);

SIMPLE_TEST(MajorityElement_Map, TestSAMPLE1, 4, SAMPLE1);
SIMPLE_TEST(MajorityElement_Map, TestSAMPLE2, NO_MAJORITY, SAMPLE2);


THE_BENCHMARK(MajorityElement_MooreVoting, SAMPLE1);

SIMPLE_TEST(MajorityElement_MooreVoting, TestSAMPLE1, 4, SAMPLE1);
SIMPLE_TEST(MajorityElement_MooreVoting, TestSAMPLE2, NO_MAJORITY, SAMPLE2);
