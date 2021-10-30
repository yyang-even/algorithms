#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Segregate 0s and 1s in an array
 *
 * @reference   Segregate 0s and 1s in an array
 *              https://www.geeksforgeeks.org/segregate-0s-and-1s-in-an-array-by-traversing-array-once/
 * @reference   Dutch National Flag
 *              http://users.monash.edu/~lloyd/tildeAlgDS/Sort/Flag/
 *
 * You are given an array of 0s and 1s in random order. Segregate 0s on left side and 1s
 * on right side of the array. Traverse array only once.
 *
 * @reference   Segregate Even and Odd numbers
 *              https://www.geeksforgeeks.org/segregate-even-and-odd-numbers/
 * @reference   Segregate even and odd numbers | Set 2
 *              https://www.geeksforgeeks.org/segregate-even-odd-set-2/
 * @reference   Segregate even and odd numbers | Set 3
 *              https://www.geeksforgeeks.org/segregate-even-odd-numbers-set-3/
 *
 * Given an array A[], write a function that segregates even and odd numbers. The
 * functions should put all even numbers first, and then odd numbers.
 *
 * @reference   Sort Array By Parity
 *              https://leetcode.com/problems/sort-array-by-parity/
 *
 * Given an integer array nums, move all the even integers at the beginning of the array
 * followed by all the odd integers. Return any array that satisfies this condition.
 */
inline auto Segregate0sAnd1sCount(ArrayType values) {
    const auto number_of_0s = std::count(values.cbegin(), values.cend(), 0);
    std::fill_n(values.begin(), number_of_0s, 0);
    std::fill(values.begin() + number_of_0s, values.end(), 1);

    return values;
}


auto Segregate0sAnd1sDNF(ArrayType values) {
    auto zeros_end = values.begin();
    for (auto ones_begin = values.end(); zeros_end != ones_begin;) {
        if (*zeros_end == 1) {
            std::iter_swap(zeros_end, --ones_begin);
        } else {
            ++zeros_end;
        }
    }

    return values;
}


auto SegregateEvenOdd(ArrayType nums) {
    std::size_t even = 0;
    for (std::size_t i = 0; i < nums.size(); ++i) {
        if (nums[i] % 2 == 0) {
            std::swap(nums[i], nums[even++]);
        }
    }

    return nums;
}


/** Sort an array of 0s, 1s and 2s
 *
 * @reference   Sort an array of 0s, 1s and 2s (Simple Counting)
 *              https://www.geeksforgeeks.org/sort-array-0s-1s-2s-simple-counting/
 * @reference   Sort an array of 0s, 1s and 2s
 *              https://www.geeksforgeeks.org/sort-an-array-of-0s-1s-and-2s/
 *
 * Given an array A[] consisting 0s, 1s and 2s, write a function that sorts A[]. The
 * functions should put all 0s first, then all 1s and all 2s in last.
 *
 * @reference   Sorting objects using In-Place sorting algorithm
 *              https://www.geeksforgeeks.org/sorting-objects-using-in-place-sorting-algorithm/
 * @reference   Sorting Terminology
 *              https://www.geeksforgeeks.org/sorting-terminology/
 *
 * Given an array of red, blue and yellow objects, the task is to use an in-place sorting
 * algorithm to sort the array in such a way that all the blue objects appear before all
 * the red objects and all the red objects appear before all the yellow objects.
 *
 * @reference   Sort Colors
 *              https://leetcode.com/problems/sort-colors/
 *
 * Given an array nums with n objects colored red, white, or blue, sort them in-place so
 * that objects of the same color are adjacent, with the colors in the order red, white,
 * and blue. We will use the integers 0, 1, and 2 to represent the color red, white, and
 * blue, respectively. You must solve this problem without using the library's sort function.
 */
auto Sort0s1s2s(ArrayType values) {
    auto zeros_end = values.begin();
    auto twos_begin = values.end();
    for (auto ones_end = zeros_end; ones_end != twos_begin;) {
        if (*ones_end == 0) {
            std::iter_swap(zeros_end++, ones_end++);
        } else if (*ones_end == 1) {
            ++ones_end;
        } else {
            std::iter_swap(ones_end, --twos_begin);
        }
    }

    return values;
}


auto Sort0s1s2s_Index(ArrayType nums) {
    int left = 0;
    int right = nums.size() - 1;
    for (int i = 0; i <= right; ++i) {
        if (nums[i] == 0) {
            std::swap(nums[i], nums[left++]);
        } else if (nums[i] == 2) {
            std::swap(nums[i--], nums[right--]);
        }
    }

    return nums;
}


/**
 * @reference   Move all zeros to start and ones to end in an Array of random integers
 *              https://www.geeksforgeeks.org/move-all-zeros-to-start-and-ones-to-end-in-an-array-of-random-integers/
 *
 * Given an array arr[] of random integers, the task is to push all the zero's in the
 * array to the start and all the one's to the end of the array. Note that the order of
 * all the other elements should be the same.
 */

}//namespace


const ArrayType VALUES1 = {};
const ArrayType VALUES2 = {1};
const ArrayType VALUES3 = {0, 1};
const ArrayType VALUES4 = {0, 1, 0, 1, 1, 1};
const ArrayType EXPECTED4 = {0, 0, 1, 1, 1, 1};
const ArrayType VALUES5 = {0, 1, 0, 1, 0, 0, 1, 1, 1, 0};
const ArrayType EXPECTED5 = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1};


THE_BENCHMARK(Segregate0sAnd1sCount, VALUES5);

SIMPLE_TEST(Segregate0sAnd1sCount, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(Segregate0sAnd1sCount, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(Segregate0sAnd1sCount, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(Segregate0sAnd1sCount, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(Segregate0sAnd1sCount, TestSAMPLE5, EXPECTED5, VALUES5);


THE_BENCHMARK(SegregateEvenOdd, VALUES5);

SIMPLE_TEST(SegregateEvenOdd, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(SegregateEvenOdd, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(SegregateEvenOdd, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(SegregateEvenOdd, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(SegregateEvenOdd, TestSAMPLE5, EXPECTED5, VALUES5);


THE_BENCHMARK(Segregate0sAnd1sDNF, VALUES5);

SIMPLE_TEST(Segregate0sAnd1sDNF, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(Segregate0sAnd1sDNF, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(Segregate0sAnd1sDNF, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(Segregate0sAnd1sDNF, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(Segregate0sAnd1sDNF, TestSAMPLE5, EXPECTED5, VALUES5);


const ArrayType VALUES6 = {0, 1, 2, 0, 1, 2};
const ArrayType EXPECTED6 = {0, 0, 1, 1, 2, 2};
const ArrayType VALUES7 = {0, 1, 1, 0, 1, 2, 1, 2, 0, 0, 0, 1};
const ArrayType EXPECTED7 = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2};


THE_BENCHMARK(Sort0s1s2s, VALUES5);

SIMPLE_TEST(Sort0s1s2s, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(Sort0s1s2s, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(Sort0s1s2s, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(Sort0s1s2s, TestSAMPLE6, EXPECTED6, VALUES6);
SIMPLE_TEST(Sort0s1s2s, TestSAMPLE7, EXPECTED7, VALUES7);


THE_BENCHMARK(Sort0s1s2s_Index, VALUES5);

SIMPLE_TEST(Sort0s1s2s_Index, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(Sort0s1s2s_Index, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(Sort0s1s2s_Index, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(Sort0s1s2s_Index, TestSAMPLE6, EXPECTED6, VALUES6);
SIMPLE_TEST(Sort0s1s2s_Index, TestSAMPLE7, EXPECTED7, VALUES7);
