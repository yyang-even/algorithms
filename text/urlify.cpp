#include "common_header.h"


namespace {

/** URLify a given string (Replace spaces is %20)
 *
 * @reference   https://www.geeksforgeeks.org/urlify-given-string-replace-spaces/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 1.4.
 *
 * Write a method to replace all the spaces in a string with '%20'. You may assume that
 * the string has sufficient space at the end to hold the additional characters and that
 * you are given the "true" length of the string.
 */
auto URLify(std::string str, std::string::size_type length = 0) {
    if (length == 0) {
        length = str.size();
    }
    assert(length != 0);

    const auto cend = std::next(str.cbegin(), length);
    const auto space_count = std::count(str.cbegin(), cend, ' ');
    auto result_length = length + space_count * 2;

    str.resize(result_length);

    for (int i = length - 1; i >= 0; --i) {
        if (str[i] == ' ') {
            str[--result_length] = '0';
            str[--result_length] = '2';
            str[--result_length] = '%';
        } else {
            str[--result_length] = str[i];
        }
    }

    return str;
}

}//namespace


THE_BENCHMARK(URLify, "Mr John Smith");

SIMPLE_TEST(URLify, TestSAMPLE1, "Mr%20John%20Smith", "Mr John Smith");
SIMPLE_TEST(URLify, TestSAMPLE2, "Mr%20John%20Smith", "Mr John Smith   ", 13);
