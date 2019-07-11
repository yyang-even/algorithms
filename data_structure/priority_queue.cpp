#include "common_header.h"

#include "priority_queue.h"


namespace {

auto testPriorityQueue(const MinPriorityQueue<int>::ArrayType &array) {
    MinPriorityQueue<int> priority_queue{array};

    //No-op
    priority_queue.Prioritize(2, 8);

    priority_queue.Prioritize(9, -1);

    return priority_queue.ToSortedArray();
}


auto testListPriorityQueue(const MinPriorityQueue<int>::ArrayType &array) {
    SinglyLinkedListMinPriorityQueue priority_queue{array};
    priority_queue.Pop();

    return priority_queue.MoveToSortedArray();
}


auto testListPriorityQueueSTL(const MinPriorityQueue<int>::ArrayType &array) {
    SinglyLinkedListMinPriorityQueueSTL priority_queue{array};
    priority_queue.Pop();

    return priority_queue.MoveToSortedArray();
}

}//namespace


const MinPriorityQueue<int>::ArrayType SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};
const MinPriorityQueue<int>::ArrayType EXPECTED_ARRAY {
    8, 7, 6, 5, 4, 3, 2, 1, 0, -1
};


SIMPLE_TEST(testPriorityQueue, TestSample, EXPECTED_ARRAY, SAMPLE_ARRAY);


const std::vector<int> EXPECTED_LIST_ARRAY {1, 2, 3, 4, 5, 6, 7, 8, 9};


SIMPLE_TEST(testListPriorityQueue, TestSample, EXPECTED_LIST_ARRAY, SAMPLE_ARRAY);
SIMPLE_TEST(testListPriorityQueueSTL, TestSample, EXPECTED_LIST_ARRAY, SAMPLE_ARRAY);
