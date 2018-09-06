#include "common_header.h"

#include "3rdParty/prettyprint.hpp"

using ArrayType = std::vector<unsigned>;

/** Find Duplicates of array using bit array
 *
 * @reference   https://www.geeksforgeeks.org/find-duplicates-of-array-using-bit-array/
 *
 * You have an array of N numbers, where N is at most 32,000. The array may have
 * duplicates entries and you do not know what N is. With only 4 Kilobytes of
 * memory available, how would print all duplicates elements in the array ?
 *
 * @complexity  O(n)
 */
auto FindAllDuplicatesBitArray(const ArrayType &elements) {
    std::vector<bool> counters{elements.size(), false};

    ArrayType output;
    for(const auto elem: elements){
        if(counters[elem])
            output.push_back(elem);
        else 
            counters[elem] = true;
    }
}


const ArrayType SAMPLE1 = {1, 5, 1, 10, 12, 10};
const ArrayType EXPECTED1 = {1, 10};
const ArrayType SAMPLE2 = {50, 40, 50};
const ArrayType EXPECTED2 = {50};

SIMPLE_BENCHMARK(FindAllDuplicatesBitArray, SAMPLE1);

SIMPLE_TEST(FindAllDuplicatesBitArray, TestSample1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(FindAllDuplicatesBitArray, TestSample2, EXPECTED2, SAMPLE2);
