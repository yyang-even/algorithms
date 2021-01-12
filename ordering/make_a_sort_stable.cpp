#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Make a Sort Stable
 *
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 8.
 *
 * Write code that uses an unstable sort routine to perform a stable sort.
 */
auto MakeSortStable(const ArrayType &elements) {
    std::vector<std::pair<ArrayType::value_type, ArrayType::size_type>>
            elements_with_sequence;
    ArrayType::size_type i = 0;
    for (const auto e : elements) {
        elements_with_sequence.emplace_back(e, i);
    }

    std::sort(elements_with_sequence.begin(), elements_with_sequence.end(),
    [](const auto & lhs, const auto & rhs) {
        if (lhs.first == rhs.first) {
            return lhs.second < rhs.second;
        }
        return lhs.first < rhs.first;
    });

    ArrayType result;
    for (const auto &element_sequence_pair : elements_with_sequence) {
        result.push_back(std::move(element_sequence_pair.first));
    }

    return result;
}

}//namespace


const ArrayType VALUES1 = {};
const ArrayType VALUES2 = {1};
const ArrayType VALUES3 = {1, 2};
const ArrayType VALUES4 = {2, 3, 1};
const ArrayType EXPECTED4 = {1, 2, 3};
const ArrayType VALUES5 = {4, 3, 2, 1};
const ArrayType EXPECTED5 = {1, 2, 3, 4};


SIMPLE_BENCHMARK(MakeSortStable, Sample1, VALUES5);

SIMPLE_TEST(MakeSortStable, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(MakeSortStable, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(MakeSortStable, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(MakeSortStable, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(MakeSortStable, TestSAMPLE5, EXPECTED5, VALUES5);
