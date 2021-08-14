#include "common_header.h"


namespace {

using HeightWeightPair = std::pair<int, int>;
using ArrayType = std::vector<HeightWeightPair>;

/**
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 11.7.
 *
 * A circus is designing a tower routine consisting of people standing atop one another's
 * shoulders. For practical and aesthetic reasons, each person must be both shorter and
 * lighter than the person below him or her. Given the heights and weights of each person
 * in the circus, write a method to compute the largest possible number of people in such
 * a tower.
 *
 * Note: This problem is a variation of LIS problem.
 */
auto CircusTower(ArrayType people) {
    assert(not people.empty());

    std::sort(people.begin(), people.end(),
    [](const auto & lhs, const auto & rhs) {
        return lhs.first < rhs.first;
    });

    const auto N = people.size();
    std::vector LISs(N, 1);
    for (ArrayType::size_type i = 1; i < N; ++i) {
        for (ArrayType::size_type j = 0; j < i; ++j) {
            if (people[i].second > people[j].second and LISs[i] <= LISs[j]) {
                LISs[i] = LISs[j] + 1;
            }
        }
    }

    return *std::max_element(LISs.cbegin(), LISs.cend());
}

}//namespace


const ArrayType SAMPLE1 = {{65, 100}, {70, 150}, {56, 90}, {75, 190}, {60, 95}, {68, 110}};


THE_BENCHMARK(CircusTower, SAMPLE1);

SIMPLE_TEST(CircusTower, TestSAMPLE1, 6, SAMPLE1);
