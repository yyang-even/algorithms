#include "common_header.h"


namespace {

/** Print a long int in C using putchar() only
 *
 * @reference   https://www.geeksforgeeks.org/print-long-int-number-c-using-putchar/
 *
 * Write a C function print(n) that takes a long int number n as argument, and prints it
 * on console. The only allowed library function is putchar(), no other function like
 * itoa() or printf() is allowed. Use of loops is also not allowed.
 *
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 6.
 */
inline void put_char(std::string &stream, const char c) {
    stream.push_back(c);
}

inline void PrintIntegerHelper(std::string &stream, const unsigned num) {
    const auto next_n = num / 10;
    if (next_n) {
        PrintIntegerHelper(stream, next_n);
    }

    put_char(stream, num % 10 + '0');
}

inline auto PrintInteger(int num) {
    std::string stream;

    if (num < 0) {
        put_char(stream, '-');
        num = -num;
    }

    PrintIntegerHelper(stream, num);
    return stream;
}

}//namespace


constexpr auto LOWER = std::numeric_limits<int>::min() + 1;
constexpr auto UPPER = std::numeric_limits<int>::max();


THE_BENCHMARK(PrintInteger, -1);

SIMPLE_TEST(PrintInteger, TestSample1, "-1", -1);
SIMPLE_TEST(PrintInteger, TestSample2, "0", 0);
SIMPLE_TEST(PrintInteger, TestSample3, "1", 1);
SIMPLE_TEST(PrintInteger, TestSample4, "12045", 12045);

using std::to_string;
MUTUAL_RANDOM_TEST(PrintInteger, to_string, LOWER, UPPER);
