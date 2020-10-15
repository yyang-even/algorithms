#include "singly_linked_list.h"


namespace {

const std::vector<int> SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};

auto testGetReverseN_Iterative(const std::vector<int> &array, const std::size_t index) {
    SinglyLinkedList list {array};
    return list.GetReverseN_Iterative(index);
}

auto testGetReverseN_Recursive(const std::vector<int> &array, const std::size_t index) {
    SinglyLinkedList list {array};
    return list.GetReverseN_Recursive(index);
}

auto testGetReverseN_TwoPointers(const std::vector<int> &array,
                                 const std::size_t index) {
    SinglyLinkedList list {array};
    return list.GetReverseN_TwoPointers(index);
}

}//namespace


SIMPLE_BENCHMARK(testGetReverseN_Iterative, Sample1, SAMPLE_ARRAY, 5);

SIMPLE_TEST(testGetReverseN_Iterative, TestSampleHead,
            SAMPLE_ARRAY[SAMPLE_ARRAY.size() - 1],
            SAMPLE_ARRAY, 0);
SIMPLE_TEST(testGetReverseN_Iterative, TestSampleTail, SAMPLE_ARRAY[0], SAMPLE_ARRAY,
            SAMPLE_ARRAY.size() - 1);
SIMPLE_TEST(testGetReverseN_Iterative, TestSample,
            SAMPLE_ARRAY[SAMPLE_ARRAY.size() - 5 - 1],
            SAMPLE_ARRAY, 5);


SIMPLE_BENCHMARK(testGetReverseN_Recursive, Sample1, SAMPLE_ARRAY, 5);

SIMPLE_TEST(testGetReverseN_Recursive, TestSampleHead,
            SAMPLE_ARRAY[SAMPLE_ARRAY.size() - 1],
            SAMPLE_ARRAY, 0);
SIMPLE_TEST(testGetReverseN_Recursive, TestSampleTail, SAMPLE_ARRAY[0], SAMPLE_ARRAY,
            SAMPLE_ARRAY.size() - 1);
SIMPLE_TEST(testGetReverseN_Recursive, TestSample,
            SAMPLE_ARRAY[SAMPLE_ARRAY.size() - 5 - 1],
            SAMPLE_ARRAY, 5);


SIMPLE_BENCHMARK(testGetReverseN_TwoPointers, Sample1, SAMPLE_ARRAY, 5);

SIMPLE_TEST(testGetReverseN_TwoPointers, TestSampleHead,
            SAMPLE_ARRAY[SAMPLE_ARRAY.size() - 1],
            SAMPLE_ARRAY, 0);
SIMPLE_TEST(testGetReverseN_TwoPointers, TestSampleTail, SAMPLE_ARRAY[0], SAMPLE_ARRAY,
            SAMPLE_ARRAY.size() - 1);
SIMPLE_TEST(testGetReverseN_TwoPointers, TestSample,
            SAMPLE_ARRAY[SAMPLE_ARRAY.size() - 5 - 1],
            SAMPLE_ARRAY, 5);
