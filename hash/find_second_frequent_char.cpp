#include "common_header.h"

#include "hash/hash.h"


namespace {

/** Program to find second most frequent character
 *
 * @reference   https://www.geeksforgeeks.org/c-program-find-second-frequent-character/
 *
 * Given a string, find the second most frequent character in it. Expected time
 * complexity is O(n) where n is the length of the input string.
 */
auto FindSecondFrequentChar(const std::string_view input) {
    assert(input.size() > 1);

    const auto counters = ToFrequencyHashTable(input);

    std::size_t first_frequency = 0, second_frequency = 0;
    char first{}, second{};
    for (const auto [key, count] : counters) {
        if (count > first_frequency) {
            second_frequency = first_frequency;
            second = first;
            first_frequency = count;
            first = key;
        } else if (count > second_frequency) {
            second_frequency = count;
            second = key;
        }
    }

    return second;
}

}//namespace


THE_BENCHMARK(FindSecondFrequentChar, "geeksforgee");

SIMPLE_TEST(FindSecondFrequentChar, TestSAMPLE1, 'g', "geeksforgee");
SIMPLE_TEST(FindSecondFrequentChar, TestSAMPLE2, 'b', "aabababa");
