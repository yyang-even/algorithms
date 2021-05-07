#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Maximum and minimum of an array using minimum number of comparisons
 *
 * @reference   https://www.geeksforgeeks.org/maximum-and-minimum-in-an-array/
 * @reference   Find minimum and maximum elements in singly Circular Linked List
 *              https://www.geeksforgeeks.org/find-minimum-and-maximum-elements-in-singly-circular-linked-list/
 *
 * @reference   Second minimum element using minimum comparisons
 *              https://www.geeksforgeeks.org/second-minimum-element-using-minimum-comparisons/
 *
 * Given an array of integers, find the minimum (or maximum) element and the element just
 * greater (or smaller) than that in less than 2n comparisons. The given array is not
 * necessarily sorted. Extra space is allowed.
 */
auto MaxAndMin_Linear(const ArrayType &values) {
    assert(not values.empty());

    if (values.size() == 1) {
        return std::pair(values.front(), values.front());
    }
    auto min_iter = values.cbegin();
    auto max_iter = std::next(min_iter);
    if (*min_iter > *max_iter) {
        std::swap(min_iter, max_iter);
    }

    for (auto iter = values.cbegin() + 2; iter != values.cend(); ++iter) {
        if (*iter > *max_iter) {
            max_iter = iter;
        } else if (*iter < *min_iter) {
            min_iter = iter;
        }
    }

    return std::pair(*max_iter, *min_iter);
}


auto MaxAndMin_Tournament(const ArrayType::const_iterator cbegin,
                          const ArrayType::size_type size) {
    if (size == 1) {
        return std::pair(*cbegin, *cbegin);
    } else if (size == 2) {
        auto min_iter = cbegin;
        auto max_iter = std::next(min_iter);
        if (*min_iter > *max_iter) {
            std::swap(min_iter, max_iter);
        }

        return std::pair(*max_iter, *min_iter);
    } else {
        const auto half = size / 2;
        const auto [left_max, left_min] = MaxAndMin_Tournament(cbegin, half);
        const auto [right_max, right_min] = MaxAndMin_Tournament(std::next(cbegin, half),
                                                                 size - half);

        return std::pair(std::max(left_max, right_max),
                         std::min(left_min, right_min));
    }
}

inline auto MaxAndMin_Tournament(const ArrayType &values) {
    assert(not values.empty());

    return MaxAndMin_Tournament(values.cbegin(), values.size());
}


auto MaxAndMin_Pair(const ArrayType &values) {
    assert(not values.empty());

    auto min_iter = values.cbegin();
    auto max_iter = min_iter;
    auto iter = std::next(min_iter);
    if (values.size() % 2 == 0) {
        max_iter = iter++;
        if (*min_iter > *max_iter) {
            std::swap(min_iter, max_iter);
        }
    }

    for (; iter != values.cend(); std::advance(iter, 2)) {
        auto temp_min_iter = iter;
        auto temp_max_iter = std::next(temp_min_iter);
        if (*temp_min_iter > *temp_max_iter) {
            std::swap(temp_min_iter, temp_max_iter);
        }
        if (*temp_min_iter < *min_iter) {
            min_iter = temp_min_iter;
        }
        if (*temp_max_iter > *max_iter) {
            max_iter = temp_max_iter;
        }
    }

    return std::pair(*max_iter, *min_iter);
}


/** Sum and Product of minimum and maximum element of an Array
 *
 * @reference   https://www.geeksforgeeks.org/sum-and-product-of-minimum-and-maximum-element-of-an-array/
 */

}//namespace


const ArrayType VALUES1 = {1};
const ArrayType VALUES2 = {1, 2};
const ArrayType VALUES3 = {4, 8, 12, 16};
const ArrayType VALUES4 = {15, 0, 2, 15};


THE_BENCHMARK(MaxAndMin_Linear, VALUES4);

SIMPLE_TEST(MaxAndMin_Linear, TestSAMPLE1, std::pair(1, 1), VALUES1);
SIMPLE_TEST(MaxAndMin_Linear, TestSAMPLE2, std::pair(2, 1), VALUES2);
SIMPLE_TEST(MaxAndMin_Linear, TestSAMPLE3, std::pair(16, 4), VALUES3);
SIMPLE_TEST(MaxAndMin_Linear, TestSAMPLE4, std::pair(15, 0), VALUES4);


THE_BENCHMARK(MaxAndMin_Tournament, VALUES4);

SIMPLE_TEST(MaxAndMin_Tournament, TestSAMPLE1, std::pair(1, 1), VALUES1);
SIMPLE_TEST(MaxAndMin_Tournament, TestSAMPLE2, std::pair(2, 1), VALUES2);
SIMPLE_TEST(MaxAndMin_Tournament, TestSAMPLE3, std::pair(16, 4), VALUES3);
SIMPLE_TEST(MaxAndMin_Tournament, TestSAMPLE4, std::pair(15, 0), VALUES4);


THE_BENCHMARK(MaxAndMin_Pair, VALUES4);

SIMPLE_TEST(MaxAndMin_Pair, TestSAMPLE1, std::pair(1, 1), VALUES1);
SIMPLE_TEST(MaxAndMin_Pair, TestSAMPLE2, std::pair(2, 1), VALUES2);
SIMPLE_TEST(MaxAndMin_Pair, TestSAMPLE3, std::pair(16, 4), VALUES3);
SIMPLE_TEST(MaxAndMin_Pair, TestSAMPLE4, std::pair(15, 0), VALUES4);
