#include "common_header.h"

#include "number_convertion.h"
#include "to_binary.h"


namespace {

auto BinaryIntegerTo(const std::string &binary, const unsigned base,
                     std::string::size_type start, const std::string::size_type length,
                     const std::unordered_map<std::string, char> &binary_to_digit_map) {
    const auto remainder = length % base;
    const auto end = start + length;

    std::string result;
    for (auto substr_size = (remainder == 0 ? base : remainder);
         start < end; substr_size = base) {
        result.push_back(binary_to_digit_map.at(binary.substr(start, substr_size)));
        start += substr_size;
    }

    return result;
}


inline auto BinaryIntegerToOctal(const std::string &binary,
                                 const std::string::size_type start,
                                 const std::string::size_type length) {
    static const auto binary_to_octal_digit_map = CreateBinaryToOctalDigitMap();

    return BinaryIntegerTo(binary, 3, start, length, binary_to_octal_digit_map);
}

inline auto BinaryIntegerToOctal(const std::string &binary) {
    return BinaryIntegerToOctal(binary, 0, binary.size());
}


inline auto BinaryIntegerToHex(const std::string &binary,
                               const std::string::size_type start,
                               const std::string::size_type length) {
    static const auto binary_to_hex_digit_map = CreateBinaryToHexDigitMap();

    return BinaryIntegerTo(binary, 4, start, length, binary_to_hex_digit_map);
}


template <typename BinaryIntegerToFunc>
auto BinaryTo(const std::string &binary, const unsigned base,
              const BinaryIntegerToFunc binary_integer_to) {
    const auto dot_position = binary.find('.');
    if (dot_position == std::string::npos) {
        return binary_integer_to(binary, 0, binary.size());
    }

    auto padded_binary = binary;
    auto right_size = padded_binary.size() - dot_position - 1;
    for (int number_pad = (base - (right_size % base)) % base; number_pad--; ++right_size) {
        padded_binary.push_back('0');
    }

    const auto left = binary_integer_to(padded_binary, 0, dot_position);
    const auto right = binary_integer_to(padded_binary, dot_position + 1, right_size);

    return left + "." + right;
}


/** Convert a binary number to octal
 *
 * @reference   https://www.geeksforgeeks.org/convert-binary-number-octal/
 */
inline auto BinaryToOctal(const std::string &binary) {
    return BinaryTo(binary, 3, ToLambda(BinaryIntegerToOctal));
}


/**
 * @reference   Convert a binary number to hexadecimal number
 *              https://www.geeksforgeeks.org/convert-binary-number-hexadecimal-number/
 */
inline auto BinaryToHex(const std::string &binary) {
    return BinaryTo(binary, 4, BinaryIntegerToHex);
}


/**
 * @reference   Program to Convert Hexadecimal to Octal
 *              https://www.geeksforgeeks.org/program-to-convert-hexadecimal-to-octal/
 */
inline auto HexToOct(const std::string &hex) {
    return BinaryToOctal(HexToBinary(hex));
}


/**
 * @reference   Program to Convert Octal to Hexadecimal
 *              https://www.geeksforgeeks.org/program-to-convert-octal-to-hexadecimal/
 */

}//namespace


THE_BENCHMARK(BinaryIntegerToOctal, "110001110");

SIMPLE_TEST(BinaryIntegerToOctal, TestSAMPLE1, "616", "110001110");
SIMPLE_TEST(BinaryIntegerToOctal, TestSAMPLE2, "16", "1110");


THE_BENCHMARK(BinaryToOctal, "110001110");

SIMPLE_TEST(BinaryToOctal, TestSAMPLE1, "616", "110001110");
SIMPLE_TEST(BinaryToOctal, TestSAMPLE2, "16", "1110");
SIMPLE_TEST(BinaryToOctal, TestSAMPLE3, "1712241.26633",
            "1111001010010100001.010110110011011");


THE_BENCHMARK(BinaryToHex, "110001110");

SIMPLE_TEST(BinaryToHex, TestSAMPLE1, "18E", "110001110");
SIMPLE_TEST(BinaryToHex, TestSAMPLE2, "794A1.5B36",
            "1111001010010100001.010110110011011");


THE_BENCHMARK(HexToOct, "1AC");

SIMPLE_TEST(HexToOct, TestSAMPLE1, "0654", "1AC");
SIMPLE_TEST(HexToOct, TestSAMPLE2, "056437", "5D1F");
