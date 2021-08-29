#include "common_header.h"

#include "number_convertion.h"


namespace {

/** Similar RGB Color
 *
 * @reference   http://buttercola.blogspot.com/2019/03/leetcode-800-similar-rgb-color.html
 * @reference   https://www.cnblogs.com/grandyang/p/9296602.html
 *
 * In the following, every capital letter represents some hexadecimal digit from 0 to f.
 * The red-green-blue color "#AABBCC" can be written as "#ABC" in shorthand. For example,
 * "#15c" is shorthand for the color "#1155cc". Now, say the similarity between two
 * colors "#ABCDEF" and "#UVWXYZ" is abs((AB - UV)^2 + (CD - WX)^2 + (EF - YZ)^2). Given
 * the color "#ABCDEF", return a 7 character color that is most similar to #ABCDEF, and
 * has a shorthand (that is, it can be represented as some "#XYZ")
 */
auto SimilarRGBColor(std::string color) {
    for (std::size_t i = 1; i < color.size(); i += 2) {
        const auto v = std::stoi(color.substr(i, 2), nullptr, 16);
        const auto digit = v / 0x11 + (v % 0x11 > 8);
        color[i] = color[i + 1] = std::tolower(ToHexDigit(digit));
    }

    return color;
}

}//namespace


THE_BENCHMARK(SimilarRGBColor, "#09f166");

SIMPLE_TEST(SimilarRGBColor, TestSAMPLE1, "#11ee66", "#09f166");
SIMPLE_TEST(SimilarRGBColor, TestSAMPLE2, "#000000", "#010000");
