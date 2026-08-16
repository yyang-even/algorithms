#include "common_header.h"

#include "disjoint_set.h"


namespace {

using ArrayType = std::vector<std::string_view>;

/**
 * @reference   Satisfiability of Equality Equations
 *              https://leetcode.com/problems/satisfiability-of-equality-equations/
 *
 * You are given an array of strings equations that represent relationships between variables where each
 * string equations[i] is of length 4 and takes one of two different forms: "xi==yi" or "xi!=yi".Here,
 * xi and yi are lowercase letters (not necessarily different) that represent one-letter variable names.
 * Return true if it is possible to assign integers to variable names so as to satisfy all the given
 * equations, or false otherwise.
 *
 * @tags    #disjoint-set
 */
auto EquationsPossible(const ArrayType &equations) {
    DisjointSet_Array disjoint_set(26);

    for (const auto e : equations) {
        if (e[1] == '=') {
            disjoint_set.Union(e[0] - 'a', e[3] - 'a');
        }
    }

    for (const auto e : equations) {
        if (e[1] == '!' and disjoint_set.Find(e[0] - 'a') == disjoint_set.Find(e[3] - 'a')) {
            return false;
        }
    }

    return true;
}

} //namespace


const ArrayType SAMPLE1E = {"e==d", "e==a", "f!=d", "b!=c", "a==b"};
const ArrayType SAMPLE2E = {"e==e", "d!=e", "c==d", "d!=e"};
const ArrayType SAMPLE3E = {"f==b", "c==b", "c==b", "e!=f"};
const ArrayType SAMPLE4E = {"c==c", "f!=a", "f==b", "b==c"};
const ArrayType SAMPLE5E = {"b==a", "a==b"};
const ArrayType SAMPLE6E = {"a==b", "b!=a"};


THE_BENCHMARK(EquationsPossible, SAMPLE1E);

SIMPLE_TEST(EquationsPossible, TestSAMPLE1, true, SAMPLE1E);
SIMPLE_TEST(EquationsPossible, TestSAMPLE2, true, SAMPLE2E);
SIMPLE_TEST(EquationsPossible, TestSAMPLE3, true, SAMPLE3E);
SIMPLE_TEST(EquationsPossible, TestSAMPLE4, true, SAMPLE4E);
SIMPLE_TEST(EquationsPossible, TestSAMPLE5, true, SAMPLE5E);
SIMPLE_TEST(EquationsPossible, TestSAMPLE6, false, SAMPLE6E);


#ifdef WANT_TESTS
TEST(DisjointSet_ArrayTest, SanityTest) {
    DisjointSet_Array disjoint_set {5};

    EXPECT_EQ(2u, disjoint_set.Find(2));

    disjoint_set.Union(disjoint_set.Find(1), disjoint_set.Find(0));
    disjoint_set.Union(disjoint_set.Find(1), disjoint_set.Find(3));

    EXPECT_EQ(disjoint_set.Find(1), disjoint_set.Find(3));
    EXPECT_EQ(disjoint_set.Find(0), disjoint_set.Find(3));
    EXPECT_NE(disjoint_set.Find(1), disjoint_set.Find(2));
    EXPECT_NE(disjoint_set.Find(4), disjoint_set.Find(2));
}
#endif
