#include "common_header.h"


namespace {

/** Print numbers 1 to N
 *
 * @reference   How will you print numbers from 1 to 100 without using loop?
 *              https://www.geeksforgeeks.org/how-will-you-print-numbers-from-1-to-200-without-using-loop/
 * @reference   Print numbers 1 to N using Indirect recursion
 *              https://www.geeksforgeeks.org/print-numbers-1-n-using-indirect-recursion/
 * @reference   C Program to print numbers from 1 to N without using semicolon?
 *              https://www.geeksforgeeks.org/c-program-to-print-numbers-from-1-to-n-without-using-semicolon/
 */


/**
 * @reference   Print 1 to 100 in C++, without loop and recursion
 *              https://www.geeksforgeeks.org/output-of-c-program-set-18-3/
 */
template <unsigned N>
struct OneToNPrinter {
    static void Print(std::string &result) {
        OneToNPrinter < N - 1 >::Print(result);
        result.push_back(',');
        result.append(std::to_string(N));
    }
};

template <>
struct OneToNPrinter<1> {
    static void Print(std::string &result) {
        result.push_back('0' + 1);
    }
};

template <unsigned N>
auto PrintRange1ToN_Template() {
    std::string result;
    OneToNPrinter<N>::Print(result);
    return result;
}

const auto PrintRange1To1_Template = PrintRange1ToN_Template<1>;
const auto PrintRange1To2_Template = PrintRange1ToN_Template<2>;
const auto PrintRange1To100_Template = PrintRange1ToN_Template<100>;


/**
 * @reference   How to print N times without using loops or recursion ?
 *              https://www.geeksforgeeks.org/how-to-print-n-times-without-using-loops-or-recursion/
 * @reference   Print a character n times without using loop, recursion or goto in C++
 *              https://www.geeksforgeeks.org/print-a-character-n-times-without-using-loop-recursion-or-goto-in-cpp/
 */
struct NumberPrinter {
    static inline unsigned i = 0;
    static inline std::string result;

    NumberPrinter() {
        result.append(std::to_string(i++));
        result.push_back(',');
    }
};

auto PrintRange1ToN_Constructor(const unsigned N) {
    NumberPrinter::i = 1;
    NumberPrinter::result.clear();

    [[maybe_unused]] NumberPrinter a[N];
    NumberPrinter::result.pop_back();

    return NumberPrinter::result;
}


/**
 * @reference   How will you print numbers from 1 to 100 without using loop? | Set-2
 *              https://www.geeksforgeeks.org/program-print-upto-100-without-using-loops/
 * @reference   Print a number 100 times without using loop, recursion and macro expansion in C?
 *              https://www.geeksforgeeks.org/print-number-100-times-without-using-loop-recursion-macro-expansion-c/
 *
 * @note    Use setjmp() and longjmp().
 */
auto PrintRange1ToN_Goto(const unsigned N) {
    unsigned i = 1;
    std::string result;

begin:
    result.append(std::to_string(i++));

    if (i <= N) {
        result.push_back(',');
        goto begin;
    }

    return result;
}


/**
 * @reference   How to print a number 100 times without using loop and recursion in C?
 *              https://www.geeksforgeeks.org/print-number-100-times-without-using-loop-recursion-c/
 *
 * @note    Use Macro expansion.
 */


/**
 * @reference   Write a C program to print “GfG” repeatedly without using loop, recursion and any control structure?
 *              https://www.geeksforgeeks.org/write-c-program-print-gfg-repeatedly-without-using-loop-recursion-control-structure/
 */


/** C++ Program to print an Array using Recursion
 *
 * @reference   https://www.geeksforgeeks.org/c-program-to-print-an-array-using-recursion/
 */

}//namespace


SIMPLE_BENCHMARK0(PrintRange1To100_Template);

SIMPLE_TEST0(PrintRange1To1_Template, TestSAMPLE1, "1");
SIMPLE_TEST0(PrintRange1To2_Template, TestSAMPLE2, "1,2");


THE_BENCHMARK(PrintRange1ToN_Constructor, 100);

SIMPLE_TEST(PrintRange1ToN_Constructor, TestSAMPLE1, "1", 1);
SIMPLE_TEST(PrintRange1ToN_Constructor, TestSAMPLE2, "1,2", 2);


THE_BENCHMARK(PrintRange1ToN_Goto, 100);

SIMPLE_TEST(PrintRange1ToN_Goto, TestSAMPLE1, "1", 1);
SIMPLE_TEST(PrintRange1ToN_Goto, TestSAMPLE2, "1,2", 2);
