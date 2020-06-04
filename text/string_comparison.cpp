#include "common_header.h"


namespace {

/**
 * @reference   Program to check if two strings are same or not
 *              https://www.geeksforgeeks.org/program-to-check-if-two-strings-are-same-or-not/
 */


/** Check if two strings are same ignoring their cases
 *
 * @reference   https://www.geeksforgeeks.org/check-if-two-strings-are-same-ignoring-their-cases/
 */
auto CaseInsensitiveCompare(const std::string &lhs, const std::string &rhs) {
    return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend(),
    [](const auto a, const auto b) {
        return std::tolower(a) == std::tolower(b);
    });
}

}//namespace


SIMPLE_BENCHMARK(CaseInsensitiveCompare, "Geeks", "geeks");

SIMPLE_TEST(CaseInsensitiveCompare, TestSAMPLE1, true, "Geeks", "geeks");
SIMPLE_TEST(CaseInsensitiveCompare, TestSAMPLE2, false, "Geek", "geeksforgeeks");
