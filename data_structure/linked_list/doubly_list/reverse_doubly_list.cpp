#include "doubly_linked_list.h"
#include "doubly_circular_linked_list.h"


namespace {

bool testReverse(std::vector<int> array) {
    DoublyLinkedList list {array};
    list.Reverse();

    std::reverse(array.begin(), array.end());

    return list.CopyToArray() == array;
}


bool testReverse_Recursive(std::vector<int> array) {
    DoublyLinkedList list {array};
    list.Reverse_Recursive();

    std::reverse(array.begin(), array.end());

    return list.CopyToArray() == array;
}


bool testReverse_TwoPointers(std::vector<int> array) {
    DoublyLinkedList list {array};
    list.Reverse_TwoPointers();

    std::reverse(array.begin(), array.end());

    return list.CopyToArray() == array;
}


bool testReverse_Circular(std::vector<int> array) {
    DoublyCircularLinkedList list {array};
    list.Reverse();

    std::reverse(array.begin(), array.end());

    return list.CopyToArray() == array;
}

}//namespace


const std::vector<int> SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};


SIMPLE_BENCHMARK(testReverse, Sample1, SAMPLE_ARRAY);

SIMPLE_TEST(testReverse, TestSample, true, SAMPLE_ARRAY);


SIMPLE_BENCHMARK(testReverse_Recursive, Sample1, SAMPLE_ARRAY);

SIMPLE_TEST(testReverse_Recursive, TestSample, true, SAMPLE_ARRAY);


SIMPLE_BENCHMARK(testReverse_TwoPointers, Sample1, SAMPLE_ARRAY);

SIMPLE_TEST(testReverse_TwoPointers, TestSample, true, SAMPLE_ARRAY);


SIMPLE_BENCHMARK(testReverse_Circular, Sample1, SAMPLE_ARRAY);

SIMPLE_TEST(testReverse_Circular, TestSample, true, SAMPLE_ARRAY);
