#include "common_header.h"


/** Given a string, find its first non-repeating character
 *
 * @reference   https://www.geeksforgeeks.org/given-a-string-find-its-first-non-repeating-character/
 *
 * Given a string, find the first non-repeating character in it. For example, if the
 * input string is “GeeksforGeeks”, then output should be ‘f’ and if input string is
 * “GeeksQuiz”, then output should be ‘G’.
 */
auto FindFirstNonrepeatingChar(const std::string &input) {
    std::unordered_map<std::string::value_type, std::string::size_type> counters;
    auto first_nonrepeated_index = input.size();

    for (std::string::size_type i = 0ul; i < input.size(); ++i) {
        const auto c = input[i];
        auto iter = counters.find(c);
        if (iter == counters.cend()) {
            counters.emplace(c, i);
        } else {
            iter->second = input.size();
        }
    }
    for (const auto elem : counters) {
        if (elem.second != input.size() and elem.second < first_nonrepeated_index) {
            first_nonrepeated_index = elem.second;
        }
    }

    return input[first_nonrepeated_index];
}


SIMPLE_BENCHMARK(FindFirstNonrepeatingChar, std::string("GeeksforGeeks"));

SIMPLE_TEST(FindFirstNonrepeatingChar, TestSAMPLE1, 'f', std::string("GeeksforGeeks"));
SIMPLE_TEST(FindFirstNonrepeatingChar, TestSAMPLE2, 'G', std::string("GeeksQuiz"));
SIMPLE_TEST(FindFirstNonrepeatingChar, TestSAMPLE3, 'd', std::string("aabbccd"));
