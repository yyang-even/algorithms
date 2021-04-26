#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;
using ResultType = std::unordered_multiset<std::string>;

/** Print all possible words from phone digits
 *
 * @reference   https://www.geeksforgeeks.org/find-possible-words-phone-digits/
 *
 * Given a keypad as shown in the diagram, and an n digit number, list all
 * words which are possible by pressing these numbers.
 *
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 7.
 */
const std::vector<std::string_view> CharKeys = { "0",    "1",    "abc",  "def", "ghi",
                                                 "jkl", "mno", "pqrs", "tuv", "wxyz"
                                               };

void AllPossibleWordsFromPhoneDigits_Recursive(const ArrayType &phone_digits,
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

auto AllPossibleWordsFromPhoneDigits_Recursive(const ArrayType &phone_digits) {
    std::string one_word;
    ResultType results;
    AllPossibleWordsFromPhoneDigits_Recursive(phone_digits, one_word, results);

    return results;
}


auto AllPossibleWordsFromPhoneDigits_Iterative(const ArrayType &phone_digits) {
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

            const auto &current_char_keys =  CharKeys[phone_digits[i]];
            if (one_word[i] == current_char_keys.back()) {
                one_word[i] = current_char_keys.front();
            } else {
                ++one_word[i];
                break;
            }
        }
    }
}

}//namespace


const ArrayType SAMPLE1 = {2, 3, 4};
const ResultType EXPECTED1 = {"adg", "adh", "adi", "aeg", "aeh", "aei", "afg", "afh", "afi",
                              "bdg", "bdh", "bdi", "beg", "beh", "bei", "bfg", "bfh", "bfi",
                              "cdg", "cdh", "cdi", "ceg", "ceh", "cei", "cfg", "cfh", "cfi"
                             };


THE_BENCHMARK(AllPossibleWordsFromPhoneDigits_Recursive, SAMPLE1);

SIMPLE_TEST(AllPossibleWordsFromPhoneDigits_Recursive, TestSAMPLE1, EXPECTED1, SAMPLE1);


THE_BENCHMARK(AllPossibleWordsFromPhoneDigits_Iterative, SAMPLE1);

SIMPLE_TEST(AllPossibleWordsFromPhoneDigits_Iterative, TestSAMPLE1, EXPECTED1, SAMPLE1);
