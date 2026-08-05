#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/**
 * @reference   Minimum Moves to Balance Circular Array
 *              https://leetcode.com/problems/minimum-moves-to-balance-circular-array/
 *
 * You are given a circular array balance of length n, where balance[i] is the net balance of person i.
 * In one move, a person can transfer exactly 1 unit of balance to either their left or right neighbor.
 * Return the minimum number of moves required so that every person has a non-negative balance. If it is
 * impossible, return -1.
 * Note: You are guaranteed that at most 1 index has a negative balance initially.
 *
 * @tags    #greedy #accumulate #min-max-element #circular-array
 */
long long MinMovesToBalance(const ArrayType &balance) {
    long long sum = 0;
    int minimum_index = -1;
    const int N = balance.size();
    for (int i = 0; i < N; ++i) {
        const auto b = balance[i];
        sum += b;
        if (b < 0) {
            minimum_index = i;
        }
    }

    if (minimum_index == -1) {
        return 0;
    }

    if (sum < 0) {
        return -1;
    }

    long long result = 0;
    long long debt = -(balance[minimum_index]);
    for (int l = 1; debt > 0; ++l) {
        const auto left = (minimum_index - l + N) % N;
        const auto right = (minimum_index + l) % N;
        const auto total = static_cast<long long>(balance[left]) + balance[right];
        result += std::min(debt, total) * l;
        debt -= total;
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {5, 1, -4};
const ArrayType SAMPLE2 = {1, 2, -5, 2};
const ArrayType SAMPLE3 = {-3, 2};
const ArrayType SAMPLE4 = {30,  21, 263, 107, 284, 275, 205, 51, 7,   -381,
                           274, 24, 4,   308, 18,  231, 111, 71, 175, 206};


THE_BENCHMARK(MinMovesToBalance, SAMPLE1);

SIMPLE_TEST(MinMovesToBalance, TestSAMPLE1, 4, SAMPLE1);
SIMPLE_TEST(MinMovesToBalance, TestSAMPLE2, 6, SAMPLE2);
SIMPLE_TEST(MinMovesToBalance, TestSAMPLE3, -1, SAMPLE3);
SIMPLE_TEST(MinMovesToBalance, TestSAMPLE4, 506, SAMPLE4);
