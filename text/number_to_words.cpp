#include "common_header.h"


namespace {

/** Program to convert a given number to words
 *
 * @reference   https://www.geeksforgeeks.org/convert-number-to-words/
 * @reference   Program to convert a given number to words | Set 2
 *              https://www.geeksforgeeks.org/program-to-convert-a-given-number-to-words-set-2/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 17.7.
 *
 * Write code to convert a given number into words. For example, if "1234" is given as
 * input, output should be "one thousand two hundred thirty four".
 */
std::string SegmentToWords(int number) {
    assert(number > 0 and number < 1000);

    constexpr const char *DIGITS[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    constexpr const char *TEENS[] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    constexpr const char *TENS[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};

    std::string result;

    if (number >= 100) {
        result += DIGITS[number / 100] + std::string(" Hundred");
        number %= 100;
    }

    if (number >= 10 and number < 20) {
        if (not result.empty()) {
            result += " ";
        }
        return result + TEENS[number - 10];
    } else if (number >= 20) {
        if (not result.empty()) {
            result += " ";
        }
        result += TENS[number / 10];
        number %= 10;
    }

    if (number) {
        if (not result.empty()) {
            result += " ";
        }
        result += DIGITS[number];
    }

    return result;
}

std::string ToWords(int number) {
    constexpr const char *SHORT_SCALES[] = {"", " Thousand", " Million", " Billion", " Trillion"};

    if (number == 0) {
        return "Zero";
    } else if (number < 0) {
        return "Negative " + ToWords(-number);
    }

    std::string result;
    for (unsigned count = 0; number; ++count, number /= 1000) {
        const auto segment = number % 1000;

        if (segment) {
            if (not result.empty()) {
                result = " " + result;
            }
            result = SegmentToWords(segment) + SHORT_SCALES[count] + result;
        }
    }

    return result;
}

}//namespace


THE_BENCHMARK(ToWords, 1234);

SIMPLE_TEST(ToWords, TestSAMPLE0, "Zero", 0);
SIMPLE_TEST(ToWords, TestSAMPLE1, "One", 1);
SIMPLE_TEST(ToWords, TestSAMPLE2, "Negative One", -1);
SIMPLE_TEST(ToWords, TestSAMPLE3, "Twelve", 12);
SIMPLE_TEST(ToWords, TestSAMPLE4, "Twenty", 20);
SIMPLE_TEST(ToWords, TestSAMPLE5, "Three Hundred", 300);
SIMPLE_TEST(ToWords, TestSAMPLE6, "Thirty Two", 32);
SIMPLE_TEST(ToWords, TestSAMPLE7, "Four Hundred Five", 405);
SIMPLE_TEST(ToWords, TestSAMPLE8, "Six Hundred Ten", 610);
SIMPLE_TEST(ToWords, TestSAMPLE9, "Seven Hundred Eleven", 711);
SIMPLE_TEST(ToWords, TestSAMPLE10, "Eight Hundred Forty", 840);
SIMPLE_TEST(ToWords, TestSAMPLE11, "Nine Hundred Fifty Two", 952);
SIMPLE_TEST(ToWords, TestSAMPLE12, "Nine Thousand", 9000);
SIMPLE_TEST(ToWords, TestSAMPLE13, "Two Million", 2'000'000);
SIMPLE_TEST(ToWords, TestSAMPLE14, "Thirteen Thousand", 13000);
SIMPLE_TEST(ToWords, TestSAMPLE15, "Fourteen Million", 14'000'000);
SIMPLE_TEST(ToWords, TestSAMPLE16, "Sixty Thousand", 60000);
SIMPLE_TEST(ToWords, TestSAMPLE17, "Seventy Million", 70'000'000);
SIMPLE_TEST(ToWords, TestSAMPLE18, "Eighty Million Fifteen Thousand Sixteen",
            80'015'016);
SIMPLE_TEST(ToWords, TestSAMPLE19, "Ninety Million Seventeen", 90'000'017);
SIMPLE_TEST(ToWords, TestSAMPLE20, "Nine Thousand Nine Hundred Ninety Nine", 9999);
SIMPLE_TEST(ToWords, TestSAMPLE21, "Thirty Seven Thousand Seven Hundred Sixty Four",
            37764);
SIMPLE_TEST(ToWords, TestSAMPLE22, "Nine Thousand Nine Hundred Twenty Three", 9923);
