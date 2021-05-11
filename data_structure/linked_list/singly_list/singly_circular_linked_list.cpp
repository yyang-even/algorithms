#include "singly_circular_linked_list.h"


namespace {

auto testLinkedList_Helper(const std::vector<int> &array) {
    SinglyCircularLinkedList list {array};

    list.PushFront(-1);
    list.PushFront(-2);

    list.PushBack(10);
    list.PushBack(11);

    list.PushBack(12);
    list.PushFront(-3);

    list.SearchPrev(255);  //non-exist
    list.SearchPrev(255);  //non-exist

    list.InsertAfter(list.SearchPrev(5), 23);
    list.PushFront(-4);
    list.PushBack(13);
    list.InsertAfter(list.SearchPrev(-3), 24);   //head
    list.InsertAfter(list.SearchPrev(-4), 25);   //tail

    list.Delete(-4);  //head
    list.Delete(25);  //tail
    list.Delete(0);
    list.Delete(3);
    list.Delete(2);
    list.PushFront(26);
    list.PushBack(-26);

    list.DeleteAt(0);  //head
    list.DeleteAt(list.Size() - 1);   //tail
    list.DeleteAt(4);
    list.PushFront(27);
    list.PushBack(-27);

    return list;
}


inline auto testLinkedList(const std::vector<int> &array) {
    const auto list = testLinkedList_Helper(array);

    return list.CopyToArray();
}


inline auto testLinkedList_Size(const std::vector<int> &array) {
    const auto list = testLinkedList_Helper(array);

    return list.Size() ==  SinglyCircularLinkedList::Node::node_alive;
}


inline auto testLinkedList_CountSize(const std::vector<int> &array) {
    const auto list = testLinkedList_Helper(array);

    return list.Size() ==  list.CountSize();
}


inline auto testLinkedList_isCircular(const std::vector<int> &array) {
    const auto list = testLinkedList_Helper(array);

    return list.isCircular();
}

}//namespace


const std::vector<int> SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};
const std::vector<int> EXPECTED_ARRAY = {27, 24, -3, -2, -1, 8, 6, 7, 4, 23, 5, 9, 10, 11, 12, 13, -27};


THE_BENCHMARK(testLinkedList, SAMPLE_ARRAY);

SIMPLE_TEST(testLinkedList, TestSample, EXPECTED_ARRAY, SAMPLE_ARRAY);


THE_BENCHMARK(testLinkedList_Size, SAMPLE_ARRAY);

SIMPLE_TEST(testLinkedList_Size, TestSample, true, SAMPLE_ARRAY);


THE_BENCHMARK(testLinkedList_CountSize, SAMPLE_ARRAY);

SIMPLE_TEST(testLinkedList_CountSize, TestSample, true, SAMPLE_ARRAY);


THE_BENCHMARK(testLinkedList_isCircular, SAMPLE_ARRAY);

SIMPLE_TEST(testLinkedList_isCircular, TestSample, true, SAMPLE_ARRAY);
