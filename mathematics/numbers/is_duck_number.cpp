#include "common_header.h"

/** Check Whether a number is Duck Number or not
 *
 * @reference   https://www.geeksforgeeks.org/check-whether-number-duck-number-not/
 *
 * A Duck number is a number which has zeroes present in it, but there
 * should be no zero present in the beginning of the number. For example
 * 3210, 8050896, 70709 are all duck numbers whereas 02364, 03401 are not.
 * The task is to check whether the given number is a duck number or not.
 */
INT_BOOL IsDuckNumber(const std::string &number) {
    if (number.front() != '0') {
        for (auto iter = number.cbegin() + 1; iter != number.cend(); ++iter) {
            if (*iter == '0') {
                return true;
            }
        }
    }
    return false;
}


SIMPLE_BENCHMARK(IsDuckNumber, std::string("707069"));

SIMPLE_TEST(IsDuckNumber, TestSample1, TRUE, std::string("707069"));
SIMPLE_TEST(IsDuckNumber, TestSample2, TRUE, std::string("3210"));
SIMPLE_TEST(IsDuckNumber, TestSample3, TRUE, std::string("8050896"));
SIMPLE_TEST(IsDuckNumber, TestSample4, TRUE, std::string("70709"));
SIMPLE_TEST(IsDuckNumber, TestSample5, FALSE, std::string("02364"));
SIMPLE_TEST(IsDuckNumber, TestSample6, FALSE, std::string("03401"));
SIMPLE_TEST(IsDuckNumber, TestSample7, TRUE, std::string("1023"));
