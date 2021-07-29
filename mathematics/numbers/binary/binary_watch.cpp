#include "common_header.h"


namespace {

using ArrayType = std::vector<std::string>;

/** Binary Watch
 *
 * @reference   https://leetcode.com/problems/binary-watch/
 *
 * A binary watch has 4 LEDs on the top which represent the hours (0-11), and the 6 LEDs
 * on the bottom represent the minutes (0-59). Each LED represents a zero or one, with
 * the least significant bit on the right.
 */
auto BinaryWatch(const std::size_t turned_on) {
    ArrayType results;

    for (int hour = 0; hour < 12; ++hour) {
        for (int minute = 0; minute < 60; ++minute) {
            if (std::bitset<10>(hour << 6 | minute).count() == turned_on)
                results.push_back(std::to_string(hour) +
                                  (minute < 10 ? ":0" : ":") +
                                  std::to_string(minute));
        }
    }

    return results;
}

}//namespace


const ArrayType EXPECTED0 = {};
const ArrayType EXPECTED1 = {"0:01", "0:02", "0:04", "0:08", "0:16", "0:32", "1:00", "2:00", "4:00", "8:00"};


THE_BENCHMARK(BinaryWatch, 1);

SIMPLE_TEST(BinaryWatch, TestSAMPLE0, EXPECTED0, 9);
SIMPLE_TEST(BinaryWatch, TestSAMPLE1, EXPECTED1, 1);
