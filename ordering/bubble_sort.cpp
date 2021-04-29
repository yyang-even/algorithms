#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Bubble Sort
 *
 * @reference   https://www.geeksforgeeks.org/bubble-sort/
 * @reference   Sorting Strings using Bubble Sort
 *              https://www.geeksforgeeks.org/sorting-strings-using-bubble-sort-2/
 * @reference   C Program for Bubble Sort
 *              https://www.geeksforgeeks.org/c-program-for-bubble-sort/
 * @reference   C++ Program for Bubble Sort
 *              https://www.geeksforgeeks.org/cpp-program-for-bubble-sort/
 * @reference   Stable sort for descending order
 *              https://www.geeksforgeeks.org/stable-sort-descending-order/
 *
 * @complexity: O(n^2)
 */
auto BubbleSort(ArrayType values) {
    const int last_i = static_cast<int>(values.size()) - 1;
    for (int i = 0, j, last_j; i < last_i; ++i) {
        for (j = 1, last_j = values.size() - i; j < last_j; ++j) {
            if (values[j - 1] > values[j]) {
                std::swap(values[j - 1], values[j]);
            }
        }
    }

    return values;
}

/** Bubble Sort Optimized
 *
 * @reference   https://www.geeksforgeeks.org/bubble-sort/
 *
 * @complexity: O(n^2) worst case; O(n) if the array is already sorted.
 */
auto BubbleSort_Optimized(ArrayType values) {
    const int last_i = static_cast<int>(values.size()) - 1;
    bool swapped;

    for (int i = 0, j, last_j; i < last_i; ++i) {
        for (j = 1, last_j = values.size() - i, swapped = false; j < last_j; ++j) {
            if (values[j - 1] > values[j]) {
                std::swap(values[j - 1], values[j]);
                swapped = true;
            }
        }

        if (not swapped) {
            break;
        }
    }

    return values;
}


/** Recursive Bubble Sort
 *
 * @reference   https://www.geeksforgeeks.org/recursive-bubble-sort/
 * @reference   C++ Program for Recursive Bubble Sort
 *              https://www.geeksforgeeks.org/cpp-program-for-recursive-bubble-sort/
 *
 * @complexity: O(n^2)
 */
void BubbleSort_Recursive(ArrayType &values, const typename ArrayType::size_type n) {
    if (n > 1) {
        for (typename ArrayType::size_type i = 1; i < n; ++i) {
            if (values[i - 1] > values[i]) {
                std::swap(values[i - 1], values[i]);
            }
        }

        BubbleSort_Recursive(values, n - 1);
    }
}
auto BubbleSort_Recursive(ArrayType values) {
    BubbleSort_Recursive(values, values.size());
    return values;
}


/** C Program for Bubble Sort on Linked List
 *
 * @reference   https://www.geeksforgeeks.org/c-program-bubble-sort-linked-list/
 * @reference   Bubble Sort for Linked List by Swapping nodes
 *              https://www.geeksforgeeks.org/bubble-sort-for-linked-list-by-swapping-nodes/
 */
auto BubbleSort_SinglyList(std::forward_list<int> values) {
    if (not values.empty()) {
        auto last = values.cend();
        for (bool swapped = true; swapped;) {
            swapped = false;
            auto before_iter = values.cbefore_begin();
            auto iter = std::next(before_iter);
            auto next = std::next(iter);
            for (; next != last;) {
                if (*iter > *next) {
                    values.splice_after(next, values, before_iter);
                    swapped = true;
                }
                ++before_iter;
                iter = std::next(before_iter);
                next = std::next(iter);
            }
            last = iter;
        }
    }

    return values;
}


/** Bubble sort using two Stacks
 *
 * @reference   https://www.geeksforgeeks.org/bubble-sort-using-two-stacks/
 */
auto BubbleSort_TwoStacks(ArrayType values) {
    using StackType = std::stack<ArrayType::value_type, ArrayType>;

    StackType s1(values);
    for (auto iter = values.rbegin(); iter != values.rend(); ++iter) {
        StackType s2;
        s2.push(std::move(s1.top()));
        s1.pop();
        while (not s1.empty()) {
            if (s2.top() > s1.top()) {
                std::swap(s1.top(), s2.top());
            } else {
                s2.push(std::move(s1.top()));
                s1.pop();
            }
        }

        *iter = std::move(s2.top());
        s2.pop();
        s1 = std::move(s2);
    }

    return values;
}

}//namespace


using InitializerType = std::initializer_list<ArrayType::value_type>;

constexpr InitializerType VALUES1 = {};
constexpr InitializerType VALUES2 = {1};
constexpr InitializerType VALUES3 = {1, 2};
constexpr InitializerType VALUES4 = {2, 3, 1};
constexpr InitializerType EXPECTED4 = {1, 2, 3};
constexpr InitializerType VALUES5 = {2, 3, 4, 1};
constexpr InitializerType EXPECTED5 = {1, 2, 3, 4};
constexpr InitializerType VALUES6 = {1, 2, 3, 1, 2, 2};
constexpr InitializerType EXPECTED6 = {1, 1, 2, 2, 2, 3};


SIMPLE_BENCHMARK(BubbleSort, Sample1, VALUES6);

SIMPLE_TEST(BubbleSort, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(BubbleSort, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(BubbleSort, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(BubbleSort, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(BubbleSort, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(BubbleSort, TestSAMPLE6, EXPECTED6, VALUES6);


SIMPLE_BENCHMARK(BubbleSort_Optimized, Sample1, VALUES6);

SIMPLE_TEST(BubbleSort_Optimized, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(BubbleSort_Optimized, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(BubbleSort_Optimized, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(BubbleSort_Optimized, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(BubbleSort_Optimized, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(BubbleSort_Optimized, TestSAMPLE6, EXPECTED6, VALUES6);


SIMPLE_BENCHMARK(BubbleSort_Recursive, Sample1, VALUES6);

SIMPLE_TEST(BubbleSort_Recursive, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(BubbleSort_Recursive, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(BubbleSort_Recursive, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(BubbleSort_Recursive, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(BubbleSort_Recursive, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(BubbleSort_Recursive, TestSAMPLE6, EXPECTED6, VALUES6);


SIMPLE_BENCHMARK(BubbleSort_SinglyList, Sample1, VALUES6);

SIMPLE_TEST(BubbleSort_SinglyList, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(BubbleSort_SinglyList, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(BubbleSort_SinglyList, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(BubbleSort_SinglyList, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(BubbleSort_SinglyList, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(BubbleSort_SinglyList, TestSAMPLE6, EXPECTED6, VALUES6);


SIMPLE_BENCHMARK(BubbleSort_TwoStacks, Sample1, VALUES6);

SIMPLE_TEST(BubbleSort_TwoStacks, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(BubbleSort_TwoStacks, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(BubbleSort_TwoStacks, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(BubbleSort_TwoStacks, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(BubbleSort_TwoStacks, TestSAMPLE5, EXPECTED5, VALUES5);
SIMPLE_TEST(BubbleSort_TwoStacks, TestSAMPLE6, EXPECTED6, VALUES6);
