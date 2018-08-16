#include "3rdParty/prettyprint.hpp"

#include "singly_linked_list.h"


const std::vector<int> EMPTY_ARRAY {};
const std::vector<int> SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};
const std::vector<int> EXPECTED_REVERSE_ARRAY {9, 5, 4, 7, 3, 2, 6, 8, 0, 1};


auto testReverseIterative(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    list.ReverseIterative();
    return list.CopyToArray();
}

auto testReverseRecursive(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    list.ReverseRecursive();
    return list.CopyToArray();
}

SIMPLE_TEST(testReverseIterative, TestEmpty, EMPTY_ARRAY, EMPTY_ARRAY);
SIMPLE_TEST(testReverseIterative, TestSample, EXPECTED_REVERSE_ARRAY, SAMPLE_ARRAY);

SIMPLE_TEST(testReverseRecursive, TestEmpty, EMPTY_ARRAY, EMPTY_ARRAY);
SIMPLE_TEST(testReverseRecursive, TestSample, EXPECTED_REVERSE_ARRAY, SAMPLE_ARRAY);
