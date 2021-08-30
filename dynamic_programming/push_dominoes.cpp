#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Push Dominoes
 *
 * @reference   https://leetcode.com/problems/push-dominoes/
 *
 * There are n dominoes in a line, and we place each domino vertically upright. In the
 * beginning, we simultaneously push some of the dominoes either to the left or to the
 * right. After each second, each domino that is falling to the left pushes the adjacent
 * domino on the left. Similarly, the dominoes falling to the right push their adjacent
 * dominoes standing on the right. When a vertical domino has dominoes falling on it
 * from both sides, it stays still due to the balance of the forces. For the purposes of
 * this question, we will consider that a falling domino expends no additional force to
 * a falling or already fallen domino. You are given a string dominoes representing the
 * initial state where:
 *  dominoes[i] = 'L', if the ith domino has been pushed to the left,
 *  dominoes[i] = 'R', if the ith domino has been pushed to the right, and
 *  dominoes[i] = '.', if the ith domino has not been pushed.
 * Return a string representing the final state.
 */
auto PushDominoes_TwoPointers(const std::string_view dominoes) {
    std::vector index_symbols{std::pair(-1, 'L')};

    for (std::size_t i = 0; i < dominoes.size(); ++i) {
        if (dominoes[i] != '.') {
            index_symbols.emplace_back(i, dominoes[i]);
        }
    }
    index_symbols.emplace_back(dominoes.size(), 'R');

    std::string result(dominoes);
    const auto N = index_symbols.size();
    for (std::size_t i = 0; i < N - 1; ++i) {
        const auto [start, start_symbol] = index_symbols[i];
        const auto [last, next_symbol] = index_symbols[i + 1];
        if (start_symbol == next_symbol) {
            for (auto k = start + 1; k < last; ++k) {
                result[k] = start_symbol;
            }
        } else if (start_symbol == 'R' and next_symbol == 'L') {
            for (auto k = start + 1; k < last; ++k) {
                result[k] = (k - start == last - k) ? '.' : (k - start < last - k) ? 'R' : 'L';
            }
        }
    }

    return result;
}


auto PushDominoes_Force(const std::string_view dominoes) {
    int forces[dominoes.size()] = {};

    int current_force = 0;
    for (std::size_t i = 0; i < dominoes.size(); ++i) {
        if (dominoes[i] == 'R') {
            current_force = dominoes.size();
        } else if (dominoes[i] == 'L') {
            current_force = 0;
        } else if (current_force != 0) {
            --current_force;
        }
        forces[i] = current_force;
    }

    current_force = 0;
    for (int i = dominoes.size() - 1; i >= 0; --i) {
        if (dominoes[i] == 'L') {
            current_force = dominoes.size();
        } else if (dominoes[i] == 'R') {
            current_force = 0;
        } else if (current_force != 0) {
            --current_force;
        }
        forces[i] -= current_force;
    }

    std::string result;
    for (const auto a_force : forces) {
        result.push_back(a_force > 0 ? 'R' : a_force < 0 ? 'L' : '.');
    }
    return result;
}


/**
 * @reference   Shortest Distance to a Character
 *              https://leetcode.com/problems/shortest-distance-to-a-character/
 *
 * Given a string s and a character c that occurs in s, return an array of integers
 * answer where answer.length == s.length and answer[i] is the distance from index i to
 * the closest occurrence of character c in s. The distance between two indices i and j
 * is abs(i - j), where abs is the absolute value function.
 */
auto ShortestDistanceToChar(const std::string_view &s, const char c) {
    std::vector<int> result;
    int distance = s.size();
    for (const auto x : s) {
        if (c == x) {
            distance = 0;
        } else {
            ++distance;
        }

        result.push_back(distance);
    }

    distance = s.size();
    for (int i = s.size() - 1; i >= 0; --i) {
        if (c == s[i]) {
            distance = 0;
        } else {
            ++distance;
        }

        result[i] = std::min(result[i], distance);
    }

    return result;
}

}//namespace


THE_BENCHMARK(PushDominoes_TwoPointers, "RR.L");

SIMPLE_TEST(PushDominoes_TwoPointers, TestSAMPLE1, "RR.L", "RR.L");
SIMPLE_TEST(PushDominoes_TwoPointers, TestSAMPLE2, "LL.RR.LLRRLL..", ".L.R...LR..L..");


THE_BENCHMARK(PushDominoes_Force, "RR.L");

SIMPLE_TEST(PushDominoes_Force, TestSAMPLE1, "RR.L", "RR.L");
SIMPLE_TEST(PushDominoes_Force, TestSAMPLE2, "LL.RR.LLRRLL..", ".L.R...LR..L..");


const ArrayType EXPECTED1 = {3, 2, 1, 0, 1, 0, 0, 1, 2, 2, 1, 0};
const ArrayType EXPECTED2 = {3, 2, 1, 0};


THE_BENCHMARK(ShortestDistanceToChar, "loveleetcode", 'e');

SIMPLE_TEST(ShortestDistanceToChar, TestSAMPLE1, EXPECTED1, "loveleetcode", 'e');
SIMPLE_TEST(ShortestDistanceToChar, TestSAMPLE2, EXPECTED2, "aaab", 'b');
