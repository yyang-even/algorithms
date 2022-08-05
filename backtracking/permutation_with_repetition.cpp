#include "common_header.h"


namespace {

using ArrayType = std::vector<std::string>;
using InputType = std::vector<int>;
using ResultType = std::unordered_multiset<std::string>;

/** Print all permutations with repetition of characters
 *
 * @reference   https://www.geeksforgeeks.org/print-all-permutations-with-repetition-of-characters/
 *
 * Given a string of length n, print all permutation of the given string. Repetition of characters
 * is allowed. Print these permutations in lexicographically sorted order.
 */
void PermutationWithRepetitionHelper(const std::string &input,
                                     const std::string &buffer,
                                     const std::string::iterator buffer_iter,
                                     ArrayType &outputs) {
    for (const auto c : input) {
        *buffer_iter = c;

        const auto next = std::next(buffer_iter);
        if (next == buffer.end()) {
            outputs.push_back(buffer);
        } else {
            PermutationWithRepetitionHelper(input, buffer, next, outputs);
        }
    }
}

auto PermutationWithRepetition(std::string input) {
    std::sort(input.begin(), input.end());

    ArrayType outputs;
    auto buffer = input;

    PermutationWithRepetitionHelper(input, buffer, buffer.begin(), outputs);

    return outputs;
}


/** Print all possible words from phone digits
 *
 * @reference   https://www.geeksforgeeks.org/find-possible-words-phone-digits/
 *
 * Given a keypad as shown in the diagram, and an n digit number, list all words which are possible
 * by pressing these numbers.
 *
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 7.
 *
 * @reference   Letter Combinations of a Phone Number
 *              https://leetcode.com/problems/letter-combinations-of-a-phone-number/
 *
 * Given a string containing digits from 2-9 inclusive, return all possible letter combinations
 * that the number could represent. Return the answer in any order.
 * A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1
 * does not map to any letters.
 */
const std::vector<std::string_view> CharKeys = {
    "0", "1", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

void AllPossibleWordsFromPhoneDigits_Recursive(const InputType &phone_digits,
                                               std::string &one_word,
                                               ResultType &results) {
    if (one_word.size() == phone_digits.size()) {
        results.insert(one_word);
        return;
    }

    const auto current_digit = phone_digits[one_word.size()];
    for (const auto c : CharKeys[current_digit]) {
        one_word.push_back(c);
        AllPossibleWordsFromPhoneDigits_Recursive(phone_digits, one_word, results);
        one_word.pop_back();
    }
}

inline auto AllPossibleWordsFromPhoneDigits_Recursive(const InputType &phone_digits) {
    std::string one_word;
    ResultType results;
    AllPossibleWordsFromPhoneDigits_Recursive(phone_digits, one_word, results);

    return results;
}


auto AllPossibleWordsFromPhoneDigits_Iterative(const InputType &phone_digits) {
    std::string one_word;
    for (const auto digit : phone_digits) {
        one_word.push_back(CharKeys[digit].front());
    }

    ResultType results;
    while (true) {
        results.insert(one_word);

        for (int i = phone_digits.size() - 1; i >= -1; --i) {
            if (i == -1) {
                return results;
            }

            const auto current_char_keys = CharKeys[phone_digits[i]];
            if (one_word[i] == current_char_keys.back()) {
                one_word[i] = current_char_keys.front();
            } else {
                ++one_word[i];
                break;
            }
        }
    }
}

} //namespace


const ArrayType EXPECTED1 = {"aaa", "aab", "aac", "aba", "abb", "abc", "aca", "acb", "acc",
                             "baa", "bab", "bac", "bba", "bbb", "bbc", "bca", "bcb", "bcc",
                             "caa", "cab", "cac", "cba", "cbb", "cbc", "cca", "ccb", "ccc"};


THE_BENCHMARK(PermutationWithRepetition, "ab4c12ed3");

SIMPLE_TEST(PermutationWithRepetition, TestSAMPLE1, EXPECTED1, "abc");


const InputType SAMPLE1P = {2, 3, 4};
const ResultType EXPECTED1P = {"adg", "adh", "adi", "aeg", "aeh", "aei", "afg", "afh", "afi",
                               "bdg", "bdh", "bdi", "beg", "beh", "bei", "bfg", "bfh", "bfi",
                               "cdg", "cdh", "cdi", "ceg", "ceh", "cei", "cfg", "cfh", "cfi"};


THE_BENCHMARK(AllPossibleWordsFromPhoneDigits_Recursive, SAMPLE1P);

SIMPLE_TEST(AllPossibleWordsFromPhoneDigits_Recursive, TestSAMPLE1, EXPECTED1P, SAMPLE1P);


THE_BENCHMARK(AllPossibleWordsFromPhoneDigits_Iterative, SAMPLE1P);

SIMPLE_TEST(AllPossibleWordsFromPhoneDigits_Iterative, TestSAMPLE1, EXPECTED1P, SAMPLE1P);
