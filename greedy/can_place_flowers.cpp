#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Can Place Flowers
 *
 * @reference   https://leetcode.com/problems/can-place-flowers/
 *
 * You have a long flowerbed in which some of the plots are planted, and some are not.
 * However, flowers cannot be planted in adjacent plots. Given an integer array flowerbed
 * containing 0's and 1's, where 0 means empty and 1 means not empty, and an integer n,
 * return if n new flowers can be planted in the flowerbed without violating the
 * no-adjacent-flowers rule.
 */
auto CanPlaceFlowers(const ArrayType &flowerbed, int m) {
    for (std::size_t i = 0; i < flowerbed.size(); ++i) {
        if (m == 0) {
            break;
        }

        if (flowerbed[i] == 1) {
            ++i;
        } else if (i + 1 == flowerbed.size() or flowerbed[i + 1] == 0) {
            ++i;
            --m;
        }
    }

    return m == 0;
}

}//namespace


const ArrayType SAMPLE1 = {1, 0, 0, 0, 1};
const ArrayType SAMPLE2 = {0, 0, 0};


THE_BENCHMARK(CanPlaceFlowers, SAMPLE1, 2);

SIMPLE_TEST(CanPlaceFlowers, TestSAMPLE1, true, SAMPLE1, 1);
SIMPLE_TEST(CanPlaceFlowers, TestSAMPLE2, false, SAMPLE1, 2);
SIMPLE_TEST(CanPlaceFlowers, TestSAMPLE3, true, SAMPLE2, 2);
SIMPLE_TEST(CanPlaceFlowers, TestSAMPLE4, false, SAMPLE2, 3);
