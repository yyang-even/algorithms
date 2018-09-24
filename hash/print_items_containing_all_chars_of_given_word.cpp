#include "common_header.h"


using ArrayType = std::vector<std::string>;
/** Print list items containing all characters of a given word
 *
 * @reference   https://www.geeksforgeeks.org/print-list-items-containing-all-characters-of-a-given-word/
 *
 * There is a list of items. Given a specific word, e.g., "sun", print out
 * all the items in list which contain all the characters of "sun".
 * For example if the given word is "sun" and the items are "sunday",
 * "geeksforgeeks", "utensils", "just" and "sss", then the program should
 * print "sunday" and "utensils".
 */
auto ItemsContainingAllCharsOfGivenWord(const ArrayType &items, const std::string &word){
    std::unordered_map<std::string::value_type, std::string::size_type> counters;
    for(const auto c: word){
        ++counters[c];
    }

    ArrayType output;
    for(const auto item: items) {
        auto length = word.size();
        auto temp_counters = counters;
        for(const auto c: item) {
            auto iter = temp_counters.find(c);
            if(iter != temp_counters.cend() and iter->second != 0ul){
                --(iter->second);
                if(not --length){
                    output.push_back(item);
                    break;
                }
            }
        }
    }

    return output;
}


const ArrayType SAMPLE = {"geeksforgeeks", "unsorted", "sunday", "just", "sss"};
const ArrayType EXPECTED = {"unsorted", "sunday"};

SIMPLE_BENCHMARK(ItemsContainingAllCharsOfGivenWord, SAMPLE, std::string("sun"));

SIMPLE_TEST(ItemsContainingAllCharsOfGivenWord, TestSAMPLE1, EXPECTED, SAMPLE, std::string("sun"));
