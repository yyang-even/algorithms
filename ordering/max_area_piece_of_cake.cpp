#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Maximum Area of a Piece of Cake After Horizontal and Vertical Cuts
 *
 * @reference   https://leetcode.com/problems/maximum-area-of-a-piece-of-cake-after-horizontal-and-vertical-cuts/
 *
 * You are given a rectangular cake of size h x w and two arrays of integers horizontalCuts and
 * verticalCuts where:
 *  horizontalCuts[i] is the distance from the top of the rectangular cake to the ith horizontal
 *      cut and similarly, and
 *  verticalCuts[j] is the distance from the left of the rectangular cake to the jth vertical cut.
 * Return the maximum area of a piece of cake after you cut at each horizontal and vertical position
 * provided in the arrays horizontalCuts and verticalCuts. Since the answer can be a large number,
 * return this modulo 10^9 + 7.
 */
auto MaxAreaPieceOfCake(const int h,
                        const int w,
                        ArrayType horizontalCuts,
                        ArrayType verticalCuts) {
    std::sort(std::begin(horizontalCuts), std::end(horizontalCuts));
    auto max_horizontal_diff = std::max(horizontalCuts.front(), h - horizontalCuts.back());
    for (std::size_t i = 1; i < horizontalCuts.size(); ++i) {
        max_horizontal_diff =
            std::max(max_horizontal_diff, horizontalCuts[i] - horizontalCuts[i - 1]);
    }

    std::sort(std::begin(verticalCuts), std::end(verticalCuts));
    auto max_vertical_diff = std::max(verticalCuts.front(), w - verticalCuts.back());
    for (std::size_t i = 1; i < verticalCuts.size(); ++i) {
        max_vertical_diff = std::max(max_vertical_diff, verticalCuts[i] - verticalCuts[i - 1]);
    }

    return static_cast<unsigned long>(max_horizontal_diff) * max_vertical_diff % LARGE_PRIME;
}

} //namespace


const ArrayType SAMPLE1H = {1, 2, 4};
const ArrayType SAMPLE1V = {1, 3};

const ArrayType SAMPLE2H = {3, 1};
const ArrayType SAMPLE2V = {1};

const ArrayType SAMPLE3 = {3};


THE_BENCHMARK(MaxAreaPieceOfCake, 5, 4, SAMPLE1H, SAMPLE1V);

SIMPLE_TEST(MaxAreaPieceOfCake, TestSAMPLE1, 4, 5, 4, SAMPLE1H, SAMPLE1V);
SIMPLE_TEST(MaxAreaPieceOfCake, TestSAMPLE2, 6, 5, 4, SAMPLE2H, SAMPLE2V);
SIMPLE_TEST(MaxAreaPieceOfCake, TestSAMPLE3, 9, 5, 4, SAMPLE3, SAMPLE3);
