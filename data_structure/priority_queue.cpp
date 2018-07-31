#include "common_header.h"

#include "3rdParty/prettyprint.hpp"

#include "priority_queue.h"


auto testPriorityQueue(const MinPriorityQueue::ArrayType &array) {
    MinPriorityQueue priority_queue{array};

    //No-op
    priority_queue.Prioritize(2, 8);

    priority_queue.Prioritize(9, -1);

    return priority_queue.ToSortedArray();
}


const MinPriorityQueue::ArrayType SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};
const MinPriorityQueue::ArrayType EXPECTED_ARRAY {
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8
};

SIMPLE_TEST(testPriorityQueue, TestSample, EXPECTED_ARRAY, SAMPLE_ARRAY);
