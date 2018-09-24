#include "singly_linked_list.h"


const std::vector<int> SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};

auto testGetReverseNIterative(const std::vector<int> &array, const std::size_t index) {
    SinglyLinkedList list {array};
    return list.GetReverseNIterative(index);
}

auto testGetReverseNRecursive(const std::vector<int> &array, const std::size_t index) {
    SinglyLinkedList list {array};
    return list.GetReverseNRecursive(index);
}

auto testGetReverseNTwoPointers(const std::vector<int> &array, const std::size_t index) {
    SinglyLinkedList list {array};
    return list.GetReverseNTwoPointers(index);
}

SIMPLE_TEST(testGetReverseNIterative, TestSampleHead, SAMPLE_ARRAY[SAMPLE_ARRAY.size() - 1],
            SAMPLE_ARRAY, 0);
SIMPLE_TEST(testGetReverseNIterative, TestSampleTail, SAMPLE_ARRAY[0], SAMPLE_ARRAY,
            SAMPLE_ARRAY.size() - 1);
SIMPLE_TEST(testGetReverseNIterative, TestSample, SAMPLE_ARRAY[SAMPLE_ARRAY.size() - 5 - 1],
            SAMPLE_ARRAY, 5);

SIMPLE_TEST(testGetReverseNRecursive, TestSampleHead, SAMPLE_ARRAY[SAMPLE_ARRAY.size() - 1],
            SAMPLE_ARRAY, 0);
SIMPLE_TEST(testGetReverseNRecursive, TestSampleTail, SAMPLE_ARRAY[0], SAMPLE_ARRAY,
            SAMPLE_ARRAY.size() - 1);
SIMPLE_TEST(testGetReverseNRecursive, TestSample, SAMPLE_ARRAY[SAMPLE_ARRAY.size() - 5 - 1],
            SAMPLE_ARRAY, 5);

SIMPLE_TEST(testGetReverseNTwoPointers, TestSampleHead, SAMPLE_ARRAY[SAMPLE_ARRAY.size() - 1],
            SAMPLE_ARRAY, 0);
SIMPLE_TEST(testGetReverseNTwoPointers, TestSampleTail, SAMPLE_ARRAY[0], SAMPLE_ARRAY,
            SAMPLE_ARRAY.size() - 1);
SIMPLE_TEST(testGetReverseNTwoPointers, TestSample, SAMPLE_ARRAY[SAMPLE_ARRAY.size() - 5 - 1],
            SAMPLE_ARRAY, 5);
