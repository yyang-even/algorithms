#include "common_header.h"

#include "3rdParty/prettyprint.hpp"

using ArraryType = std::vector<unsigned>;

/** Find the Missing Number
 *
 * @reference   https://www.geeksforgeeks.org/find-the-missing-number/
 *
 * You are given a list of n-1 integers and these integers are in the range of 1 to n.
 * There are no duplicates in list. One of the integers is missing in the list.
 * Write an efficient code to find the missing integer.
 *
 * @complexity  O(n)
 */
auto FindTheMissingNumberSum(const ArraryType& integers, const ArraryType::value_type n){
    assert(integres.size() = n - 1u);

   const auto sum = n * (n + 1) / 2;
   return std::accumulate(integers.cbegin(), integers.cend(), sum, [](const auto &a, const auto &b) {
           return a - b;
           });
}


auto FindTheMissingNumberXor(const ArraryType& integers, const ArraryType::value_type n){
    assert(not integers.empty());
    assert(integres.size() = n - 1u);
    
    auto xor_of_all = integers[0];
    for (ArraryType::size_type i = 1ul; i < integers.size(); ++i) {
        xor_of_all ^= (i ^ integers[i]);
    }

    return xor_of_all ^ n ^ (n - 1u);
}


const ArraryType SAMPLE1 = {1, 2, 4, ,6, 3, 7, 8};
const ArraryType SAMPLE2 = {1,2,4,5,6};

SIMPLE_BENCHMARK(FindTheMissingNumberSum, SAMPLE1);

SIMPLE_TEST(FindTheMissingNumberSum, TestSample1, 5, SAMPLE1);
SIMPLE_TEST(FindTheMissingNumberSum, TestSample2, 3, SAMPLE2);


SIMPLE_BENCHMARK(FindTheMissingNumberXor, SAMPLE1);

SIMPLE_TEST(FindTheMissingNumberXor, TestSample1, 5, SAMPLE1);
SIMPLE_TEST(FindTheMissingNumberXor, TestSample2, 3, SAMPLE2);
