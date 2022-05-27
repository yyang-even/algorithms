#include "common_header.h"


namespace {

/** Zigzag Conversion
 *
 * @reference   https://leetcode.com/problems/zigzag-conversion/
 *
 * The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this:
 * (you may want to display this pattern in a fixed font for better legibility)
 *  P   A   H   N
 *  A P L S I I G
 *  Y   I   R
 * And then read line by line: "PAHNAPLSIIGYIR"
 * Write the code that will take a string and make this conversion given a number of rows.
 */
auto ZigZagConversion(const std::string_view s, const int num_rows) {
    std::vector<std::string> rows(num_rows);
    for (std::size_t i = 0; i < s.size();) {
        for (int j = 0; j < num_rows and i < s.size(); ++j) {
            rows[j].push_back(s[i++]);
        }

        for (int j = num_rows - 2; j >= 1 and i < s.size(); --j) {
            rows[j].push_back(s[i++]);
        }
    }

    std::string result;
    for (auto &a_row : rows) {
        result += std::move(a_row);
    }

    return result;
}

} //namespace


THE_BENCHMARK(ZigZagConversion, "PAYPALISHIRING", 3);

SIMPLE_TEST(ZigZagConversion, TestSAMPLE1, "PAHNAPLSIIGYIR", "PAYPALISHIRING", 3);
/**
 * P     I    N
 * A   L S  I G
 * Y A   H R
 * P     I
 */
SIMPLE_TEST(ZigZagConversion, TestSAMPLE2, "PINALSIGYAHRPI", "PAYPALISHIRING", 4);
SIMPLE_TEST(ZigZagConversion, TestSAMPLE3, "A", "A", 1);
