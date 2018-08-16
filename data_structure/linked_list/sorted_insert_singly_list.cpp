#include "3rdParty/prettyprint.hpp"

#include "singly_linked_list.h"


const std::vector<int> SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};

auto testSortedInsert(std::vector<int> array) {
    std::sort(array.begin(), array.end());
    SinglyLinkedList list {array};

    list.SortedInsert(-1);
    list.SortedInsert(15);
    list.SortedInsert(11);
    list.InsertFront(-8);
    list.PushBack(18);

    return list.CopyToArray();
}

const std::vector<int> EXPECTED_SORTED_INSERT_ARRAY { -8, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 15, 18};

SIMPLE_TEST(testSortedInsert, TestSample, EXPECTED_SORTED_INSERT_ARRAY, SAMPLE_ARRAY);
