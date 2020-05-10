#pragma once


static inline auto CreateHexDigitToDecimalMap() {
    std::unordered_map<char, int> hex_digit_to_decimal_map;
    for (int i = 0; i < 10; ++i) {
        hex_digit_to_decimal_map['0' + i] = i;
    }

    for (int i = 0; i < 6; ++i) {
        hex_digit_to_decimal_map['a' + i] = 10 + i;
        hex_digit_to_decimal_map['A' + i] = 10 + i;
    }

    return hex_digit_to_decimal_map;
}


static inline auto OctalDigitToDecimal(const char digit) {
    return digit - '0';
}


static inline auto HexDigitToDecimal(const char digit) {
    static const auto hex_digit_to_decimal_map = CreateHexDigitToDecimalMap();
    return hex_digit_to_decimal_map.at(digit);
}
