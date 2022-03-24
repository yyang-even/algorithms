#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Boats to Save People
 *
 * @reference   https://leetcode.com/problems/boats-to-save-people/
 *
 * You are given an array people where people[i] is the weight of the ith person, and an
 * infinite number of boats where each boat can carry a maximum weight of limit. Each boat
 * carries at most two people at the same time, provided the sum of the weight of those
 * people is at most limit.
 * Return the minimum number of boats to carry every given person.
 */
auto BoatsToSavePeople(ArrayType people, const int limit) {
    std::sort(people.begin(), people.end());

    int left = 0;
    int right = people.size() - 1;

    int result = 0;
    while (left <= right) {
        ++result;
        if (people[left] + people[right--] <= limit) {
            ++left;
        }
    }

    return result;
}

}//namespace


const ArrayType SAMPLE1 = {1, 2};
const ArrayType SAMPLE2 = {3, 2, 2, 1};
const ArrayType SAMPLE3 = {3, 5, 3, 4};


THE_BENCHMARK(BoatsToSavePeople, SAMPLE1, 3);

SIMPLE_TEST(BoatsToSavePeople, TestSAMPLE1, 1, SAMPLE1, 3);
SIMPLE_TEST(BoatsToSavePeople, TestSAMPLE2, 3, SAMPLE2, 3);
SIMPLE_TEST(BoatsToSavePeople, TestSAMPLE3, 4, SAMPLE3, 5);
