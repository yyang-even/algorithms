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
 * You are given an array of 0s and 1s in random order. Segregate 0s on left side and
 * 1s on right side of the array. Traverse array only once.
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
 */
auto Segregate0sAnd1sCount(ArrayType values) {
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

}//namespace


const ArrayType VALUES1 = {};
const ArrayType VALUES2 = {1};
const ArrayType VALUES3 = {0, 1};
const ArrayType VALUES4 = {0, 1, 0, 1, 1, 1};
const ArrayType EXPECTED4 = {0, 0, 1, 1, 1, 1};
const ArrayType VALUES5 = {0, 1, 0, 1, 0, 0, 1, 1, 1, 0};
const ArrayType EXPECTED5 = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1};


SIMPLE_BENCHMARK(Segregate0sAnd1sCount, VALUES5);

SIMPLE_TEST(Segregate0sAnd1sCount, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(Segregate0sAnd1sCount, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(Segregate0sAnd1sCount, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(Segregate0sAnd1sCount, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(Segregate0sAnd1sCount, TestSAMPLE5, EXPECTED5, VALUES5);


SIMPLE_BENCHMARK(Segregate0sAnd1sDNF, VALUES5);

SIMPLE_TEST(Segregate0sAnd1sDNF, TestSAMPLE1, VALUES1, VALUES1);
SIMPLE_TEST(Segregate0sAnd1sDNF, TestSAMPLE2, VALUES2, VALUES2);
SIMPLE_TEST(Segregate0sAnd1sDNF, TestSAMPLE3, VALUES3, VALUES3);
SIMPLE_TEST(Segregate0sAnd1sDNF, TestSAMPLE4, EXPECTED4, VALUES4);
SIMPLE_TEST(Segregate0sAnd1sDNF, TestSAMPLE5, EXPECTED5, VALUES5);
