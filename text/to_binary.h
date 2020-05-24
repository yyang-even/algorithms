#pragma once

template <unsigned Size>
static inline auto ToBinary(const std::string &octal,
                            const std::function<int(const char)> to_decimal) {
    std::stringstream ss_out;
    for (const auto octal_digit : octal) {
        ss_out << std::bitset<Size>(to_decimal(octal_digit));
    }

    return ss_out.str();
}


/** Program to Convert Hexadecimal Number to Binary
 *
 * @reference   https://www.geeksforgeeks.org/program-to-convert-hexadecimal-number-to-binary/
 */
static inline auto HexToBinary(const std::string &hex) {
    return ToBinary<4>(hex, HexDigitToDecimal);
}
