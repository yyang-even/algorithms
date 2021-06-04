#include "common_header.h"


namespace {

/** Check Whether a number is Duck Number or not
 *
 * @reference   https://www.geeksforgeeks.org/check-whether-number-duck-number-not/
 *
 * A Duck number is a number which has zeroes present in it, but there should be no zero
 * present in the beginning of the number. For example 3210, 8050896, 70709 are all duck
 * numbers whereas 02364, 03401 are not. The task is to check whether the given number
 * is a duck number or not.
 */
constexpr auto IsDuckNumber(const std::string_view number) {
    if (number.front() != '0') {
        for (auto iter = number.cbegin() + 1; iter != number.cend(); ++iter) {
            if (*iter == '0') {
                return true;
            }
        }
    }
    return false;
}

}//namespace


THE_BENCHMARK(IsDuckNumber, "707069");

SIMPLE_TEST(IsDuckNumber, TestSample1, true, "707069");
SIMPLE_TEST(IsDuckNumber, TestSample2, true, "3210");
SIMPLE_TEST(IsDuckNumber, TestSample3, true, "8050896");
SIMPLE_TEST(IsDuckNumber, TestSample4, true, "70709");
SIMPLE_TEST(IsDuckNumber, TestSample5, false, "02364");
SIMPLE_TEST(IsDuckNumber, TestSample6, false, "03401");
SIMPLE_TEST(IsDuckNumber, TestSample7, true, "1023");
