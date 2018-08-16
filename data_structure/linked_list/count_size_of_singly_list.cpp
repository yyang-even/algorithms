#include "3rdParty/prettyprint.hpp"

#include "singly_linked_list.h"


const std::vector<int> EMPTY_ARRAY {};
const std::vector<int> SINGLE_ARRAY {
    1
};
const std::vector<int> EVEN_ARRAY {
    1, 3
};
const std::vector<int> ODD_ARRAY {
    1, 2, 3
};
const std::vector<int> SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};
const auto EXPECTED_SIZE = SAMPLE_ARRAY.size();


auto testCountSizeIterative(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    return list.CountSizeIterative();
}

SIMPLE_TEST(testCountSizeIterative, TestEmpty, 0, EMPTY_ARRAY);
SIMPLE_TEST(testCountSizeIterative, TestSingle, 1, SINGLE_ARRAY);
SIMPLE_TEST(testCountSizeIterative, TestEven, 2, EVEN_ARRAY);
SIMPLE_TEST(testCountSizeIterative, TestOdd, 3, ODD_ARRAY);
SIMPLE_TEST(testCountSizeIterative, TestSample, EXPECTED_SIZE, SAMPLE_ARRAY);


auto testCountSizeRecursive(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    return list.CountSizeRecursive();
}

SIMPLE_TEST(testCountSizeRecursive, TestEmpty, 0, EMPTY_ARRAY);
SIMPLE_TEST(testCountSizeRecursive, TestSingle, 1, SINGLE_ARRAY);
SIMPLE_TEST(testCountSizeRecursive, TestEven, 2, EVEN_ARRAY);
SIMPLE_TEST(testCountSizeRecursive, TestOdd, 3, ODD_ARRAY);
SIMPLE_TEST(testCountSizeRecursive, TestSample, EXPECTED_SIZE, SAMPLE_ARRAY);
