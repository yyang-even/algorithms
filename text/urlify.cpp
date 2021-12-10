#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** URLify a given string (Replace spaces is %20)
 *
 * @reference   https://www.geeksforgeeks.org/urlify-given-string-replace-spaces/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 1.4.
 *
 * Write a method to replace all the spaces in a string with '%20'. You may assume that
 * the string has sufficient space at the end to hold the additional characters and that
 * you are given the "true" length of the string.
 *
 * @reference   Defanging an IP Address
 *              https://leetcode.com/problems/defanging-an-ip-address/
 *
 * Given a valid (IPv4) IP address, return a defanged version of that IP address. A
 * defanged IP address replaces every period "." with "[.]".
 */
auto URLify(std::string str, std::string::size_type length = 0) {
    if (length == 0) {
        length = str.size();
    }
    assert(length != 0);

    const auto cend = std::next(str.cbegin(), length);
    const auto space_count = std::count(str.cbegin(), cend, ' ');
    auto result_length = length + space_count * 2;

    str.resize(result_length);

    for (int i = length - 1; i >= 0; --i) {
        if (str[i] == ' ') {
            str[--result_length] = '0';
            str[--result_length] = '2';
            str[--result_length] = '%';
        } else {
            str[--result_length] = str[i];
        }
    }

    return str;
}


/**
 * @reference   Duplicate Zeros
 *              https://leetcode.com/problems/duplicate-zeros/
 *
 * Given a fixed-length integer array arr, duplicate each occurrence of zero, shifting
 * the remaining elements to the right. Note that elements beyond the length of the
 * original array are not written. Do the above modifications to the input array in place
 * and do not return anything.
 */
auto DuplicateZeros(ArrayType nums) {
    const int size = nums.size();
    int right = 0;
    int left = 0;
    for (; right < size; ++left) {
        if (nums[left] == 0) {
            right += 2;
        } else {
            ++right;
        }
    }

    --left;
    if (right-- > size) {
        nums.back() = 0;
        right -= 2;
        --left;
    }

    for (; left >= 0; --left) {
        if (nums[left] == 0) {
            nums[right--] = 0;
            nums[right--] = 0;
        } else {
            nums[right--] = nums[left];
        }
    }

    return nums;
}


/**
 * @reference   Replace Elements with Greatest Element on Right Side
 *              https://leetcode.com/problems/replace-elements-with-greatest-element-on-right-side/
 *
 * Given an array arr, replace every element in that array with the greatest element
 * among the elements to its right, and replace the last element with -1. After doing
 * so, return the array.
 */

}//namespace


THE_BENCHMARK(URLify, "Mr John Smith");

SIMPLE_TEST(URLify, TestSAMPLE1, "Mr%20John%20Smith", "Mr John Smith");
SIMPLE_TEST(URLify, TestSAMPLE2, "Mr%20John%20Smith", "Mr John Smith   ", 13);


const ArrayType SAMPLE1 = {1, 0, 2, 3, 0, 4, 5, 0};
const ArrayType EXPECTED1 = {1, 0, 0, 2, 3, 0, 0, 4};

const ArrayType SAMPLE2 = {1, 2, 3};

const ArrayType SAMPLE3 = {8, 4, 5, 0, 0, 0, 0, 7};
const ArrayType EXPECTED3 = {8, 4, 5, 0, 0, 0, 0, 0};


THE_BENCHMARK(DuplicateZeros, SAMPLE1);

SIMPLE_TEST(DuplicateZeros, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(DuplicateZeros, TestSAMPLE2, SAMPLE2, SAMPLE2);
SIMPLE_TEST(DuplicateZeros, TestSAMPLE3, EXPECTED3, SAMPLE3);
