#include "array_linked_list.h"


namespace {

auto testLinkedList_Helper(const std::vector<int> &array) {
    ArrayLinkedList list {array};

    list.PushFront(-1);
    list.PushFront(-2);

    list.PushBack(10);
    list.PushBack(11);

    list.PushBack(12);
    list.PushFront(-3);

    list.Search(255);  //non-exist
    list.Search(255);  //non-exist

    list.InsertAfter(list.Search(5), 23);
    list.PushFront(-4);
    list.PushBack(13);
    list.InsertAfter(list.Search(-4), 24);   //head
    list.InsertAfter(list.Search(13), 25);   //tail

    list.Delete(-4);  //head
    list.Delete(25);  //tail
    list.Delete(0);
    list.Delete(3);
    list.Delete(2);
    list.PushFront(26);
    list.PushBack(-26);

    return list;
}


inline auto testLinkedList(const std::vector<int> &array) {
    const auto list = testLinkedList_Helper(array);

    return list.CopyToArray();
}

}//namespace


const std::vector<int> SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};
const std::vector<int> EXPECTED_ARRAY = {26, 24, -3, -2, -1, 1, 8, 6, 7, 4, 5, 23, 9, 10, 11, 12, 13, -26};


THE_BENCHMARK(testLinkedList, SAMPLE_ARRAY);

SIMPLE_TEST(testLinkedList, TestSample, EXPECTED_ARRAY, SAMPLE_ARRAY);
