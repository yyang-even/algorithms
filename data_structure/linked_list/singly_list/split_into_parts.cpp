#include "common_header.h"


namespace {

using ListType = std::forward_list<int>;
using ArrayType = std::vector<ListType>;

/** Split Linked List in Parts
 *
 * @reference   https://leetcode.com/problems/split-linked-list-in-parts/
 *
 * Given the head of a singly linked list and an integer k, split the linked list into k
 * consecutive linked list parts. The length of each part should be as equal as possible:
 * no two parts should have a size differing by more than one. This may lead to some parts
 * being null. The parts should be in the order of occurrence in the input list, and parts
 * occurring earlier should always have a size greater than or equal to parts occurring
 * later. Return an array of the k parts.
 */
auto SplitIntoParts(ListType a_list, const int k) {
    const auto length = std::distance(a_list.cbegin(), a_list.cend());
    const auto average = length / k;
    const auto number_longer = length % k;

    ArrayType result;
    for (int i = 0; i < k; ++i) {
        ListType part;
        part.splice_after(part.cbefore_begin(), a_list, a_list.cbefore_begin(),
                          std::next(a_list.cbegin(), average + (i < number_longer)));
        result.push_back(part);
    }

    return result;
}

}//namespace


const ListType SAMPLE1 = {1, 2, 3};
const ArrayType EXPECTED1 = {{1}, {2}, {3}, {}, {}};

const ListType SAMPLE2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
const ArrayType EXPECTED2 = {{1, 2, 3, 4}, {5, 6, 7}, {8, 9, 10}};


THE_BENCHMARK(SplitIntoParts, SAMPLE2, 3);

SIMPLE_TEST(SplitIntoParts, TestSAMPLE1, EXPECTED1, SAMPLE1, 5);
SIMPLE_TEST(SplitIntoParts, TestSAMPLE2, EXPECTED2, SAMPLE2, 3);
