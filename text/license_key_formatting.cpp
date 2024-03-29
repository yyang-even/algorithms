#include "common_header.h"

#include <regex>


namespace {

/** License Key Formatting
 *
 * @reference   https://leetcode.com/problems/license-key-formatting/
 *
 * You are given a license key represented as a string s that consists of only
 * alphanumeric characters and dashes. The string is separated into n + 1 groups by n
 * dashes. You are also given an integer k. We want to reformat the string s such that
 * each group contains exactly k characters, except for the first group, which could be
 * shorter than k but still must contain at least one character. Furthermore, there must
 * be a dash inserted between two groups, and you should convert all lowercase letters
 * to uppercase. Return the reformatted license key.
 */
auto LicenseKeyFormatting(const std::string_view s, const int K) {
    std::string result;
    int count = 0;
    for (int i = s.size() - 1; i >= 0; --i) {
        if (s[i] != '-') {
            if (count++ % K == 0) {
                result.push_back('-');
            }
            result.push_back(std::toupper(s[i]));
        }
    }

    std::reverse(result.begin(), result.end());
    if (not result.empty()) {
        result.pop_back();
    }
    return result;
}


/**
 * @reference   Reformat Phone Number
 *              https://leetcode.com/problems/reformat-phone-number/
 *
 * You are given a phone number as a string number. number consists of digits, spaces ' ',
 * and/or dashes '-'.
 * You would like to reformat the phone number in a certain manner. Firstly, remove all
 * spaces and dashes. Then, group the digits from left to right into blocks of length 3
 * until there are 4 or fewer digits. The final digits are then grouped as follows:
 *  2 digits: A single block of length 2.
 *  3 digits: A single block of length 3.
 *  4 digits: Two blocks of length 2 each.
 * The blocks are then joined by dashes. Notice that the reformatting process should
 * never produce any blocks of length 1 and produce at most two blocks of length 2.
 * Return the phone number after formatting.
 * There are at least two digits in number.
 */
auto ReformatPhoneNumber_Regex(std::string number) {
    number.erase(std::remove_if(number.begin(), number.end(),
                                ToNegationLambda(std::isdigit)),
                 number.end());
    return std::regex_replace(number, std::regex("...?(?=..)"), "$0-");
}


std::string ReformatPhoneNumber_Recursive_Helper(const std::string &number) {
    if (number.size() >= 4) {
        const auto take = number.size() > 4 ? 3 : 2;
        return number.substr(0, take) + "-" +
               ReformatPhoneNumber_Recursive_Helper(number.substr(take));
    }

    return number;
}

auto ReformatPhoneNumber_Recursive(std::string number) {
    number.erase(std::remove_if(number.begin(), number.end(),
                                ToNegationLambda(std::isdigit)),
                 number.end());
    return ReformatPhoneNumber_Recursive_Helper(number);
}


auto ReformatPhoneNumber_Iterative(std::string number) {
    const auto end = std::remove_if(number.begin(), number.end(),
                                    ToNegationLambda(std::isdigit));

    const int size = end - number.cbegin();
    std::string result;
    for (int i = 0; i < size;) {
        if (not result.empty()) {
            result.push_back('-');
        }

        const auto digits_left = size - i;
        if (digits_left == 4) {
            result += number.substr(i, 2) + '-' + number.substr(i + 2, 2);
            break;
        } else if (digits_left < 4) {
            result += number.substr(i, digits_left);
            break;
        } else {
            result += number.substr(i, 3);
            i += 3;
        }
    }

    return result;
}


/**
 * @reference   Number of Valid Words in a Sentence
 *              https://leetcode.com/problems/number-of-valid-words-in-a-sentence/
 *
 * A sentence consists of lowercase letters ('a' to 'z'), digits ('0' to '9'), hyphens
 * ('-'), punctuation marks ('!', '.', and ','), and spaces (' ') only. Each sentence can
 * be broken down into one or more tokens separated by one or more spaces ' '.
 * A token is a valid word if all three of the following are true:
 *  It only contains lowercase letters, hyphens, and/or punctuation (no digits).
 *  There is at most one hyphen '-'. If present, it must be surrounded by lowercase
 *      characters ("a-b" is valid, but "-ab" and "ab-" are not valid).
 *  There is at most one punctuation mark. If present, it must be at the end of the token
 *      ("ab,", "cd!", and "." are valid, but "a!b" and "c.," are not valid).
 * Examples of valid words include "a-b.", "afad", "ba-c", "a!", and "!".
 * Given a string sentence, return the number of valid words in sentence.
 */
auto CountValidWords(const std::string &sentence) {
    const std::regex pattern("(^[a-z]+(-[a-z]+)?)?[,.!]?$");

    int result = 0;
    std::stringstream ss(sentence);
    for (std::string word; ss >> word;) {
        if (std::regex_match(word, pattern)) {
            ++result;
        }
    }

    return result;
}


/**
 * @reference   Divide a String Into Groups of Size k
 *              https://leetcode.com/problems/divide-a-string-into-groups-of-size-k/
 *
 * A string s can be partitioned into groups of size k using the following procedure:
 *  The first group consists of the first k characters of the string, the second group
 *      consists of the next k characters of the string, and so on. Each character can be
 *      a part of exactly one group.
 *  For the last group, if the string does not have k characters remaining, a character
 *      fill is used to complete the group.
 * Note that the partition is done so that after removing the fill character from the last
 * group (if it exists) and concatenating all the groups in order, the resultant string
 * should be s.
 * Given the string s, the size of each group k and the character fill, return a string
 * array denoting the composition of every group s has been divided into, using the above
 * procedure.
 */

}//namespace


THE_BENCHMARK(LicenseKeyFormatting, "5F3Z-2e-9-w", 4);

SIMPLE_TEST(LicenseKeyFormatting, TestSAMPLE1, "5F3Z-2E9W", "5F3Z-2e-9-w", 4);
SIMPLE_TEST(LicenseKeyFormatting, TestSAMPLE2, "2-5G-3J", "2-5g-3-J", 2);


THE_BENCHMARK(ReformatPhoneNumber_Regex, "1-23-45 6");

SIMPLE_TEST(ReformatPhoneNumber_Regex, TestSAMPLE1, "123-456", "1-23-45 6");
SIMPLE_TEST(ReformatPhoneNumber_Regex, TestSAMPLE2, "123-45-67", "123 4-567");
SIMPLE_TEST(ReformatPhoneNumber_Regex, TestSAMPLE3, "123-456-78", "123 4-5678");


THE_BENCHMARK(ReformatPhoneNumber_Recursive, "1-23-45 6");

SIMPLE_TEST(ReformatPhoneNumber_Recursive, TestSAMPLE1, "123-456", "1-23-45 6");
SIMPLE_TEST(ReformatPhoneNumber_Recursive, TestSAMPLE2, "123-45-67", "123 4-567");
SIMPLE_TEST(ReformatPhoneNumber_Recursive, TestSAMPLE3, "123-456-78", "123 4-5678");


THE_BENCHMARK(ReformatPhoneNumber_Iterative, "1-23-45 6");

SIMPLE_TEST(ReformatPhoneNumber_Iterative, TestSAMPLE1, "123-456", "1-23-45 6");
SIMPLE_TEST(ReformatPhoneNumber_Iterative, TestSAMPLE2, "123-45-67", "123 4-567");
SIMPLE_TEST(ReformatPhoneNumber_Iterative, TestSAMPLE3, "123-456-78", "123 4-5678");


THE_BENCHMARK(CountValidWords, "cat and  dog");

SIMPLE_TEST(CountValidWords, TestSAMPLE1, 3, "cat and  dog");
SIMPLE_TEST(CountValidWords, TestSAMPLE2, 0, "!this  1-s b8d!");
SIMPLE_TEST(CountValidWords, TestSAMPLE3, 5, "alice and  bob are playing stone-game10");
