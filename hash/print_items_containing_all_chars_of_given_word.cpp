#include "common_header.h"

#include "hash/hash.h"


namespace {

using ArrayType = std::vector<std::string_view>;

/** Print list items containing all characters of a given word
 *
 * @reference   https://www.geeksforgeeks.org/print-list-items-containing-all-characters-of-a-given-word/
 *
 * There is a list of items. Given a specific word, e.g., "sun", print out all the items
 * in list which contain all the characters of "sun". For example if the given word is
 * "sun" and the items are "sunday", "geeksforgeeks", "utensils", "just" and "sss", then
 * the program should print "sunday" and "utensils".
 */
auto ItemsContainingAllCharsOfGivenWord(const ArrayType &items,
                                        const std::string_view word) {
    const auto counters = ToFrequencyHashTable(word);

    ArrayType output;
    for (const auto item : items) {
        auto length = word.size();
        auto temp_counters = counters;
        for (const auto c : item) {
            const auto iter = temp_counters.find(c);
            if (iter != temp_counters.cend() and iter->second != 0) {
                --(iter->second);
                if (not --length) {
                    output.push_back(item);
                    break;
                }
            }
        }
    }

    return output;
}

}//namespace


const ArrayType SAMPLE = {"geeksforgeeks", "unsorted", "sunday", "just", "sss"};
const ArrayType EXPECTED = {"unsorted", "sunday"};


THE_BENCHMARK(ItemsContainingAllCharsOfGivenWord, SAMPLE, "sun");

SIMPLE_TEST(ItemsContainingAllCharsOfGivenWord, TestSAMPLE1, EXPECTED, SAMPLE, "sun");
