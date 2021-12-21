#include "common_header.h"


namespace {

/** Decode String
 *
 * @reference   https://leetcode.com/problems/decode-string/
 *
 * Given an encoded string, return its decoded string. The encoding rule is: k[encoded_string],
 * where the encoded_string inside the square brackets is being repeated exactly k times.
 * Note that k is guaranteed to be a positive integer. You may assume that the input string
 * is always valid; No extra white spaces, square brackets are well-formed, etc. Furthermore,
 * you may assume that the original data does not contain any digits and that digits are
 * only for those repeat numbers, k. For example, there won't be input like 3a or 2[4].
 */
void DecodeString_Recursive(const std::string_view s, std::size_t &i,
                            std::string &result) {
    int repeat = 0;
    while (i < s.size()) {
        const auto c = s[i++];
        if (std::isdigit(c)) {
            repeat = repeat * 10 + c - '0';
        } else if (c == '[') {
            std::string substr;
            DecodeString_Recursive(s, i, substr);
            while (repeat-- > 0) {
                result.append(substr);
            }
            repeat = 0;
        } else if (c == ']') {
            return;
        } else {
            result.push_back(c);
        }
    }
}

inline auto DecodeString_Recursive(const std::string_view s) {
    std::string result;
    std::size_t i = 0;
    DecodeString_Recursive(s, i, result);

    return result;
}

}//namespace


THE_BENCHMARK(DecodeString_Recursive, "3[a]2[bc]");

SIMPLE_TEST(DecodeString_Recursive, TestSAMPLE1, "aaabcbc", "3[a]2[bc]");
SIMPLE_TEST(DecodeString_Recursive, TestSAMPLE2, "accaccacc", "3[a2[c]]");
SIMPLE_TEST(DecodeString_Recursive, TestSAMPLE3, "abcabccdcdcdef", "2[abc]3[cd]ef");
SIMPLE_TEST(DecodeString_Recursive, TestSAMPLE4, "abccdcdcdxyz", "abc3[cd]xyz");
