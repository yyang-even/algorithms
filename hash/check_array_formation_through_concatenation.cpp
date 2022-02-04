#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Check Array Formation Through Concatenation
 *
 * @reference   https://leetcode.com/problems/check-array-formation-through-concatenation/
 *
 * You are given an array of distinct integers arr and an array of integer arrays pieces,
 * where the integers in pieces are distinct. Your goal is to form arr by concatenating
 * the arrays in pieces in any order. However, you are not allowed to reorder the integers
 * in each array pieces[i].
 * Return true if it is possible to form the array arr from pieces. Otherwise, return false.
 * 1 <= pieces.length <= arr.length <= 100
 * sum(pieces[i].length) == arr.length
 * The integers in pieces are distinct (i.e., If we flatten pieces in a 1D array, all the
 * integers in this array are distinct).
 */
auto CheckArrayFormation(const ArrayType &nums, const std::vector<ArrayType> &pieces) {
    std::vector hash(101, -1);
    for (std::size_t i = 0; i < pieces.size(); ++i) {
        hash[pieces[i].front()] = i;
    }

    for (std::size_t i = 0; i < nums.size();) {
        const auto p = hash[nums[i]];
        if (p == -1) {
            return false;
        }

        for (std::size_t j = 0; j < pieces[p].size();) {
            if (nums[i++] != pieces[p][j++]) {
                return false;
            }
        }
    }

    return true;
}

}//namespace


const ArrayType SAMPLE1N = {15, 88};
const std::vector<ArrayType> SAMPLE1P = {{88}, {15}};

const ArrayType SAMPLE2N = {49, 18, 16};
const std::vector<ArrayType> SAMPLE2P = {{16, 18, 49}};

const ArrayType SAMPLE3N = {91, 4, 64, 78};
const std::vector<ArrayType> SAMPLE3P = {{78}, {4, 64}, {91}};


THE_BENCHMARK(CheckArrayFormation, SAMPLE1N, SAMPLE1P);

SIMPLE_TEST(CheckArrayFormation, TestSAMPLE1, true, SAMPLE1N, SAMPLE1P);
SIMPLE_TEST(CheckArrayFormation, TestSAMPLE2, false, SAMPLE2N, SAMPLE2P);
SIMPLE_TEST(CheckArrayFormation, TestSAMPLE3, true, SAMPLE3N, SAMPLE3P);
