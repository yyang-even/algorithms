#include "common_header.h"

using ArrayType = std::vector<int>;
/** Pair with given product | Set 1 (Find if any pair exists)
 *
 * @reference   https://www.geeksforgeeks.org/pair-with-given-product-set-1-find-if-any-pair-exists/
 *
 * Given an array of distinct elements and a number x, find if there is a pair with product equal to x.
 */
INT_BOOL PairElementsProductAsN(const ArrayType &elements, const ArrayType::value_type N){
    std::unordered_set<ArrayType::value_type> value_set{};

    for(const auto elem: elements){
        if(elem == 0 and N == 0) {
            return true;
        }

        if(N%elem == 0){
            if(value_set.find(N/elem) != value_set.cend())
                return true;
            value_set.insert(elem);
        }
    }

    return false;
}


const ArrayType SAMPLE1 = {10, 20, 9, 40};
const ArrayType SAMPLE2 = {10, 20, 9, 40};
const ArrayType SAMPLE3 = {-10, 20, 9, -40};
const ArrayType SAMPLE4 = {-10, 20, 9, 40};
const ArrayType SAMPLE5 = {0, 20, 9, 40};

SIMPLE_BENCHMARK(PairElementsProductAsN, SAMPLE1, 33);

SIMPLE_TEST(PairElementsProductAsN, TestSample1, TRUE, SAMPLE1, 400);
SIMPLE_TEST(PairElementsProductAsN, TestSample2, FALSE, SAMPLE2, 190);
SIMPLE_TEST(PairElementsProductAsN, TestSample3, TRUE, SAMPLE3, 400);
SIMPLE_TEST(PairElementsProductAsN, TestSample4, TRUE, SAMPLE4, -400);
SIMPLE_TEST(PairElementsProductAsN, TestSample5, TRUE, SAMPLE5, 0);
