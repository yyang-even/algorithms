#include "common_header.h"

typedef const unsigned char *Byte_Pointer;
/**
 * @reference   How will you show memory representation of C variables?
 *              http://www.geeksforgeeks.org/how-will-you-show-memory-representation-of-c-variables/
 * @reference   Randal E.Bryant, David R.O'Hallaron.
 *              Computer System: A Programmer's Perspective (Third Edition). Section 2.1.
 *
 * Write a C program to show memory representation of C variables like int, float, pointer, etc.
 */
std::string PrintBytesC(const Byte_Pointer bytes, const size_t len) {
    std::string str_out(len * 2, '0');
    char *buff = (char *)str_out.data();
    for (size_t i = 0; i < len; ++i, buff += 2) {
        sprintf(buff, "%.2x", bytes[i]);
    }
    return str_out;
}

std::string PrintIntC(const int num) {
    return PrintBytesC((Byte_Pointer)(&num), sizeof(num));
}

std::string PrintBytesCpp(const Byte_Pointer bytes, const size_t len) {
    std::stringstream ss_out;
    for (size_t i = 0; i < len; ++i) {
        ss_out << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(bytes[i]);
    }
    return ss_out.str();
}

std::string PrintIntCpp(const int num) {
    return PrintBytesCpp(reinterpret_cast<Byte_Pointer>(&num), sizeof(num));
}


SIMPLE_BENCHMARK(PrintIntCpp, -1);

SIMPLE_TEST(PrintIntCpp, TestSample1, std::string(sizeof(int) * 2, 'f'), -1);
SIMPLE_TEST(PrintIntCpp, TestSample2, std::string(sizeof(int) * 2, '0'), 0);

SIMPLE_BENCHMARK(PrintIntC, -1);

SIMPLE_TEST(PrintIntC, TestSample1, std::string(sizeof(int) * 2, 'f'), -1);
SIMPLE_TEST(PrintIntC, TestSample2, std::string(sizeof(int) * 2, '0'), 0);
