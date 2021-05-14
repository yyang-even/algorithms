#include "common_header.h"


namespace {

using ArrayType = std::vector<unsigned>;

/** How to print dimensions of multidimensional array in C++
 *
 * @reference   https://www.geeksforgeeks.org/print-dimensions-multidimensional-array-c/
 * @reference   Initialization of a multidimensional arrays in C/C++
 *              https://www.geeksforgeeks.org/g-fact-44/
 * @reference   Passing a 2D array to a C++ function
 *              https://stackoverflow.com/questions/8767166/passing-a-2d-array-to-a-c-function
 */
template <typename T, std::size_t row_size>
constexpr inline void
DimensionsOfMultidimensionalArray(const T(&)[row_size], ArrayType &outputs) {
    outputs.push_back(row_size);
}

template <typename T, std::size_t row_size, std::size_t column_size>
constexpr inline void
DimensionsOfMultidimensionalArray(const T(&elements)[row_size][column_size],
                                  ArrayType &outputs) {
    outputs.push_back(row_size);
    DimensionsOfMultidimensionalArray(elements[0], outputs);
}


template <typename T>
constexpr inline
std::enable_if_t<std::rank<T>::value == 1>
DimensionsOfMultidimensionalArray_EnableIf(const T &, ArrayType &outputs) {
    outputs.push_back(std::extent<T>::value);
}

template <typename T>
constexpr inline
std::enable_if_t < std::rank<T>::value != 1 >
DimensionsOfMultidimensionalArray_EnableIf(const T &elements, ArrayType &outputs) {
    outputs.push_back(std::extent<T>::value);
    DimensionsOfMultidimensionalArray_EnableIf(elements[0], outputs);
}

}//namespace


#ifdef WANT_TESTS
#define TestDimensionsOfTwoDimensionalArray(funcName, testName, dimension1, dimension2) namespace { \
    TEST(DimensionsOfTwoDimensionalArrayTest, testName) {                                           \
        ArrayType outputs;                                                                          \
        constexpr int elements[dimension1][dimension2] = {};                                        \
        funcName(elements, outputs);                                                                \
                                                                                                    \
        const ArrayType EXPECTED_DIMENSIONS = {dimension1, dimension2};                             \
        EXPECT_EQ(EXPECTED_DIMENSIONS, outputs);                                                    \
    }                                                                                               \
}

#define TestDimensionsOfThreeDimensionalArray(funcName, testName, dimension1, dimension2, dimension3) namespace {   \
    TEST(DimensionsOfThreeDimensionalArrayTest, testName) {                                                         \
        ArrayType outputs;                                                                                          \
        constexpr int elements[dimension1][dimension2][dimension3] = {};                                            \
        funcName(elements, outputs);                                                                                \
                                                                                                                    \
        const ArrayType EXPECTED_DIMENSIONS = {dimension1, dimension2, dimension3};                                 \
        EXPECT_EQ(EXPECTED_DIMENSIONS, outputs);                                                                    \
    }                                                                                                               \
}


TestDimensionsOfTwoDimensionalArray(DimensionsOfMultidimensionalArray, TestSAMPLE1,
                                    5, 8);
TestDimensionsOfThreeDimensionalArray(DimensionsOfMultidimensionalArray, TestSAMPLE2,
                                      5, 8, 3);


TestDimensionsOfTwoDimensionalArray(DimensionsOfMultidimensionalArray_EnableIf,
                                    TestSAMPLE3, 5, 8);
TestDimensionsOfThreeDimensionalArray(DimensionsOfMultidimensionalArray_EnableIf,
                                      TestSAMPLE4, 5, 8, 3);
#endif
