#include "common_header.h"


namespace {

/** Program to find second most frequent character
 *
 * @reference   https://www.geeksforgeeks.org/c-program-find-second-frequent-character/
 *
 * Given a string, find the second most frequent character in it. Expected
 * time complexity is O(n) where n is the length of the input string.
 */
auto FindSecondFrequentChar(const std::string &input) {
    assert(input.size() > 1ul);

    std::unordered_map<std::string::value_type, std::string::size_type> counters;

    for (const auto c : input) {
        ++counters[c];
    }

    std::string::size_type first_frequency = 0ul, second_frequency = 0ul;
    std::string::value_type first{}, second{};
    for (const auto &elem : counters) {
        if (elem.second > first_frequency) {
            second_frequency = first_frequency;
            second = first;
            first_frequency = elem.second;
            first = elem.first;
        } else if (elem.second > second_frequency) {
            second_frequency = elem.second;
            second = elem.first;
        }
    }

    return second;
}

}//namespace


SIMPLE_BENCHMARK(FindSecondFrequentChar, "geeksforgee");

SIMPLE_TEST(FindSecondFrequentChar, TestSAMPLE1, 'g', "geeksforgee");
SIMPLE_TEST(FindSecondFrequentChar, TestSAMPLE2, 'b', "aabababa");
