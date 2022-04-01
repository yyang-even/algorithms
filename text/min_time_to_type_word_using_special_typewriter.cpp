#include "common_header.h"


namespace {

/** Minimum Time to Type Word Using Special Typewriter
 *
 * @reference   https://leetcode.com/problems/minimum-time-to-type-word-using-special-typewriter/
 *
 * There is a special typewriter with lowercase English letters 'a' to 'z' arranged in a
 * circle with a pointer. A character can only be typed if the pointer is pointing to that
 * character. The pointer is initially pointing to the character 'a'.
 */
constexpr auto MinTimeToType(const std::string_view word) {
    int result = word.size();
    auto prev = 'a';
    for (const auto c : word) {
        const auto diff = std::abs(prev - c);
        result += std::min(diff, 26 - diff);
        prev = c;
    }

    return result;
}

}//namespace


THE_BENCHMARK(MinTimeToType, "abc");

SIMPLE_TEST(MinTimeToType, TestSAMPLE1, 5, "abc");
SIMPLE_TEST(MinTimeToType, TestSAMPLE2, 7, "bza");
SIMPLE_TEST(MinTimeToType, TestSAMPLE3, 34, "zjpc");
