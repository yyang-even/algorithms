#include "common_header.h"


namespace {

using ArrayType = std::vector<std::string::size_type>;

/** String Matching
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 32.1.
 * @reference   Naive algorithm for Pattern Searching
 *              https://www.geeksforgeeks.org/naive-algorithm-for-pattern-searching/
 * @reference   C Program for Naive algorithm for Pattern Searching
 *              https://www.geeksforgeeks.org/c-program-for-naive-algorithm-for-pattern-searching/
 *
 * Given a text txt[0..n-1] and a pattern pat[0..m-1], write a function
 * search(char pat[], char txt[]) that prints all occurrences of pat[] in txt[].
 * You may assume that n > m.
 */
auto StringMatcing_Naive(const std::string &text, const std::string &pattern) {
    assert(text.size() >= pattern.size());

    ArrayType shifts;
    for (std::string::size_type i = 0; i <= text.size() - pattern.size(); ++i) {
        std::string::size_type j = 0;
        for (; j < pattern.size(); ++j) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }

        if (j == pattern.size()) {
            shifts.push_back(i);
        }
    }

    return shifts;
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 32.1-2.
 * @reference   Optimized Naive Algorithm for Pattern Searching
 *              https://www.geeksforgeeks.org/optimized-naive-algorithm-for-pattern-searching/
 */
auto StringMatcing_OptimizedNaive(const std::string &text, const std::string &pattern) {
    assert(text.size() >= pattern.size());
    assert(std::unordered_set<char>(pattern.cbegin(), pattern.cend()).size() ==
           pattern.size());

    ArrayType shifts;
    std::string::size_type i = 0;
    while (i <= text.size() - pattern.size()) {
        std::string::size_type j = 0;
        for (; j < pattern.size(); ++j) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }

        if (j == pattern.size()) {
            shifts.push_back(i);
            i += pattern.size();
        } else if (j) {
            i += j;
        } else {
            ++i;
        }
    }

    return shifts;
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 32.2.
 * @reference   Rabin-Karp Algorithm for Pattern Searching
 *              https://www.geeksforgeeks.org/rabin-karp-algorithm-for-pattern-searching/
 * @reference   C Program for Rabin-Karp Algorithm for Pattern Searching
 *              https://www.geeksforgeeks.org/c-program-for-rabin-karp-algorithm-for-pattern-searching/
 */
auto StringMatcing_RabinKarp(const std::string &text, const std::string &pattern,
                             const int q = 101) {
    assert(not pattern.empty());
    assert(text.size() >= pattern.size());

    const int RADIX_D = 256;
    int h = 1;

    for (std::string::size_type i = 0; i < pattern.size() - 1; ++i) {
        h = (h * RADIX_D) % q;
    }

    int pattern_hash = 0;
    int text_hash = 0;
    for (std::string::size_type i = 0; i < pattern.size(); ++i) {
        pattern_hash = (RADIX_D * pattern_hash + pattern[i]) % q;
        text_hash = (RADIX_D * text_hash + text[i]) % q;
    }

    ArrayType shifts;
    for (std::string::size_type i = 0; i <= text.size() - pattern.size(); ++i) {
        if (pattern_hash == text_hash) {
            std::string::size_type j = 0;
            for (; j < pattern.size(); ++j) {
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }

            if (j == pattern.size()) {
                shifts.push_back(i);
            }
        }

        if (i < text.size() - pattern.size()) {
            text_hash = (RADIX_D * (text_hash - text[i] * h) + text[i + pattern.size()]) % q;
            if (text_hash < 0) {
                text_hash += q;
            }
        }
    }

    return shifts;
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 32.3.
 * @reference   Finite Automata algorithm for Pattern Searching
 *              https://www.geeksforgeeks.org/finite-automata-algorithm-for-pattern-searching/
 */
std::string::size_type getNextState(const std::string &pattern,
                                    const std::string::size_type state, const int c) {
    if (state < pattern.size() and c == pattern[state]) {
        return state + 1;
    }

    for (auto next_state = state; next_state > 0; --next_state) {
        const auto next_state_minus_1 = next_state - 1;
        if (pattern[next_state_minus_1] == c) {
            std::string::size_type i = 0;
            for (; i < next_state_minus_1; ++i) {
                if (pattern[i] != pattern[state - next_state_minus_1 + i]) {
                    break;
                }
            }

            if (i == next_state_minus_1) {
                return next_state;
            }
        }
    }

    return 0;
}

auto createTransitionFunctionTable(const std::string &pattern, const int RADIX_D) {
    std::vector<ArrayType>
    transition_fucntion_table(pattern.size() + 1, ArrayType(RADIX_D, 0));

    for (std::string::size_type state = 0; state <= pattern.size(); ++state) {
        for (int c = 0; c < RADIX_D; ++c) {
            transition_fucntion_table[state][c] = getNextState(pattern, state, c);
        }
    }

    return transition_fucntion_table;
}

/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 32.4-8.
 * @reference   Pattern Searching | Set 6 (Efficient Construction of Finite Automata)
 *              https://www.geeksforgeeks.org/pattern-searching-set-5-efficient-constructtion-of-finite-automata/
 */
auto createTransitionFunctionTable_Optimized(const std::string &pattern,
                                             const int RADIX_D) {
    std::vector<ArrayType>
    transition_fucntion_table(pattern.size() + 1, ArrayType(RADIX_D, 0));
    transition_fucntion_table[0][pattern[0]] = 1;

    std::string::size_type longest_prefix_suffix = 0;
    for (std::string::size_type i = 1; i <= pattern.size(); ++i) {
        for (int j = 0; j < RADIX_D; ++j) {
            transition_fucntion_table[i][j] = transition_fucntion_table[longest_prefix_suffix][j];
        }

        transition_fucntion_table[i][pattern[i]] = i + 1;

        if (i < pattern.size()) {
            longest_prefix_suffix = transition_fucntion_table[longest_prefix_suffix][pattern[i]];
        }
    }

    return transition_fucntion_table;
}

template <typename TransitionTableCreator>
auto StringMatcing_FiniteAutomata(const TransitionTableCreator transition_table_creator,
                                  const std::string &text, const std::string &pattern) {
    assert(text.size() >= pattern.size());

    const int RADIX_D = 256;
    const auto TRANSITION_FUCNTION_TABLE = transition_table_creator(pattern, RADIX_D);

    ArrayType shifts;
    unsigned state = 0;
    for (std::string::size_type i = 0; i < text.size(); ++i) {
        state = TRANSITION_FUCNTION_TABLE[state][text[i]];
        if (state == pattern.size()) {
            shifts.push_back(i + 1 - pattern.size());
        }
    }

    return shifts;
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 32.4.
 * @reference   KMP Algorithm for Pattern Searching
 *              https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/
 */
auto computeLongestPrefixSuffix(const std::string &pattern) {
    ArrayType longest_prefix_suffix = {0};
    std::string::size_type number_chars_matched = 0;

    for (std::string::size_type i = 1; i < pattern.size(); ++i) {
        while (number_chars_matched > 0 and pattern[number_chars_matched] != pattern[i]) {
            number_chars_matched = longest_prefix_suffix[number_chars_matched - 1];
        }

        if (pattern[number_chars_matched] == pattern[i]) {
            ++number_chars_matched;
        }

        longest_prefix_suffix.push_back(number_chars_matched);
    }

    return longest_prefix_suffix;
}

auto StringMatcing_KMP(const std::string &text, const std::string &pattern) {
    assert(text.size() >= pattern.size());

    ArrayType shifts;
    const auto LONGEST_PREFIX_SUFFIX = computeLongestPrefixSuffix(pattern);
    std::string::size_type number_chars_matched = 0;
    for (std::string::size_type i = 0; i < text.size(); ++i) {
        while (number_chars_matched > 0 and pattern[number_chars_matched] != text[i]) {
            number_chars_matched = LONGEST_PREFIX_SUFFIX[number_chars_matched - 1];
        }

        if (pattern[number_chars_matched] == text[i]) {
            ++number_chars_matched;
        }

        if (number_chars_matched == pattern.size()) {
            shifts.push_back(i + 1 - pattern.size());
            number_chars_matched = LONGEST_PREFIX_SUFFIX.back();
        }
    }

    return shifts;
}


/**
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Exercises 32.4-7.
 * @reference   A Program to check if strings are rotations of each other or not
 *              https://www.geeksforgeeks.org/a-program-to-check-if-strings-are-rotations-of-each-other/
 * @reference   Check if strings are rotations of each other or not | Set 2
 *              https://www.geeksforgeeks.org/check-strings-rotations-not-set-2/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 1.8.
 *
 * Given a string s1 and a string s2, write a snippet to say whether s2 is a rotation
 * of s1?
 *
 * @reference   Pattern Searching using C++ library
 *              https://www.geeksforgeeks.org/pattern-searching-using-c-library/
 */
auto AreRotations(const std::string &lhs, const std::string &rhs) {
    if (lhs.size() != rhs.size()) {
        return false;
    }

    const auto concatenation = lhs + lhs;
    return concatenation.find(rhs) != std::string::npos;
}


/**
 * @reference   Check if two numbers are bit rotations of each other or not
 *              https://www.geeksforgeeks.org/check-two-numbers-bit-rotations-not/
 */
auto AreBitsRotations(const uint32_t lhs, const uint32_t rhs) {
    for (auto concatenation = lhs | (static_cast<uint64_t>(lhs) << 32);
         concatenation >= rhs; concatenation >>= 1) {
        if (static_cast<uint32_t>(concatenation) == rhs) {
            return true;
        }
    }

    return false;
}

}//namespace


const ArrayType EXPECTED1 = {0, 9, 12};
const ArrayType EXPECTED2 = {10};
const ArrayType EXPECTED3 = {4, 12};
const ArrayType EXPECTED4 = {0, 10};
const ArrayType EXPECTED6 = {8};


THE_BENCHMARK(StringMatcing_Naive, "AABAACAADAABAABA", "AABA");

SIMPLE_TEST(StringMatcing_Naive, TestSAMPLE1, EXPECTED1, "AABAACAADAABAABA", "AABA");
SIMPLE_TEST(StringMatcing_Naive, TestSAMPLE2, EXPECTED2, "THIS IS A TEST TEXT", "TEST");
SIMPLE_TEST(StringMatcing_Naive, TestSAMPLE3, EXPECTED3, "ABCEABCDABCEABCD", "ABCD");
SIMPLE_TEST(StringMatcing_Naive, TestSAMPLE4, EXPECTED4, "GEEKS FOR GEEKS", "GEEKS");
SIMPLE_TEST(StringMatcing_Naive, TestSAMPLE5, EXPECTED2,
            "ABABDABACDABABCABAB", "ABABCABAB");
SIMPLE_TEST(StringMatcing_Naive, TestSAMPLE6, EXPECTED6, "cabababcababaca", "ababaca");


THE_BENCHMARK(StringMatcing_OptimizedNaive, "ABCEABCDABCEABCD", "ABCD");

SIMPLE_TEST(StringMatcing_OptimizedNaive, TestSAMPLE3, EXPECTED3,
            "ABCEABCDABCEABCD", "ABCD");


THE_BENCHMARK(StringMatcing_RabinKarp, "AABAACAADAABAABA", "AABA");

SIMPLE_TEST(StringMatcing_RabinKarp, TestSAMPLE1, EXPECTED1,
            "AABAACAADAABAABA", "AABA");
SIMPLE_TEST(StringMatcing_RabinKarp, TestSAMPLE2, EXPECTED2,
            "THIS IS A TEST TEXT", "TEST");
SIMPLE_TEST(StringMatcing_RabinKarp, TestSAMPLE3, EXPECTED3,
            "ABCEABCDABCEABCD", "ABCD");
SIMPLE_TEST(StringMatcing_RabinKarp, TestSAMPLE4, EXPECTED4,
            "GEEKS FOR GEEKS", "GEEKS");
SIMPLE_TEST(StringMatcing_RabinKarp, TestSAMPLE5, EXPECTED2,
            "ABABDABACDABABCABAB", "ABABCABAB");
SIMPLE_TEST(StringMatcing_RabinKarp, TestSAMPLE6, EXPECTED6,
            "cabababcababaca", "ababaca");


SIMPLE_BENCHMARK(StringMatcing_FiniteAutomata, BMSampleA1,
                 createTransitionFunctionTable, "AABAACAADAABAABA", "AABA");

SIMPLE_TEST(StringMatcing_FiniteAutomata, TestSAMPLE1a, EXPECTED1,
            createTransitionFunctionTable, "AABAACAADAABAABA", "AABA");
SIMPLE_TEST(StringMatcing_FiniteAutomata, TestSAMPLE2a, EXPECTED2,
            createTransitionFunctionTable, "THIS IS A TEST TEXT", "TEST");
SIMPLE_TEST(StringMatcing_FiniteAutomata, TestSAMPLE3a, EXPECTED3,
            createTransitionFunctionTable, "ABCEABCDABCEABCD", "ABCD");
SIMPLE_TEST(StringMatcing_FiniteAutomata, TestSAMPLE4a, EXPECTED4,
            createTransitionFunctionTable, "GEEKS FOR GEEKS", "GEEKS");
SIMPLE_TEST(StringMatcing_FiniteAutomata, TestSAMPLE5a, EXPECTED2,
            createTransitionFunctionTable, "ABABDABACDABABCABAB", "ABABCABAB");
SIMPLE_TEST(StringMatcing_FiniteAutomata, TestSAMPLE6a, EXPECTED6,
            createTransitionFunctionTable, "cabababcababaca", "ababaca");


SIMPLE_BENCHMARK(StringMatcing_FiniteAutomata, BMSampleB1,
                 createTransitionFunctionTable_Optimized, "AABAACAADAABAABA", "AABA");

SIMPLE_TEST(StringMatcing_FiniteAutomata, TestSAMPLE1b, EXPECTED1,
            createTransitionFunctionTable_Optimized, "AABAACAADAABAABA", "AABA");
SIMPLE_TEST(StringMatcing_FiniteAutomata, TestSAMPLE2b, EXPECTED2,
            createTransitionFunctionTable_Optimized, "THIS IS A TEST TEXT", "TEST");
SIMPLE_TEST(StringMatcing_FiniteAutomata, TestSAMPLE3b, EXPECTED3,
            createTransitionFunctionTable_Optimized, "ABCEABCDABCEABCD", "ABCD");
SIMPLE_TEST(StringMatcing_FiniteAutomata, TestSAMPLE4b, EXPECTED4,
            createTransitionFunctionTable_Optimized, "GEEKS FOR GEEKS", "GEEKS");
SIMPLE_TEST(StringMatcing_FiniteAutomata, TestSAMPLE5b, EXPECTED2,
            createTransitionFunctionTable_Optimized, "ABABDABACDABABCABAB", "ABABCABAB");
SIMPLE_TEST(StringMatcing_FiniteAutomata, TestSAMPLE6b, EXPECTED6,
            createTransitionFunctionTable_Optimized, "cabababcababaca", "ababaca");


THE_BENCHMARK(StringMatcing_KMP, "AABAACAADAABAABA", "AABA");

SIMPLE_TEST(StringMatcing_KMP, TestSAMPLE1, EXPECTED1, "AABAACAADAABAABA", "AABA");
SIMPLE_TEST(StringMatcing_KMP, TestSAMPLE2, EXPECTED2, "THIS IS A TEST TEXT", "TEST");
SIMPLE_TEST(StringMatcing_KMP, TestSAMPLE3, EXPECTED3, "ABCEABCDABCEABCD", "ABCD");
SIMPLE_TEST(StringMatcing_KMP, TestSAMPLE4, EXPECTED4, "GEEKS FOR GEEKS", "GEEKS");
SIMPLE_TEST(StringMatcing_KMP, TestSAMPLE5, EXPECTED2,
            "ABABDABACDABABCABAB", "ABABCABAB");
SIMPLE_TEST(StringMatcing_KMP, TestSAMPLE6, EXPECTED6, "cabababcababaca", "ababaca");


THE_BENCHMARK(AreRotations, "ABACD", "CDABA");

SIMPLE_TEST(AreRotations, TestSAMPLE1, true, "ABACD", "CDABA");
SIMPLE_TEST(AreRotations, TestSAMPLE2, true, "ABCD", "CDAB");
SIMPLE_TEST(AreRotations, TestSAMPLE3, false, "ABCD", "ACBD");


THE_BENCHMARK(AreBitsRotations, 122, 2147483678);

SIMPLE_TEST(AreBitsRotations, TestSAMPLE1, true, 122, 2147483678);
SIMPLE_TEST(AreBitsRotations, TestSAMPLE2, true, 1, 8);
SIMPLE_TEST(AreBitsRotations, TestSAMPLE3, false, 0b101, 0b111);
