#include "singly_list/singly_linked_list.h"
#include "singly_list/singly_circular_linked_list.h"
#include "doubly_list/doubly_linked_list.h"

#include "sorted_insert_linked_list.h"


namespace {

auto testSortedInsert_Singly(std::vector<int> array) {
    std::sort(array.begin(), array.end());
    SinglyLinkedList list {array};

    list.SortedInsert(-1);  //head
    list.SortedInsert(15);  //tail
    list.SortedInsert(11);
    list.InsertFront(-8);
    list.PushBack(18);

    return list.CopyToArray();
}


auto testSortedInsert_Doubly(std::vector<int> array) {
    std::sort(array.begin(), array.end());
    DoublyLinkedList list {array};

    list.SortedInsert(-1);  //head
    list.SortedInsert(15);  //tail
    list.SortedInsert(11);
    list.PushFront(-8);
    list.PushBack(18);

    return list.CopyToArray();
}


auto testSortedInsert_SinglyCircular(std::vector<int> array) {
    std::sort(array.begin(), array.end());
    SinglyCircularLinkedList list {array};

    list.SortedInsert(-1);  //head
    list.SortedInsert(15);  //tail
    list.SortedInsert(11);
    list.PushFront(-8);
    list.PushBack(18);

    return list.CopyToArray();
}


auto testSortedInsert_SinglyCircular_Convert(std::vector<int> array) {
    std::sort(array.begin(), array.end());
    SinglyCircularLinkedList list {array};

    list.SortedInsert_Convert(-1);  //head
    list.SortedInsert_Convert(15);  //tail
    list.SortedInsert_Convert(11);
    list.PushFront(-8);
    list.PushBack(18);

    return list.CopyToArray();
}

}//namespace


const std::vector<int> SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};
const std::vector<int> EXPECTED_SORTED_INSERT_ARRAY = { -8, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 15, 18};


THE_BENCHMARK(testSortedInsert_Singly, SAMPLE_ARRAY);

SIMPLE_TEST(testSortedInsert_Singly, TestSample, EXPECTED_SORTED_INSERT_ARRAY,
            SAMPLE_ARRAY);


const std::forward_list<int> EMPTY_LIST = {};
const std::forward_list<int> SINGLE_ITEM_LIST = {5};
const std::forward_list<int> EXPECTED2 = {2, 5};
const std::forward_list<int> EXPECTED3 = {5, 8};
const std::forward_list<int> SAMPLE_LIST = {EXPECTED_SORTED_INSERT_ARRAY.cbegin(), EXPECTED_SORTED_INSERT_ARRAY.cend()};
const std::forward_list<int> EXPECTED4 = { -8, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 15, 18};


THE_BENCHMARK(SortedInsert_STL, SAMPLE_LIST, 10);

SIMPLE_TEST(SortedInsert_STL, TestSample1, SINGLE_ITEM_LIST,
            EMPTY_LIST, SINGLE_ITEM_LIST.front());
SIMPLE_TEST(SortedInsert_STL, TestSample2, EXPECTED2,
            SINGLE_ITEM_LIST, EXPECTED2.front());
SIMPLE_TEST(SortedInsert_STL, TestSample3, EXPECTED3, SINGLE_ITEM_LIST, 8);
SIMPLE_TEST(SortedInsert_STL, TestSample4, EXPECTED4, SAMPLE_LIST, 10);


THE_BENCHMARK(testSortedInsert_Doubly, SAMPLE_ARRAY);

SIMPLE_TEST(testSortedInsert_Doubly, TestSample, EXPECTED_SORTED_INSERT_ARRAY,
            SAMPLE_ARRAY);


THE_BENCHMARK(testSortedInsert_SinglyCircular, SAMPLE_ARRAY);

SIMPLE_TEST(testSortedInsert_SinglyCircular, TestSample, EXPECTED_SORTED_INSERT_ARRAY,
            SAMPLE_ARRAY);


THE_BENCHMARK(testSortedInsert_SinglyCircular_Convert, SAMPLE_ARRAY);

SIMPLE_TEST(testSortedInsert_SinglyCircular_Convert, TestSample,
            EXPECTED_SORTED_INSERT_ARRAY, SAMPLE_ARRAY);
