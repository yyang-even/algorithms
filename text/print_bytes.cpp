#include "common_header.h"


namespace {

typedef const unsigned char *Byte_Pointer;
/**
 * @reference   How will you show memory representation of C variables?
 *              https://www.geeksforgeeks.org/how-will-you-show-memory-representation-of-c-variables/
 * @reference   Randal E.Bryant, David R.O'Hallaron.
 *              Computer System: A Programmer's Perspective (Third Edition). Section 2.1.
 * @reference   StringStream in C++ for Decimal to Hexadecimal and back
 *              https://www.geeksforgeeks.org/stringstream-c-decimal-hexadecimal-back/
 *
 * Write a C program to show memory representation of C variables like int, float, pointer, etc.
 */
std::string PrintBytes_C(const Byte_Pointer bytes, const size_t len) {
    std::string str_out(len * 2, '0');
    char *buff = (char *)str_out.data();
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

}//namespace


SIMPLE_BENCHMARK(PrintInt_Cpp, -1);

SIMPLE_TEST(PrintInt_Cpp, TestSample1, std::string(sizeof(int) * 2, 'f'), -1);
SIMPLE_TEST(PrintInt_Cpp, TestSample2, std::string(sizeof(int) * 2, '0'), 0);


SIMPLE_BENCHMARK(PrintInt_C, -1);

SIMPLE_TEST(PrintInt_C, TestSample1, std::string(sizeof(int) * 2, 'f'), -1);
SIMPLE_TEST(PrintInt_C, TestSample2, std::string(sizeof(int) * 2, '0'), 0);
