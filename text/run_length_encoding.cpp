#include "common_header.h"


namespace {

/** Run Length Encoding
 *
 * @reference   https://www.geeksforgeeks.org/run-length-encoding/
 *
 * Given an input string, write a function that returns the Run Length Encoded string for the input string.
 * For example, if the input string is “wwwwaaadexxxxxx”, then the function should return “w4a3d1e1x6”.
 */
auto RunLengthEncoding(const std::string &input) {
    std::string output;

    for (std::string::size_type i = 0; i < input.size();) {
        auto next_i = input.find_first_not_of(input[i], i);
        if (next_i == std::string::npos) {
            next_i = input.size();
        }
        const auto count = next_i - i;
        output.push_back(input[i]);
        output.append(std::to_string(count));
        i = next_i;
    }

    return output;
}

}//namespace


SIMPLE_BENCHMARK(RunLengthEncoding, Sample1, "wwwwaaadexxxxxx");

SIMPLE_TEST(RunLengthEncoding, TestSAMPLE1, "w4a3d1e1x6", "wwwwaaadexxxxxx");
