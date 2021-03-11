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
auto FindSecondFrequentChar(const std::string &input) {
    assert(input.size() > 1ul);

    const auto counters = ToFrequencyHashTable(input);

    std::string::size_type first_frequency = 0ul, second_frequency = 0ul;
    std::string::value_type first{}, second{};
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


SIMPLE_BENCHMARK(FindSecondFrequentChar, Sample1, "geeksforgee");

SIMPLE_TEST(FindSecondFrequentChar, TestSAMPLE1, 'g', "geeksforgee");
SIMPLE_TEST(FindSecondFrequentChar, TestSAMPLE2, 'b', "aabababa");
