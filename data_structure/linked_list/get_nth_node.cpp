#include "3rdParty/prettyprint.hpp"

#include "singly_linked_list.h"


const std::vector<int> SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};

auto testGetNIterative(const std::vector<int> &array, const std::size_t index) {
    SinglyLinkedList list {array};
    return list.GetNIterative(index);
}

auto testGetNRecursive(const std::vector<int> &array, const std::size_t index) {
    SinglyLinkedList list {array};
    return list.GetNRecursive(index);
}

SIMPLE_TEST(testGetNIterative, TestSampleHead, SAMPLE_ARRAY[0], SAMPLE_ARRAY, 0);
SIMPLE_TEST(testGetNIterative, TestSampleTail, SAMPLE_ARRAY[SAMPLE_ARRAY.size() - 1], SAMPLE_ARRAY,
            SAMPLE_ARRAY.size() - 1);
SIMPLE_TEST(testGetNIterative, TestSample, SAMPLE_ARRAY[5], SAMPLE_ARRAY, 5);

SIMPLE_TEST(testGetNRecursive, TestSampleHead, SAMPLE_ARRAY[0], SAMPLE_ARRAY, 0);
SIMPLE_TEST(testGetNRecursive, TestSampleTail, SAMPLE_ARRAY[SAMPLE_ARRAY.size() - 1], SAMPLE_ARRAY,
            SAMPLE_ARRAY.size() - 1);
SIMPLE_TEST(testGetNRecursive, TestSample, SAMPLE_ARRAY[5], SAMPLE_ARRAY, 5);
