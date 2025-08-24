#include "common_header.h"


namespace {

using ArrayType = std::vector<std::string_view>;
using OutputType = std::unordered_multiset<std::string>;
using DictType = std::unordered_set<std::string_view>;

/**
 * @reference   Word Break
 *              https://leetcode.com/problems/word-break/
 *
 * Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a
 * space-separated sequence of one or more dictionary words.
 * Note that the same word in the dictionary may be reused multiple times in the segmentation.
 *
 * @reference   Word Break Problem | DP-32
 *              https://www.geeksforgeeks.org/word-break-problem-dp-32/
 *
 * Given an input string and a dictionary of words, find out if the input string can be segmented into a
 * space-separated sequence of dictionary words.
 *
 * @tags    #DP
 */
bool WordBreak(const std::string_view s, const ArrayType &wordDict) {
    std::unordered_set<std::string_view> dictionary(wordDict.cbegin(), wordDict.cend());

    std::vector<bool> dp(s.size() + 1, false);
    dp[0] = true;

    for (std::size_t i = 1; i <= s.size(); ++i) {
        for (int j = i - 1; j >= 0; --j) {
            if (dp[j]) {
                const auto word = s.substr(j, i - j);
                if (dictionary.find(word) != dictionary.cend()) {
                    dp[i] = true;
                    break;
                }
            }
        }
    }

    return dp[s.size()];
}


/**
 * @reference   Word Break Problem | (Trie solution)
 *              https://www.geeksforgeeks.org/word-break-problem-trie-solution/
 *
 * @note    This solution replaces unordered_set with Trie.
 *
 * @tags    #trie
 */


/**
 * @reference   Word Break Problem using Backtracking
 *              https://www.geeksforgeeks.org/word-break-problem-using-backtracking/
 *
 * Given a valid sentence without any spaces between the words and a dictionary of valid English words,
 * find all possible ways to break the sentence in individual dictionary words.
 *
 * @tags    #backtracking
 */
void AllWayToWordBreak(const std::string &a_string,
                       const DictType &words,
                       const std::string &prefix,
                       OutputType &results) {
    for (std::size_t i = 1; i <= a_string.size(); ++i) {
        const auto substring = a_string.substr(0, i);
        if (words.find(substring) != words.cend()) {
            const auto new_prefix = prefix + substring;
            if (i == a_string.size()) {
                results.insert(new_prefix);
            } else {
                AllWayToWordBreak(
                    a_string.substr(i, a_string.size() - i), words, new_prefix + " ", results);
            }
        }
    }
}

inline auto AllWayToWordBreak(const std::string &a_string, const ArrayType &words) {
    std::unordered_set<std::string_view> dictionary(words.cbegin(), words.cend());

    OutputType results;
    AllWayToWordBreak(a_string, dictionary, "", results);
    return results;
}


/**
 * @reference   Minimum Word Break
 *              https://www.geeksforgeeks.org/minimum-word-break/
 *
 * Given a string s, break s such that every substring of the partition can be found in the dictionary.
 * Return the minimum break needed.
 *
 * @tags    #DP
 */
bool MinimumWordBreak(const std::string_view a_string, const DictType &words) {
    std::vector<int> word_breaks(a_string.size() + 1, 0);
    word_breaks[0] = 1;

    for (std::size_t i = 0; i <= a_string.size(); ++i) {
        if (word_breaks[i]) {
            const auto number_breaks = word_breaks[i] + 1;
            for (auto j = i; j <= a_string.size(); ++j) {
                if (words.find(a_string.substr(i, j - i)) != words.cend()) {
                    if ((not word_breaks[j]) or (word_breaks[i] + 1 < word_breaks[j])) {
                        word_breaks[j] = number_breaks;
                    }
                }
            }
        }
    }

    return word_breaks[a_string.size()] - 1;
}


/**
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 17.14.
 *
 * Given a dictionary (a list of words), design an algorithm to find the optimal way of "unconcatenating"
 * a sequence of words. In this case, "optimal" is defined to be the parsing which minimizes the number
 * of unrecognized sequences of characters.
 *
 * @tags    #DP
 */


/**
 * @reference   Restore IP Addresses
 *              https://leetcode.com/problems/restore-ip-addresses/
 *
 * A valid IP address consists of exactly four integers separated by single dots. Each integer is
 * between 0 and 255 (inclusive) and cannot have leading zeros.
 *  For example, "0.1.2.201" and "192.168.1.1" are valid IP addresses, but "0.011.255.245",
 *  "192.168.1.312" and "192.168@1.1" are invalid IP addresses.
 * Given a string s containing only digits, return all possible valid IP addresses that can be formed by
 * inserting dots into s. You are not allowed to reorder or remove any digits in s. You may return the
 * valid IP addresses in any order.
 *
 * @tags    #backtracking
 */
void RestoreIPAddresses(const std::string_view ip,
                        const std::size_t start,
                        std::string prefix,
                        const int group,
                        OutputType &results) {
    if (group > 4)
        return;
    if (group == 4 and start == ip.size()) {
        prefix.pop_back();
        results.insert(prefix);
    }

    if (ip[start] == '0') {
        RestoreIPAddresses(ip, start + 1, prefix + ip[start] + '.', group + 1, results);
    } else {
        int v = 0;
        for (auto i = start; i < ip.size(); ++i) {
            v = v * 10 + ip[i] - '0';
            if (v > 255) {
                break;
            }

            prefix.push_back(ip[i]);
            RestoreIPAddresses(ip, i + 1, prefix + '.', group + 1, results);
        }
    }
}

inline auto RestoreIPAddresses(const std::string_view ip) {
    OutputType results;
    RestoreIPAddresses(ip, 0, "", 0, results);

    return results;
}

} //namespace


const ArrayType SAMPLE1 = {"mobile",
                           "samsung",
                           "sam",
                           "sung",
                           "man",
                           "mango",
                           "icecream",
                           "and",
                           "go",
                           "i",
                           "like",
                           "ice",
                           "cream"};
const ArrayType SAMPLE7 = {"leet", "code"};
const ArrayType SAMPLE8 = {"apple", "pen"};
const ArrayType SAMPLE9 = {"cats", "dog", "sand", "and", "cat"};


THE_BENCHMARK(WordBreak, "leetcode", SAMPLE7);

SIMPLE_TEST(WordBreak, TestSAMPLE0, true, "", SAMPLE1);
SIMPLE_TEST(WordBreak, TestSAMPLE1, true, "ilike", SAMPLE1);
SIMPLE_TEST(WordBreak, TestSAMPLE2, true, "ilikesamsung", SAMPLE1);
SIMPLE_TEST(WordBreak, TestSAMPLE3, true, "iiiiiiii", SAMPLE1);
SIMPLE_TEST(WordBreak, TestSAMPLE4, true, "ilikelikeimangoiii", SAMPLE1);
SIMPLE_TEST(WordBreak, TestSAMPLE5, true, "samsungandmango", SAMPLE1);
SIMPLE_TEST(WordBreak, TestSAMPLE6, false, "samsungandmangok", SAMPLE1);
SIMPLE_TEST(WordBreak, TestSAMPLE7, true, "leetcode", SAMPLE7);
SIMPLE_TEST(WordBreak, TestSAMPLE8, true, "applepenapple", SAMPLE8);
SIMPLE_TEST(WordBreak, TestSAMPLE9, false, "catsandog", SAMPLE9);


const OutputType EXPECTED1 = {"i like ice cream and man go",
                              "i like ice cream and mango",
                              "i like icecream and man go",
                              "i like icecream and mango"};

const OutputType EXPECTED2 = {"i like sam sung mobile", "i like samsung mobile"};


THE_BENCHMARK(AllWayToWordBreak, "ilikeicecreamandmango", SAMPLE1);

SIMPLE_TEST(AllWayToWordBreak, TestSAMPLE1, EXPECTED1, "ilikeicecreamandmango", SAMPLE1);
SIMPLE_TEST(AllWayToWordBreak, TestSAMPLE2, EXPECTED2, "ilikesamsungmobile", SAMPLE1);


const DictType DICTIONARY2 = {"Cat", "Mat", "Ca", "tM", "at", "C", "Dog", "og", "Do"};


THE_BENCHMARK(MinimumWordBreak, "CatMat", DICTIONARY2);

SIMPLE_TEST(MinimumWordBreak, TestSAMPLE0, 0, "", DICTIONARY2);
SIMPLE_TEST(MinimumWordBreak, TestSAMPLE1, 1, "CatMat", DICTIONARY2);
SIMPLE_TEST(MinimumWordBreak, TestSAMPLE2, 2, "CatMatat", DICTIONARY2);
SIMPLE_TEST(MinimumWordBreak, TestSAMPLE3, -1, "samsungandmangok", DICTIONARY2);


const OutputType EXPECTED1I = {"255.255.11.135", "255.255.111.35"};
const OutputType EXPECTED2I = {"0.0.0.0"};
const OutputType EXPECTED3I = {"1.0.10.23", "1.0.102.3", "10.1.0.23", "10.10.2.3", "101.0.2.3"};


THE_BENCHMARK(RestoreIPAddresses, "101023");

SIMPLE_TEST(RestoreIPAddresses, TestSAMPLE1, EXPECTED1I, "25525511135");
SIMPLE_TEST(RestoreIPAddresses, TestSAMPLE2, EXPECTED2I, "0000");
SIMPLE_TEST(RestoreIPAddresses, TestSAMPLE3, EXPECTED3I, "101023");
