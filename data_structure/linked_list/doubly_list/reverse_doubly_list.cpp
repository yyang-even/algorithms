#include "doubly_linked_list.h"


namespace {

bool testReverse(std::vector<int> array) {
    DoublyLinkedList list {array};
    list.Reverse();

    std::reverse(array.begin(), array.end());

    std::cout << list.CopyToArray() << std::endl;
    std::cout << array << std::endl;
    return list.CopyToArray() == array;
}

}//namespace


const std::vector<int> SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};


SIMPLE_BENCHMARK(testReverse, SAMPLE_ARRAY);

SIMPLE_TEST(testReverse, TestSample, true, SAMPLE_ARRAY);
