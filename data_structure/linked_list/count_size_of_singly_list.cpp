#include "singly_list/singly_linked_list.h"


namespace {

const std::vector<int> EMPTY_ARRAY {};
const std::vector<int> SINGLE_ARRAY = {1};
const std::vector<int> EVEN_ARRAY = {1, 3};
const std::vector<int> ODD_ARRAY = {1, 2, 3};
const std::vector<int> SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};


auto testCountSize_Iterative(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    return list.CountSize_Iterative();
}


auto testCountSize_Recursive(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    return list.CountSize_Recursive();
}

}//namespace


SIMPLE_BENCHMARK(testCountSize_Iterative, SAMPLE_ARRAY);

SIMPLE_TEST(testCountSize_Iterative, TestEmpty, EMPTY_ARRAY.size(), EMPTY_ARRAY);
SIMPLE_TEST(testCountSize_Iterative, TestSingle, SINGLE_ARRAY.size(), SINGLE_ARRAY);
SIMPLE_TEST(testCountSize_Iterative, TestEven, EVEN_ARRAY.size(), EVEN_ARRAY);
SIMPLE_TEST(testCountSize_Iterative, TestOdd, ODD_ARRAY.size(), ODD_ARRAY);
SIMPLE_TEST(testCountSize_Iterative, TestSample, SAMPLE_ARRAY.size(), SAMPLE_ARRAY);


SIMPLE_BENCHMARK(testCountSize_Recursive, SAMPLE_ARRAY);

SIMPLE_TEST(testCountSize_Recursive, TestEmpty, EMPTY_ARRAY.size(), EMPTY_ARRAY);
SIMPLE_TEST(testCountSize_Recursive, TestSingle, SINGLE_ARRAY.size(), SINGLE_ARRAY);
SIMPLE_TEST(testCountSize_Recursive, TestEven, EVEN_ARRAY.size(), EVEN_ARRAY);
SIMPLE_TEST(testCountSize_Recursive, TestOdd, ODD_ARRAY.size(), ODD_ARRAY);
SIMPLE_TEST(testCountSize_Recursive, TestSample, SAMPLE_ARRAY.size(), SAMPLE_ARRAY);
