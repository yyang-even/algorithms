#include "common_header.h"

#include <iomanip>


namespace {

using Byte_Pointer = const unsigned char *;

/**
 * @reference   How will you show memory representation of C variables?
 *              https://www.geeksforgeeks.org/how-will-you-show-memory-representation-of-c-variables/
 * @reference   Randal E.Bryant, David R.O'Hallaron.
 *              Computer System: A Programmer's Perspective (Third Edition). Section 2.1.
 * @reference   StringStream in C++ for Decimal to Hexadecimal and back
 *              https://www.geeksforgeeks.org/stringstream-c-decimal-hexadecimal-back/
 *
 * Write a C program to show memory representation of C variables like int, float,
 * pointer, etc.
 */
std::string PrintBytes_C(const Byte_Pointer bytes, const size_t len) {
    std::string str_out(len * 2, '0');
    auto *buff = str_out.data();
    for (size_t i = 0; i < len; ++i, buff += 2) {
        sprintf(buff, "%.2x", bytes[i]);
    }
    return str_out;
}

std::string PrintInt_C(const int num) {
    return PrintBytes_C((Byte_Pointer)(&num), sizeof(num));
}


std::string PrintBytes_Cpp(const Byte_Pointer bytes, const size_t len) {
    std::stringstream ss_out;
    for (size_t i = 0; i < len; ++i) {
        ss_out << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(bytes[i]);
    }
    return ss_out.str();
}

std::string PrintInt_Cpp(const int num) {
    return PrintBytes_Cpp(reinterpret_cast<Byte_Pointer>(&num), sizeof(num));
}


/** Convert Hexadecimal value String to ASCII value String
 *
 * @reference   https://www.geeksforgeeks.org/convert-hexadecimal-value-string-ascii-value-string/
 */
auto HexToChar(const std::string &hex) {
    assert(hex.size() % 2 == 0);

    std::string result;
    for (std::string::size_type i = 0; i < hex.size(); i += 2) {
        const auto c = std::stoul(hex.substr(i, 2), nullptr, 16);
        result.push_back(c);
    }

    return result;
}

}//namespace


THE_BENCHMARK(PrintInt_Cpp, -1);

SIMPLE_TEST(PrintInt_Cpp, TestSample1, std::string(sizeof(int) * 2, 'f'), -1);
SIMPLE_TEST(PrintInt_Cpp, TestSample2, std::string(sizeof(int) * 2, '0'), 0);


THE_BENCHMARK(PrintInt_C, -1);

SIMPLE_TEST(PrintInt_C, TestSample1, std::string(sizeof(int) * 2, 'f'), -1);
SIMPLE_TEST(PrintInt_C, TestSample2, std::string(sizeof(int) * 2, '0'), 0);


THE_BENCHMARK(HexToChar, "6765656b73");

SIMPLE_TEST(HexToChar, TestSample1, "geeks", "6765656b73");
SIMPLE_TEST(HexToChar, TestSample2, "avengers", "6176656e67657273");
