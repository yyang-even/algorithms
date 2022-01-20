#include "common_header.h"

#include "number_convertion.h"


namespace {

auto ToDecimal(const std::string_view number, const int base,
               const std::function<int(const char)> to_decimal) {
    int result = 0;
    int sign = 1;

    if (not number.empty()) {
        auto cbegin = number.cbegin();
        if (*cbegin == '-') {
            sign = -1;
            ++cbegin;
        }

        while (cbegin != number.cend()) {
            result = result * base + to_decimal(*(cbegin++));
        }
    }

    return sign * result;
}


/** Write your own atoi()
 *
 * @reference   https://www.geeksforgeeks.org/write-your-own-atoi/
 * @reference   C++ Program to Convert String to Integer
 *              https://www.geeksforgeeks.org/c-program-to-convert-string-to-integer/
 * @reference   Convert string to integer without using any in-built functions
 *              https://www.geeksforgeeks.org/convert-string-to-integer-without-using-any-in-built-functions/
 * @reference   Converting string to number and vice-versa in C++
 *              https://www.geeksforgeeks.org/converting-string-to-number-and-vice-versa-in-c/
 * @reference   Converting Strings to Numbers in C/C++
 *              https://www.geeksforgeeks.org/converting-strings-numbers-cc/
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 6.
 *
 * @reference   String to Integer (atoi)
 *              https://leetcode.com/problems/string-to-integer-atoi/
 *
 * Implement the myAtoi(string s) function, which converts a string to a 32-bit signed
 * integer (similar to C/C++'s atoi function).
 * The algorithm for myAtoi(string s) is as follows:
 *  Read in and ignore any leading whitespace.
 *  Check if the next character (if not already at the end of the string) is '-' or '+'.
 *      Read this character in if it is either. This determines if the final result is
 *      negative or positive respectively. Assume the result is positive if neither is
 *      present.
 *  Read in next the characters until the next non-digit character or the end of the
 *      input is reached. The rest of the string is ignored.
 *  Convert these digits into an integer (i.e. "123" -> 123, "0032" -> 32). If no digits
 *      were read, then the integer is 0. Change the sign as necessary (from step 2).
 *  If the integer is out of the 32-bit signed integer range [-2^31, 2^31 - 1], then clamp
 *      the integer so that it remains in the range. Specifically, integers less than
 *      -2^31 should be clamped to -2^31, and integers greater than 2^31 - 1 should be
 *      clamped to 2^31 - 1.
 * Return the integer as the final result.
 * Note:
 *  Only the space character ' ' is considered a whitespace character.
 *  Do not ignore any characters other than the leading whitespace or the rest of the
 *      string after the digits.
 */
int DecToDecimal(const std::string_view dec) {
    std::size_t i = 0;
    while (i < dec.size() and dec[i] == ' ') {
        ++i;
    }

    if (i >= dec.size()) {
        return 0;
    }

    int sign = 1;
    if (dec[i] == '-') {
        sign = -1;
        ++i;
    } else if (dec[i] == '+') {
        ++i;
    }

    long result = 0;
    while (i < dec.size() and std::isdigit(dec[i])) {
        result = result * 10 + dec[i++] - '0';
        if (result > INT_MAX) {
            return sign == 1 ? INT_MAX : INT_MIN;
        }
    }

    return sign * result;
}


/**
 * @reference   Recursive Implementation of atoi()
 *              https://www.geeksforgeeks.org/recursive-implementation-of-atoi/
 */
inline constexpr auto
DecToDecimal_Recursive(const std::string_view::const_reverse_iterator crbegin,
                       const std::string_view::size_type n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return *crbegin - '0';
    }

    return DecToDecimal_Recursive(std::next(crbegin), n - 1) * 10 + *crbegin - '0';
}

inline constexpr auto DecToDecimal_Recursive(const std::string_view dec) {
    return DecToDecimal_Recursive(dec.crbegin(), dec.size());
}


enum class State {
    q0,
    q1,
    q2,
    qd
};

class AtoiStateMachine {
    State current_state = State::q0;
    int result = 0;
    int sign = 1;

    void toQ2(const char c) {
        const auto digit = c - '0';
        if ((result > INT_MAX / 10) or
            (result == INT_MAX / 10 and digit > INT_MAX % 10)) {
            if (sign == 1) {
                result = INT_MAX;
            } else {
                result = INT_MIN;
                sign = 1;
            }

            current_state = State::qd;
        } else {
            result = result * 10 + digit;

            current_state = State::q2;
        }
    }

public:
    auto Transition(const char c) {
        if (current_state == State::q0) {
            if (c == ' ') {
            } else if (c == '-') {
                sign = -1;
                current_state = State::q1;
            } else if (c == '+') {
                current_state = State::q1;
            } else if (std::isdigit(c)) {
                toQ2(c);
            } else {
                current_state = State::qd;
            }
        } else if (current_state == State::q1 or current_state == State::q2) {
            if (std::isdigit(c)) {
                toQ2(c);
            } else {
                current_state = State::qd;
            }
        }

        return current_state != State::qd;
    }

    auto Get() const {
        return sign * result;
    }
};

inline auto Atoi_StateMachine(const std::string_view number) {
    AtoiStateMachine sm;
    for (const auto c : number) {
        if (not sm.Transition(c)) {
            break;
        }
    }

    return sm.Get();
}


/** Program for Hexadecimal to Decimal
 *
 * @reference   https://www.geeksforgeeks.org/program-for-hexadecimal-to-decimal/
 */
inline auto HexToDecimal(const std::string_view hex) {
    return ToDecimal(hex, 16, HexDigitToDecimal);
}


/**
 * @reference   StringStream in C++ for Decimal to Hexadecimal and back
 *              https://www.geeksforgeeks.org/stringstream-c-decimal-hexadecimal-back/
 */
inline auto HexToDecimal_StringStream(const std::string &hex) {
    int decimal_result = 0;
    std::stringstream ss(hex);
    ss >> std::hex >> decimal_result;

    return decimal_result;
}


/** Program for Octal to Decimal Conversion
 *
 * @reference   https://www.geeksforgeeks.org/program-octal-decimal-conversion/
 */
inline auto OctalToDecimal(const std::string_view octal) {
    return ToDecimal(octal, 8, OctalDigitToDecimal);
}


/** Program for Binary To Decimal Conversion
 *
 * @reference   https://www.geeksforgeeks.org/program-binary-decimal-conversion/
 */
inline auto BinaryToDecimal(const std::string_view binary) {
    return ToDecimal(binary, 2, BinaryDigitToDecimal);
}


/**
 * @reference   Recursive Program for Binary to Decimal
 *              https://www.geeksforgeeks.org/recursive-program-for-binary-to-decimal/
 */
inline constexpr int BinaryToDecimal_Recursive(const std::string_view binary,
                                               const std::string_view::size_type i = 0) {
    if (i == binary.size()) {
        return 0;
    }

    return (BinaryDigitToDecimal(binary[i]) << (binary.size() - i - 1)) +
           BinaryToDecimal_Recursive(binary, i + 1);
}

}//namespace


THE_BENCHMARK(HexToDecimal, "1A");

SIMPLE_TEST(HexToDecimal, TestSAMPLE1, 26, "1A");
SIMPLE_TEST(HexToDecimal, TestSAMPLE2, 43, "2B");
SIMPLE_TEST(HexToDecimal, TestSAMPLE3, 103, "67");
SIMPLE_TEST(HexToDecimal, TestSAMPLE4, 1298, "512");
SIMPLE_TEST(HexToDecimal, TestSAMPLE5, 291, "123");


THE_BENCHMARK(HexToDecimal_StringStream, "1A");

SIMPLE_TEST(HexToDecimal_StringStream, TestSAMPLE1, 26, "1A");
SIMPLE_TEST(HexToDecimal_StringStream, TestSAMPLE2, 43, "2B");
SIMPLE_TEST(HexToDecimal_StringStream, TestSAMPLE3, 103, "67");
SIMPLE_TEST(HexToDecimal_StringStream, TestSAMPLE4, 1298, "512");
SIMPLE_TEST(HexToDecimal_StringStream, TestSAMPLE5, 291, "123");


THE_BENCHMARK(OctalToDecimal, "67");

SIMPLE_TEST(OctalToDecimal, TestSAMPLE1, 55, "67");
SIMPLE_TEST(OctalToDecimal, TestSAMPLE2, 330, "512");
SIMPLE_TEST(OctalToDecimal, TestSAMPLE3, 83, "123");


THE_BENCHMARK(BinaryToDecimal, "111");

SIMPLE_TEST(BinaryToDecimal, TestSAMPLE1, 7, "111");
SIMPLE_TEST(BinaryToDecimal, TestSAMPLE2, 10, "1010");
SIMPLE_TEST(BinaryToDecimal, TestSAMPLE3, 33, "100001");
SIMPLE_TEST(BinaryToDecimal, TestSAMPLE4, 169, "10101001");
SIMPLE_TEST(BinaryToDecimal, TestSAMPLE5, 9, "1001");


THE_BENCHMARK(BinaryToDecimal_Recursive, "111");

SIMPLE_TEST(BinaryToDecimal_Recursive, TestSAMPLE1, 7, "111");
SIMPLE_TEST(BinaryToDecimal_Recursive, TestSAMPLE2, 10, "1010");
SIMPLE_TEST(BinaryToDecimal_Recursive, TestSAMPLE3, 33, "100001");
SIMPLE_TEST(BinaryToDecimal_Recursive, TestSAMPLE4, 169, "10101001");
SIMPLE_TEST(BinaryToDecimal_Recursive, TestSAMPLE5, 9, "1001");


THE_BENCHMARK(DecToDecimal, "111");

SIMPLE_TEST(DecToDecimal, TestSAMPLE1, 1, "1");
SIMPLE_TEST(DecToDecimal, TestSAMPLE2, 0, "0");
SIMPLE_TEST(DecToDecimal, TestSAMPLE3, -1, "-1");
SIMPLE_TEST(DecToDecimal, TestSAMPLE4, 4562, "4562");
SIMPLE_TEST(DecToDecimal, TestSAMPLE5, -42, "   -42");
SIMPLE_TEST(DecToDecimal, TestSAMPLE6, 4193, "4193 with words");
SIMPLE_TEST(DecToDecimal, TestSAMPLE7, INT_MAX, std::to_string(INT_MAX));
SIMPLE_TEST(DecToDecimal, TestSAMPLE8, INT_MIN, std::to_string(INT_MIN));


THE_BENCHMARK(DecToDecimal_Recursive, "111");

SIMPLE_TEST(DecToDecimal_Recursive, TestSAMPLE1, 1, "1");
SIMPLE_TEST(DecToDecimal_Recursive, TestSAMPLE2, 0, "0");
SIMPLE_TEST(DecToDecimal_Recursive, TestSAMPLE4, 4562, "4562");


THE_BENCHMARK(Atoi_StateMachine, "111");

SIMPLE_TEST(Atoi_StateMachine, TestSAMPLE1, 1, "1");
SIMPLE_TEST(Atoi_StateMachine, TestSAMPLE2, 0, "0");
SIMPLE_TEST(Atoi_StateMachine, TestSAMPLE3, -1, "-1");
SIMPLE_TEST(Atoi_StateMachine, TestSAMPLE4, 4562, "4562");
SIMPLE_TEST(Atoi_StateMachine, TestSAMPLE5, -42, "   -42");
SIMPLE_TEST(Atoi_StateMachine, TestSAMPLE6, 4193, "4193 with words");
SIMPLE_TEST(Atoi_StateMachine, TestSAMPLE7, INT_MAX, std::to_string(INT_MAX));
SIMPLE_TEST(Atoi_StateMachine, TestSAMPLE8, INT_MIN, std::to_string(INT_MIN));
