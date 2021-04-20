#pragma once

#include <charconv>


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


const auto BinaryDigitToDecimal = OctalDigitToDecimal;


static inline auto CreateBinaryToOctalDigitMap() {
    std::unordered_map<std::string, char> binary_to_octal_digit_map = {
        {"00", '0'},
        {"0", '0'},
        {"01", '1'},
        {"1", '1'},
        {"10", '2'},
        {"11", '3'},
    };

    for (int i = 0; i < 8; ++i) {
        binary_to_octal_digit_map[std::bitset<3>(i).to_string()] = '0' + i;
    }

    return binary_to_octal_digit_map;
}


static inline auto CreateBinaryToHexDigitMap() {
    std::unordered_map<std::string, char> binary_to_hex_digit_map = {
        {"1", '1'},
        {"10", '2'},
        {"11", '3'},
        {"100", '4'},
        {"101", '5'},
        {"110", '6'},
        {"111", '7'},
    };

    for (int i = 0; i < 10; ++i) {
        binary_to_hex_digit_map[std::bitset<4>(i).to_string()] = '0' + i;
    }

    for (int i = 0; i < 6; ++i) {
        binary_to_hex_digit_map[std::bitset<4>(10 + i).to_string()] = 'A' + i;
    }

    return binary_to_hex_digit_map;
}


static inline auto from_string_view(const std::string_view sv, const int base = 10) {
    int value{};

    const auto result = std::from_chars(sv.data(), sv.data() + sv.size(), value, base);
    if (result.ec == std::errc::invalid_argument) {
        throw std::invalid_argument{"invalid_argument"};
    } else if (result.ec == std::errc::result_out_of_range) {
        throw std::out_of_range{"out_of_range"};
    }

    return value;
}
