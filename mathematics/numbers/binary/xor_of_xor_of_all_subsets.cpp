#include "common_header.h"


namespace {

using SetType = std::unordered_set<unsigned>;

/** Given a set, find XOR of the XOR’s of all subsets.
 *
 * @reference   https://www.geeksforgeeks.org/given-a-set-find-xor-of-the-xors-of-all-subsets/
 * @reference   Bits manipulation (Important tactics)
 *              https://www.geeksforgeeks.org/bits-manipulation-important-tactics/
 *
 * The question is to find XOR of the XOR's of all subsets. i.e if the set is {1,2,3}.
 * All subsets are : [{1}, {2}, {3}, {1, 2}, {1, 3}, {2, 3}, {1, 2, 3}]. Find the XOR
 * of each of the subset and then find the XOR of every subset result.
 */
inline SetType::value_type FindXorOfXorOfAllSubsets(const SetType &s) {
    return s.size() == 1 ? *s.cbegin() : 0;
}

}//namespace


const SetType SAMPLE_SET = {1, 2, 3};
const SetType SINGLE_SET = {5};


THE_BENCHMARK(FindXorOfXorOfAllSubsets, SAMPLE_SET);

SIMPLE_TEST(FindXorOfXorOfAllSubsets, TestSample1, 0, SAMPLE_SET);
SIMPLE_TEST(FindXorOfXorOfAllSubsets, TestSample2, *SINGLE_SET.cbegin(), SINGLE_SET);
