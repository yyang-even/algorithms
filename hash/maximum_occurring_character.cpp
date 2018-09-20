#include "common_header.h"

/** Return maximum occurring character in an input string
 *
 * @reference   https://www.geeksforgeeks.org/return-maximum-occurring-character-in-the-input-string/
 *
 * Write an efficient function to return maximum occurring character in the input
 * string e.g., if input string is “test” then function should return ‘t’.
 */
auto MaximumOccurringChar(const std::string &input) {
    std::unordered_map<std::string::value_type, std::string::size_type> counters;

    for (const auto c : input) {
        ++counters[c];
    }

    std::string::size_type max = 0ul;
    std::string::value_type max_char = input.front();

    for (const auto count : counters) {
        if (count.second > max) {
            max_char = count.first;
            max = count.second;
        }
    }

    return max_char;
}


SIMPLE_BENCHMARK(MaximumOccurringChar, std::string("sample string"));

SIMPLE_TEST(MaximumOccurringChar, TestSAMPLE1, 's', std::string("sample string"));
SIMPLE_TEST(MaximumOccurringChar, TestSAMPLE2, 't', std::string("test"));
