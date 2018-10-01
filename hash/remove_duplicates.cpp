#include "common_header.h"

#include <bitset>

/** Remove duplicates from a given string
 *
 * @reference   https://www.geeksforgeeks.org/remove-duplicates-from-a-given-string/
 *
 * @complexity  O(n)
 */
auto RemoveDuplicates(const std::string &input) {
    std::unordered_set<std::string::value_type> hash_table;

    std::string output;
    for (const auto c : input) {
        if (hash_table.find(c) == hash_table.cend()) {
            output.push_back(c);
            hash_table.emplace(c);
        }
    }

    return output;
}


/** Remove duplicates from a string in O(1) extra space
 *
 * @reference   https://www.geeksforgeeks.org/remove-duplicates-from-a-string-in-o1-extra-space/
 *
 * Given a string str of lowercase characters, the task is to remove duplicates and return
 * a resultant string without modifying the order of characters in the original string.
 */
auto RemoveDuplicatesBits(const std::string &input) {
    std::bitset < 'z' - 'a' > hash_table;

    std::string output;
    for (const auto c : input) {
        const auto index = c - 'a';
        if (not hash_table.test(index)) {
            output.push_back(c);
            hash_table.set(index);
        }
    }

    return output;
}


SIMPLE_BENCHMARK(RemoveDuplicates, std::string("geeksforgeeks"));

SIMPLE_TEST(RemoveDuplicates, TestSAMPLE1, std::string("geksfor"), std::string("geeksforgeeks"));
SIMPLE_TEST(RemoveDuplicates, TestSAMPLE2, std::string("chartes"), std::string("characters"));


SIMPLE_BENCHMARK(RemoveDuplicatesBits, std::string("geeksforgeeks"));

SIMPLE_TEST(RemoveDuplicatesBits, TestSAMPLE1, std::string("geksfor"),
            std::string("geeksforgeeks"));
SIMPLE_TEST(RemoveDuplicatesBits, TestSAMPLE2, std::string("chartes"), std::string("characters"));
