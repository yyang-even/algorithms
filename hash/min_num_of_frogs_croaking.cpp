#include "common_header.h"


namespace {

/**
 * @reference   Minimum Number of Frogs Croaking
 *              https://leetcode.com/problems/minimum-number-of-frogs-croaking/
 *
 * You are given the string croakOfFrogs, which represents a combination of the string "croak" from
 * different frogs, that is, multiple frogs can croak at the same time, so multiple "croak" are mixed.
 * Return the minimum number of different frogs to finish all the croaks in the given string.
 * A valid "croak" means a frog is printing five letters 'c', 'r', 'o', 'a', and 'k' sequentially. The
 * frogs have to print all five letters to finish a croak. If the given string is not a combination of a
 * valid "croak" return -1.
 *
 * @tags    #hash-table
 */
auto MinNumOfFrogsCroaking(const std::string_view croakOfFrogs) {
    const std::string_view CROAK = "croak";
    const auto N = CROAK.size();

    if (croakOfFrogs.size() % N != 0) {
        return -1;
    }

    int result = 0;
    int current_croaking = 0;
    std::vector progress(N, 0);
    for (const auto c : croakOfFrogs) {
        const auto i = CROAK.find(c);

        if (i == 0) {
            result = std::max(result, ++current_croaking);
        } else if (progress[i - 1]-- <= 0) {
            return -1;
        } else if (i == 4) {
            --current_croaking;
        }

        ++progress[i];
    }

    return current_croaking == 0 ? result : -1;
}

} //namespace


THE_BENCHMARK(MinNumOfFrogsCroaking, "croakcroak");

SIMPLE_TEST(MinNumOfFrogsCroaking, TestSAMPLE1, 1, "croakcroak");
SIMPLE_TEST(MinNumOfFrogsCroaking, TestSAMPLE2, 2, "crcoakroak");
SIMPLE_TEST(MinNumOfFrogsCroaking, TestSAMPLE3, -1, "croakcrook");
