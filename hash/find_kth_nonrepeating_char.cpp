#include "common_header.h"


namespace {

/** K’th Non-repeating Character
 *
 * @reference   https://www.geeksforgeeks.org/kth-non-repeating-character/
 *
 * Given a string and a number k, find the k'th non-repeating character in the string.
 * Consider a large input string with lots of characters and a small character set. How
 * to find the character by only doing only one traversal of input string?
 */
auto FindKthNonrepeatingChar(const std::string_view input, const std::size_t K) {
    std::unordered_map<char, std::size_t> counters;

    for (std::string::size_type i = 0; i < input.size(); ++i) {
        const auto c = input[i];
        if (const auto [iter, inserted] = counters.emplace(c, i); not inserted) {
            iter->second = input.size();
        }
    }

    std::vector<std::size_t> nonrepeating_char_indice;
    for (const auto [_, index] : counters) {
        if (index != input.size()) {
            nonrepeating_char_indice.push_back(index);
        }
    }

    std::nth_element(nonrepeating_char_indice.begin(),
                     nonrepeating_char_indice.begin() + K - 1,
                     nonrepeating_char_indice.end());

    return input[nonrepeating_char_indice[K - 1]];
}

}//namespace


THE_BENCHMARK(FindKthNonrepeatingChar, "GeeksforGeeks", 3);

SIMPLE_TEST(FindKthNonrepeatingChar, TestSAMPLE1, 'r', "GeeksforGeeks", 3);
SIMPLE_TEST(FindKthNonrepeatingChar, TestSAMPLE2, 'o', "GeeksforGeeks", 2);
