#include "singly_linked_list.h"
#include "singly_circular_linked_list.h"


namespace {

inline auto testReverse_Iterative(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    list.Reverse_Iterative();
    return list.CopyToArray();
}


inline auto testReverse_Recursive(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    list.Reverse_Recursive();
    return list.CopyToArray();
}


inline auto testReverse_TwoPointers(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    list.Reverse_TwoPointers();
    return list.CopyToArray();
}


inline auto testReverse_Stack(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    list.Reverse_Stack();
    return list.CopyToArray();
}


inline auto testReverse_Circular(const std::vector<int> &array) {
    SinglyCircularLinkedList list {array};
    list.Reverse();
    return list.CopyToArray();
}

}//namespace


const std::vector<int> EMPTY_ARRAY {};
const std::vector<int> SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};
const std::vector<int> EXPECTED_REVERSE_ARRAY {9, 5, 4, 7, 3, 2, 6, 8, 0, 1};


THE_BENCHMARK(testReverse_Iterative, SAMPLE_ARRAY);

SIMPLE_TEST(testReverse_Iterative, TestEmpty, EMPTY_ARRAY, EMPTY_ARRAY);
SIMPLE_TEST(testReverse_Iterative, TestSample, EXPECTED_REVERSE_ARRAY, SAMPLE_ARRAY);


THE_BENCHMARK(testReverse_Recursive, SAMPLE_ARRAY);

SIMPLE_TEST(testReverse_Recursive, TestEmpty, EMPTY_ARRAY, EMPTY_ARRAY);
SIMPLE_TEST(testReverse_Recursive, TestSample, EXPECTED_REVERSE_ARRAY, SAMPLE_ARRAY);


THE_BENCHMARK(testReverse_TwoPointers, SAMPLE_ARRAY);

SIMPLE_TEST(testReverse_TwoPointers, TestEmpty, EMPTY_ARRAY, EMPTY_ARRAY);
SIMPLE_TEST(testReverse_TwoPointers, TestSample, EXPECTED_REVERSE_ARRAY, SAMPLE_ARRAY);


THE_BENCHMARK(testReverse_Stack, SAMPLE_ARRAY);

SIMPLE_TEST(testReverse_Stack, TestEmpty, EMPTY_ARRAY, EMPTY_ARRAY);
SIMPLE_TEST(testReverse_Stack, TestSample, EXPECTED_REVERSE_ARRAY, SAMPLE_ARRAY);


THE_BENCHMARK(testReverse_Circular, SAMPLE_ARRAY);

SIMPLE_TEST(testReverse_Circular, TestEmpty, EMPTY_ARRAY, EMPTY_ARRAY);
SIMPLE_TEST(testReverse_Circular, TestSample, EXPECTED_REVERSE_ARRAY, SAMPLE_ARRAY);
