#include "common_header.h"

#include "to_decimal.h"


namespace {

auto BinaryIntegerToOctal(const std::string &binary,
                          std::string::size_type start, const std::string::size_type length) {
    static const auto binary_to_octal_digit_map = CreateBinaryToOctalDigitMap();

    const auto remainder = length % 3;
    const auto end = start + length;

    std::string result;
    for (std::string::size_type substr_size = (remainder == 0 ? 3 : remainder);
         start < end; substr_size = 3) {
        result.push_back(binary_to_octal_digit_map.at(binary.substr(start, substr_size)));
        start += substr_size;
    }

    return result;
}

auto BinaryIntegerToOctal(const std::string &binary) {
    return BinaryIntegerToOctal(binary, 0, binary.size());
}


/** Convert a binary number to octal
 *
 * @reference   https://www.geeksforgeeks.org/convert-binary-number-octal/
 */
auto BinaryToOctal(std::string binary) {
    const auto dot_position = binary.find('.');
    if (dot_position == std::string::npos) {
        return BinaryIntegerToOctal(binary);
    }

    const auto right_size = binary.size() - dot_position - 1;
    for (int number_pad = (3 - (right_size % 3)) % 3; number_pad--;) {
        binary.push_back('0');
    }

    const auto left = BinaryIntegerToOctal(binary, 0, dot_position);
    const auto right = BinaryIntegerToOctal(binary, dot_position + 1, binary.size() - dot_position - 1);

    return left + "." + right;
}

}//namespace


SIMPLE_BENCHMARK(BinaryIntegerToOctal, "110001110");

SIMPLE_TEST(BinaryIntegerToOctal, TestSAMPLE1, "616", "110001110");
SIMPLE_TEST(BinaryIntegerToOctal, TestSAMPLE2, "16", "1110");


SIMPLE_BENCHMARK(BinaryToOctal, "110001110");

SIMPLE_TEST(BinaryToOctal, TestSAMPLE1, "616", "110001110");
SIMPLE_TEST(BinaryToOctal, TestSAMPLE2, "16", "1110");
SIMPLE_TEST(BinaryToOctal, TestSAMPLE3, "1712241.26633", "1111001010010100001.010110110011011");
