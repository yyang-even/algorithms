#include "common_header.h"


namespace {

using ArrayType = std::unordered_multiset<std::string>;

/** Write a program to print all permutations of a given string
 *
 * @reference   https://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/
 * @reference   Permutations of a given string using STL
 *              https://www.geeksforgeeks.org/permutations-of-a-given-string-using-stl/
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 7.
 * @reference   Section VI. Five Algorithm Approaches.
 *              Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *
 * A permutation, also called an "arrangement number" or "order", is a rearrangement of
 * the elements of an ordered list S into a one-to-one correspondence with S itself. A
 * string of length n has n! permutation.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 9.5.
 *
 * @reference   Permutations
 *              https://leetcode.com/problems/permutations/
 *
 * Given an array nums of distinct integers, return all the possible permutations. You
 * can return the answer in any order.
 *
 * @complexity  O(n * n!)
 */
void PermutationHelper(const std::string &input, std::string::iterator start,
                       ArrayType &outputs) {
    if (start == input.cend()) {
        outputs.insert(input);
    } else {
        for (auto iter = start; iter != input.cend(); ++iter) {
            std::iter_swap(start, iter);
            PermutationHelper(input, std::next(start), outputs);
            std::iter_swap(start, iter);
        }
    }
}

inline auto Permutation(std::string input) {
    assert(not input.empty());

    ArrayType outputs;
    PermutationHelper(input, input.begin(), outputs);
    return outputs;
}


auto PermutationSTL(std::string input) {
    ArrayType outputs;

    std::sort(input.begin(), input.end());

    do {
        outputs.insert(input);
    } while (std::next_permutation(input.begin(), input.end()));

    return outputs;
}


/**
 * @reference   Permutations II
 *              https://leetcode.com/problems/permutations-ii/
 *
 * Given a collection of numbers, nums, that might contain duplicates, return all
 * possible unique permutations in any order.
 */
void PermutationWithDuplicates_Hash(std::string &nums, const std::size_t i,
                                    ArrayType &results) {
    if (i >= nums.size()) {
        results.insert(nums);
        return;
    }

    std::unordered_set<char> seen;
    for (auto j = i; j < nums.size(); ++j) {
        if (seen.insert(nums[j]).second) {
            std::swap(nums[i], nums[j]);
            PermutationWithDuplicates_Hash(nums, i + 1, results);
            std::swap(nums[i], nums[j]);
        }
    }
}

inline auto PermutationWithDuplicates_Hash(std::string nums) {
    ArrayType results;
    PermutationWithDuplicates_Hash(nums, 0, results);
    return results;
}


void PermutationWithDuplicates_Sort(std::string nums, const std::size_t i,
                                    ArrayType &results) {
    if (i >= nums.size()) {
        results.insert(nums);
        return;
    }

    for (auto j = i; j < nums.size(); ++j) {
        if (i != j and nums[i] == nums[j]) {
            continue;
        }

        std::swap(nums[i], nums[j]);
        PermutationWithDuplicates_Sort(nums, i + 1, results);
    }
}

inline auto PermutationWithDuplicates_Sort(std::string nums) {
    std::sort(nums.begin(), nums.end());

    ArrayType results;
    PermutationWithDuplicates_Sort(nums, 0, results);
    return results;
}

}//namespace


const ArrayType EXPECTED1 = {"abc", "acb", "bac", "bca", "cba", "cab"};


THE_BENCHMARK(Permutation, "ab4c12ed3");

SIMPLE_TEST(Permutation, TestSAMPLE1, EXPECTED1, "abc");


THE_BENCHMARK(PermutationSTL, "ab4c12ed3");

SIMPLE_TEST(PermutationSTL, TestSAMPLE1, EXPECTED1, "abc");


const ArrayType EXPECTED2D = {"112", "121", "211"};
const ArrayType EXPECTED3D = {"2211", "2121", "2112", "1221", "1212", "1122"};


THE_BENCHMARK(PermutationWithDuplicates_Hash, "ab4c12ed3");

SIMPLE_TEST(PermutationWithDuplicates_Hash, TestSAMPLE1, EXPECTED1, "abc");
SIMPLE_TEST(PermutationWithDuplicates_Hash, TestSAMPLE2, EXPECTED2D, "112");
SIMPLE_TEST(PermutationWithDuplicates_Hash, TestSAMPLE3, EXPECTED3D, "1122");


THE_BENCHMARK(PermutationWithDuplicates_Sort, "ab4c12ed3");

SIMPLE_TEST(PermutationWithDuplicates_Sort, TestSAMPLE1, EXPECTED1, "abc");
SIMPLE_TEST(PermutationWithDuplicates_Sort, TestSAMPLE2, EXPECTED2D, "112");
SIMPLE_TEST(PermutationWithDuplicates_Sort, TestSAMPLE3, EXPECTED3D, "1122");
