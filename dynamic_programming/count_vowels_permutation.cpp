#include "common_header.h"


namespace {

using MemoType = std::unordered_map<char, std::vector<long>>;

/** Count Vowels Permutation
 *
 * @reference   https://leetcode.com/problems/count-vowels-permutation/
 *
 * Given an integer n, your task is to count how many strings of length n can be formed under the
 * following rules:
 *  Each character is a lower case vowel ('a', 'e', 'i', 'o', 'u')
 *  Each vowel 'a' may only be followed by an 'e'.
 *  Each vowel 'e' may only be followed by an 'a' or an 'i'.
 *  Each vowel 'i' may not be followed by another 'i'.
 *  Each vowel 'o' may only be followed by an 'i' or a 'u'.
 *  Each vowel 'u' may only be followed by an 'a'.
 * Since the answer may be too large, return it modulo 10^9 + 7.
 */
constexpr auto CountVowelsPermutation_DP(const int n) {
    long a_count[n] = {1};
    long e_count[n] = {1};
    long i_count[n] = {1};
    long o_count[n] = {1};
    long u_count[n] = {1};

    for (int i = 1; i < n; ++i) {
        a_count[i] = (e_count[i - 1] + i_count[i - 1] + u_count[i - 1]) % LARGE_PRIME;
        e_count[i] = (a_count[i - 1] + i_count[i - 1]) % LARGE_PRIME;
        i_count[i] = (e_count[i - 1] + o_count[i - 1]) % LARGE_PRIME;
        o_count[i] = i_count[i - 1] % LARGE_PRIME;
        u_count[i] = (i_count[i - 1] + o_count[i - 1]) % LARGE_PRIME;
    }

    return (a_count[n - 1] + e_count[n - 1] + i_count[n - 1] + o_count[n - 1] + u_count[n - 1]) %
           LARGE_PRIME;
}


constexpr auto CountVowelsPermutation_DP_O1(const int n) {
    long a_count = 1, e_count = 1, i_count = 1, o_count = 1, u_count = 1;

    for (int i = 1; i < n; ++i) {
        const auto a_count_new = (e_count + i_count + u_count) % LARGE_PRIME;
        const auto e_count_new = (a_count + i_count) % LARGE_PRIME;
        const auto i_count_new = (e_count + o_count) % LARGE_PRIME;
        const auto o_count_new = (i_count) % LARGE_PRIME;
        const auto u_count_new = (i_count + o_count) % LARGE_PRIME;
        a_count = a_count_new;
        e_count = e_count_new;
        i_count = i_count_new;
        o_count = o_count_new;
        u_count = u_count_new;
    }

    return (a_count + e_count + i_count + o_count + u_count) % LARGE_PRIME;
}


auto CountVowelsPermutation_Memo(const int i, const char vowel, MemoType &memo) {
    if (memo[vowel][i]) {
        return memo[vowel][i];
    }

    if (i == 0) {
        memo[vowel][i] = 1;
    } else {
        if (vowel == 'a') {
            memo[vowel][i] = (CountVowelsPermutation_Memo(i - 1, 'e', memo) +
                              CountVowelsPermutation_Memo(i - 1, 'i', memo) +
                              CountVowelsPermutation_Memo(i - 1, 'u', memo)) %
                             LARGE_PRIME;
        } else if (vowel == 'e') {
            memo[vowel][i] = (CountVowelsPermutation_Memo(i - 1, 'a', memo) +
                              CountVowelsPermutation_Memo(i - 1, 'i', memo)) %
                             LARGE_PRIME;
        } else if (vowel == 'i') {
            memo[vowel][i] = (CountVowelsPermutation_Memo(i - 1, 'e', memo) +
                              CountVowelsPermutation_Memo(i - 1, 'o', memo)) %
                             LARGE_PRIME;
        } else if (vowel == 'o') {
            memo[vowel][i] = CountVowelsPermutation_Memo(i - 1, 'i', memo);
        } else if (vowel == 'u') {
            memo[vowel][i] = (CountVowelsPermutation_Memo(i - 1, 'i', memo) +
                              CountVowelsPermutation_Memo(i - 1, 'o', memo)) %
                             LARGE_PRIME;
        }
    }

    return memo[vowel][i];
}

inline auto CountVowelsPermutation_Memo(const int n) {
    MemoType memo {{'a', std::vector(n, 0l)},
                   {'e', std::vector(n, 0l)},
                   {'i', std::vector(n, 0l)},
                   {'o', std::vector(n, 0l)},
                   {'u', std::vector(n, 0l)}};

    return (CountVowelsPermutation_Memo(n - 1, 'a', memo) +
            CountVowelsPermutation_Memo(n - 1, 'e', memo) +
            CountVowelsPermutation_Memo(n - 1, 'i', memo) +
            CountVowelsPermutation_Memo(n - 1, 'o', memo) +
            CountVowelsPermutation_Memo(n - 1, 'u', memo)) %
           LARGE_PRIME;
}


/**
 * @reference   Knight Dialer
 *              https://leetcode.com/problems/knight-dialer/
 *
 * The chess knight has a unique movement, it may move two squares vertically and one square
 * horizontally, or two squares horizontally and one square vertically (with both forming the shape of
 * an L).
 * We have a chess knight and a phone pad as shown below, the knight can only stand on a numeric cell
 * (i.e. blue cell).
 *  1   2   3
 *  4   5   6
 *  7   8   9
 *  *   0   #
 * Given an integer n, return how many distinct phone numbers of length n we can dial.
 * You are allowed to place the knight on any numeric cell initially and then you should perform n - 1
 * jumps to dial a number of length n. All jumps should be valid knight jumps.
 * As the answer may be very large, return the answer modulo 10^9 + 7.
 */
int KnightDialer(int n) {
    const std::vector<std::vector<int>> moves = {
        {4, 6}, {6, 8}, {7, 9}, {4, 8}, {0, 3, 9}, {}, {0, 1, 7}, {2, 6}, {1, 3}, {2, 4}};

    std::vector result(moves.size(), 1);
    while (n-- > 1) {
        std::vector temp(moves.size(), 0);
        for (std::size_t i = 0; i < moves.size(); ++i) {
            for (const auto n : moves[i]) {
                temp[n] = (temp[n] + result[i]) % LARGE_PRIME;
            }
        }

        std::swap(result, temp);
    }

    return std::accumulate(result.cbegin(), result.cend(), 0ll) % LARGE_PRIME;
}

} //namespace


THE_BENCHMARK(CountVowelsPermutation_DP, 5);

SIMPLE_TEST(CountVowelsPermutation_DP, TestSAMPLE1, 5, 1);
SIMPLE_TEST(CountVowelsPermutation_DP, TestSAMPLE2, 10, 2);
SIMPLE_TEST(CountVowelsPermutation_DP, TestSAMPLE3, 68, 5);


THE_BENCHMARK(CountVowelsPermutation_DP_O1, 5);

SIMPLE_TEST(CountVowelsPermutation_DP_O1, TestSAMPLE1, 5, 1);
SIMPLE_TEST(CountVowelsPermutation_DP_O1, TestSAMPLE2, 10, 2);
SIMPLE_TEST(CountVowelsPermutation_DP_O1, TestSAMPLE3, 68, 5);


THE_BENCHMARK(CountVowelsPermutation_Memo, 5);

SIMPLE_TEST(CountVowelsPermutation_Memo, TestSAMPLE1, 5, 1);
SIMPLE_TEST(CountVowelsPermutation_Memo, TestSAMPLE2, 10, 2);
SIMPLE_TEST(CountVowelsPermutation_Memo, TestSAMPLE3, 68, 5);


THE_BENCHMARK(KnightDialer, 5);

SIMPLE_TEST(KnightDialer, TestSAMPLE1, 10, 1);
SIMPLE_TEST(KnightDialer, TestSAMPLE2, 20, 2);
SIMPLE_TEST(KnightDialer, TestSAMPLE3, 136006598, 3131);
