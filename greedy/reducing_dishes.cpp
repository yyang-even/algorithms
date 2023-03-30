#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Reducing Dishes
 *
 * @reference   https://leetcode.com/problems/reducing-dishes/
 *
 * A chef has collected data on the satisfaction level of his n dishes. Chef can cook any dish in 1 unit
 * of time.
 * Like-time coefficient of a dish is defined as the time taken to cook that dish including previous
 * dishes multiplied by its satisfaction level i.e. time[i] * satisfaction[i].
 * Return the maximum sum of like-time coefficient that the chef can obtain after dishes preparation.
 * Dishes can be prepared in any order and the chef can discard some dishes to get this maximum value.
 */
auto ReducingDishes(ArrayType satisfaction) {
    std::sort(satisfaction.begin(), satisfaction.end(), std::greater<int> {});

    int result = 0;
    int sum = 0;
    for (const auto s : satisfaction) {
        if (sum + s <= 0) {
            break;
        }

        sum += s;
        result += sum;
    }

    return result;
}

} //namespace


const ArrayType SAMPLE1 = {-1, -8, 0, 5, -9};
const ArrayType SAMPLE2 = {4, 3, 2};
const ArrayType SAMPLE3 = {-1, -4, -5};


THE_BENCHMARK(ReducingDishes, SAMPLE1);

SIMPLE_TEST(ReducingDishes, TestSAMPLE1, 14, SAMPLE1);
SIMPLE_TEST(ReducingDishes, TestSAMPLE2, 20, SAMPLE2);
SIMPLE_TEST(ReducingDishes, TestSAMPLE3, 0, SAMPLE3);
