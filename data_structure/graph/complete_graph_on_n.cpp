#include "common_header.h"


namespace {

/** Complete Graph on n Vertices
 *
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Section 7.6.
 *
 * How many spanning trees are possible in the complete graph on n vertices {1,2,...,n}?
 * The complete graph has n(n-1)/2 edges, one edge joining each pair of distinct vertices;
 * so we're essentially looking for the total number of ways to connect up n given things
 * by drawing n-1 lines between them.
 */
/**
 * t(n) = n^(n-2)
 */
unsigned long long CompleteGraphOnN(const unsigned n) {
    return std::pow(n, n - 2);
}

}//namespace


SIMPLE_BENCHMARK(CompleteGraphOnN, Sample1, 1);

SIMPLE_TEST(CompleteGraphOnN, TestSample1, 0, 0);
SIMPLE_TEST(CompleteGraphOnN, TestSample2, 1, 1);
SIMPLE_TEST(CompleteGraphOnN, TestSample3, 1, 2);
SIMPLE_TEST(CompleteGraphOnN, TestSample4, 3, 3);
SIMPLE_TEST(CompleteGraphOnN, TestSample5, 16, 4);
