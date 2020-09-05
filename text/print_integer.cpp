#include "common_header.h"


namespace {

using InputType = int;

/** Print a long int in C using putchar() only
 *
 * @reference   https://www.geeksforgeeks.org/print-long-int-number-c-using-putchar/
 *
 * Write a C function print(n) that takes a long int number n as argument, and prints it on console.
 * The only allowed library function is putchar(), no other function like itoa() or printf() is
 * allowed. Use of loops is also not allowed.
 */
void put_char(std::string &stream, const char c) {
    stream.push_back(c);
}

void PrintIntegerHelper(std::string &stream, const unsigned num) {
    const auto next_n = num / 10u;
    if (next_n) {
        PrintIntegerHelper(stream, next_n);
    }

    put_char(stream, num % 10u + '0');
}
auto PrintInteger(InputType num) {
    std::string stream;

    if (num < 0) {
        put_char(stream, '-');
        num = -num;
    }

    PrintIntegerHelper(stream, num);
    return stream;
}

}//namespace


constexpr auto LOWER = std::numeric_limits<InputType>::min() + 1;
constexpr auto UPPER = std::numeric_limits<InputType>::max();


SIMPLE_BENCHMARK(PrintInteger, Sample1, -1);

SIMPLE_TEST(PrintInteger, TestSample1, "-1", -1);
SIMPLE_TEST(PrintInteger, TestSample2, "0", 0);
SIMPLE_TEST(PrintInteger, TestSample3, "1", 1);
SIMPLE_TEST(PrintInteger, TestSample4, "12045", 12045);

using std::to_string;
MUTUAL_RANDOM_TEST(PrintInteger, to_string, LOWER, UPPER);
