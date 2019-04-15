#include "singly_linked_list.h"


const std::vector<int> EMPTY_ARRAY {};
const std::vector<int> SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};
const std::vector<int> EXPECTED_REVERSE_ARRAY {9, 5, 4, 7, 3, 2, 6, 8, 0, 1};


auto testReverse_Iterative(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    list.Reverse_Iterative();
    return list.CopyToArray();
}

auto testReverse_Recursive(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    list.Reverse_Recursive();
    return list.CopyToArray();
}

SIMPLE_TEST(testReverse_Iterative, TestEmpty, EMPTY_ARRAY, EMPTY_ARRAY);
SIMPLE_TEST(testReverse_Iterative, TestSample, EXPECTED_REVERSE_ARRAY, SAMPLE_ARRAY);

SIMPLE_TEST(testReverse_Recursive, TestEmpty, EMPTY_ARRAY, EMPTY_ARRAY);
SIMPLE_TEST(testReverse_Recursive, TestSample, EXPECTED_REVERSE_ARRAY, SAMPLE_ARRAY);
