#include "common_header.h"

/** Remove spaces from a given string
 *
 * @reference   https://www.geeksforgeeks.org/remove-spaces-from-a-given-string/
 *
 * Given a string, remove all spaces from the string and return it.
 * Expected time complexity is O(n) and only one traversal of string.
 */
auto RemoveSpaces(std::string input){
    auto output_iter = input.begin();
    for(auto input_iter = input.begin(); input_iter != input.end(); ++input_iter) {
        if(*input_iter != ' ')
            *output_iter++ = *input_iter;
    }

    input.resize(output_iter - input.begin());
    return input;
}


SIMPLE_BENCHMARK(RemoveSpaces, std::string("g  eeks   for ge  eeks  "));

SIMPLE_TEST(RemoveSpaces, TestSAMPLE1, std::string("geeksforgeeeks"), std::string("g  eeks   for ge  eeks  "));
