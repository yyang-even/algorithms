#pragma once


static inline constexpr auto
StartsWith(const std::string_view str, const std::string_view prefix) {
    return str.rfind(prefix, 0) == 0;
}


static inline constexpr auto
isVowel(const int c) {
    bool is_vowel[256] = {};
    is_vowel['A'] = true;
    is_vowel['E'] = true;
    is_vowel['I'] = true;
    is_vowel['O'] = true;
    is_vowel['U'] = true;
    is_vowel['a'] = true;
    is_vowel['e'] = true;
    is_vowel['i'] = true;
    is_vowel['o'] = true;
    is_vowel['u'] = true;

    return is_vowel[c];
}
