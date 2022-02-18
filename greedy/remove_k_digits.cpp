#include "common_header.h"


namespace {

/** Remove K Digits
 *
 * @reference   https://leetcode.com/problems/remove-k-digits/
 *
 * Given string num representing a non-negative integer num, and an integer k, return the
 * smallest possible integer after removing k digits from num.
 */
std::string RemoveKDigits(const std::string_view num, std::size_t k) {
    std::string result;
    for (const auto c : num) {
        while (not result.empty() and k and c < result.back()) {
            result.pop_back();
            --k;
        }

        if (not result.empty() or c != '0') {
            result.push_back(c);
        }
    }

    return result.size() <= k ? "0" : result.substr(0, result.size() - k);
}

}//namespace


THE_BENCHMARK(RemoveKDigits, "1432219", 3);

SIMPLE_TEST(RemoveKDigits, TestSAMPLE1, "1219", "1432219", 3);
SIMPLE_TEST(RemoveKDigits, TestSAMPLE2, "200", "10200", 1);
SIMPLE_TEST(RemoveKDigits, TestSAMPLE3, "0", "10", 2);
SIMPLE_TEST(RemoveKDigits, TestSAMPLE4, "12", "1234", 2);
SIMPLE_TEST(RemoveKDigits, TestSAMPLE5, "107", "1107", 1);
SIMPLE_TEST(RemoveKDigits, TestSAMPLE6, "11", "112", 1);
SIMPLE_TEST(RemoveKDigits, TestSAMPLE7, "0", "1234567890", 9);
