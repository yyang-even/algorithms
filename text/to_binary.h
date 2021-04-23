#pragma once


template <unsigned Size>
static inline auto ToBinary(const std::string_view number,
                            const std::function<int(const char)> to_decimal) {
    std::stringstream ss_out;
    for (const auto digit : number) {
        ss_out << std::bitset<Size>(to_decimal(digit));
    }

    return ss_out.str();
}


/** Program to Convert Hexadecimal Number to Binary
 *
 * @reference   https://www.geeksforgeeks.org/program-to-convert-hexadecimal-number-to-binary/
 */
static inline auto HexToBinary(const std::string_view hex) {
    return ToBinary<4>(hex, HexDigitToDecimal);
}
