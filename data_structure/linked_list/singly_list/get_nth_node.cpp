#include "singly_linked_list.h"


namespace {

inline auto testGetN_Iterative(const std::vector<int> &array, const std::size_t index) {
    SinglyLinkedList list {array};
    return list.GetN_Iterative(index);
}

inline auto testGetN_Recursive(const std::vector<int> &array, const std::size_t index) {
    SinglyLinkedList list {array};
    return list.GetN_Recursive(index);
}

}//namespace


const std::vector<int> SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};


THE_BENCHMARK(testGetN_Iterative, SAMPLE_ARRAY, SAMPLE_ARRAY.size() - 1);

SIMPLE_TEST(testGetN_Iterative, TestSampleHead, SAMPLE_ARRAY[0], SAMPLE_ARRAY, 0);
SIMPLE_TEST(testGetN_Iterative, TestSampleTail, SAMPLE_ARRAY[SAMPLE_ARRAY.size() - 1],
            SAMPLE_ARRAY, SAMPLE_ARRAY.size() - 1);
SIMPLE_TEST(testGetN_Iterative, TestSample, SAMPLE_ARRAY[5], SAMPLE_ARRAY, 5);


THE_BENCHMARK(testGetN_Recursive, SAMPLE_ARRAY, SAMPLE_ARRAY.size() - 1);

SIMPLE_TEST(testGetN_Recursive, TestSampleHead, SAMPLE_ARRAY[0], SAMPLE_ARRAY, 0);
SIMPLE_TEST(testGetN_Recursive, TestSampleTail, SAMPLE_ARRAY[SAMPLE_ARRAY.size() - 1],
            SAMPLE_ARRAY, SAMPLE_ARRAY.size() - 1);
SIMPLE_TEST(testGetN_Recursive, TestSample, SAMPLE_ARRAY[5], SAMPLE_ARRAY, 5);
