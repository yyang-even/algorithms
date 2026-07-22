#include "common_header.h"


namespace {

using ArrayType = std::vector<std::string>;

/**
 * @reference   Binary Watch
 *              https://leetcode.com/problems/binary-watch/
 *
 * A binary watch has 4 LEDs on the top which represent the hours (0-11), and the 6 LEDs on the bottom
 * represent the minutes (0-59). Each LED represents a zero or one, with the least significant bit on
 * the right.
 * Given an integer turnedOn which represents the number of LEDs that are currently on (ignoring the
 * PM), return all possible times the watch could represent. You may return the answer in any order.
 * The hour must not contain a leading zero.
 *  For example, "01:00" is not valid. It should be "1:00".
 * The minute must consist of two digits and may contain a leading zero.
 *  For example, "10:2" is not valid. It should be "10:02".
 *
 * @tags    #backtracking #combinatorics #bit-tricks #to-string
 */
auto BinaryWatch(const std::size_t turned_on) {
    ArrayType results;

    for (int hour = 0; hour < 12; ++hour) {
        for (int minute = 0; minute < 60; ++minute) {
            if (std::bitset<10>(hour << 6 | minute).count() == turned_on)
                results.push_back(std::to_string(hour) + (minute < 10 ? ":0" : ":") +
                                  std::to_string(minute));
        }
    }

    return results;
}

} //namespace


const ArrayType EXPECTED0 = {};
const ArrayType EXPECTED1 = {
    "0:01", "0:02", "0:04", "0:08", "0:16", "0:32", "1:00", "2:00", "4:00", "8:00"};


THE_BENCHMARK(BinaryWatch, 1);

SIMPLE_TEST(BinaryWatch, TestSAMPLE0, EXPECTED0, 9);
SIMPLE_TEST(BinaryWatch, TestSAMPLE1, EXPECTED1, 1);
