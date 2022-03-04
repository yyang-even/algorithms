#include "common_header.h"


namespace {

/** Champagne Tower
 *
 * @reference   https://leetcode.com/problems/champagne-tower/
 *
 * We stack glasses in a pyramid, where the first row has 1 glass, the second row has 2
 * glasses, and so on until the 100th row.  Each glass holds one cup of champagne.
 * Then, some champagne is poured into the first glass at the top.  When the topmost glass
 * is full, any excess liquid poured will fall equally to the glass immediately to the
 * left and right of it.  When those glasses become full, any excess champagne will fall
 * equally to the left and right of those glasses, and so on.  (A glass at the bottom row
 * has its excess champagne fall on the floor.)
 * For example, after one cup of champagne is poured, the top most glass is full.  After
 * two cups of champagne are poured, the two glasses on the second row are half full.
 * After three cups of champagne are poured, those two cups become full - there are 3 full
 * glasses total now.  After four cups of champagne are poured, the third row has the
 * middle glass half full, and the two outside glasses are a quarter full, as pictured below.
 */
constexpr auto
ChampagneTower(const double poured, const int query_row, const int query_glass) {
    double dp[query_row + 2] = {poured};

    for (int r = 1; r <= query_row; ++r) {
        for (int i = r; i >= 0; --i) {
            if (dp[i] > 1.0) {
                dp[i] = (dp[i] - 1.0) / 2.0;
                dp[i + 1] += dp[i];
            }
        }
    }

    return std::min(dp[query_glass], 1.0);
}

}//namespace


THE_BENCHMARK(ChampagneTower, 1, 1, 1);

SIMPLE_DOUBLE_TEST(ChampagneTower, TestSAMPLE1, 0, 1, 1, 1);
SIMPLE_DOUBLE_TEST(ChampagneTower, TestSAMPLE2, 0.5, 2, 1, 1);
SIMPLE_DOUBLE_TEST(ChampagneTower, TestSAMPLE3, 1, 100000009, 33, 17);
