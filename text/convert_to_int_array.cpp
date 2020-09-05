#include "common_header.h"


namespace {

/** Convert a String to Integer Array in C/C++
 *
 * @reference   https://www.geeksforgeeks.org/convert-a-string-to-integer-array-in-c-c/
 *
 * Given a string str containing numbers separated with “, “. The task
 * is to convert it into an integer array and find the sum of that array.
 */
auto ConvertToIntArray(const std::string &str) {
    std::vector<int> outputs(1, 0);

    for (const auto c : str) {
        if (c == ',') {
            outputs.push_back(0);
        } else if (isdigit(c)) {
            outputs.back() = outputs.back() * 10 + c - '0';
        }
    }

    return outputs;
}

}//namespace


const std::vector<int> EXPECTED1 = {2, 6, 3, 14};
const std::vector<int> EXPECTED2 = {125, 4, 24, 5543, 111};


SIMPLE_BENCHMARK(ConvertToIntArray, Sample1, "2, 6, 3, 14");

SIMPLE_TEST(ConvertToIntArray, TestSAMPLE1, EXPECTED1, "2, 6, 3, 14");
SIMPLE_TEST(ConvertToIntArray, TestSAMPLE2, EXPECTED2, "125, 4, 24, 5543, 111");
