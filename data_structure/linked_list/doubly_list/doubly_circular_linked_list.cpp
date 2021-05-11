#include "doubly_circular_linked_list.h"


namespace {

auto testLinkedList_Helper(const std::vector<int> &array) {
    DoublyCircularLinkedList list {array};

    list.PushFront(-1);
    list.PushFront(-2);

    list.PushBack(10);
    list.PushBack(11);

    list.PushBack(12);
    list.PushFront(-3);

    list.Search(255);  //non-exist
    list.Search(255);  //non-exist

    list.InsertBefore(list.Search(5), -23);
    list.InsertAfter(list.Search(5), 23);
    list.PushFront(-4);
    list.PushBack(13);
    list.InsertBefore(list.Search(-4), -24);  //head
    list.InsertBefore(list.Search(13), -25);  //tail
    list.InsertAfter(list.Search(-24), 24);   //head
    list.InsertAfter(list.Search(13), 25);    //tail

    list.Delete(list.Search(-24));  //head
    list.Delete(list.Search(25));   //tail
    list.Delete(list.Search(0));
    list.Delete(list.Search(3));
    list.Delete(list.Search(2));
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


inline auto testLinkedList_ReverseOrder(const std::vector<int> &array) {
    const auto list = testLinkedList_Helper(array);

    auto output = list.CopyToArray_Reverse();
    std::reverse(output.begin(), output.end());
    return output;
}


inline auto testLinkedList_Size(const std::vector<int> &array) {
    const auto list = testLinkedList_Helper(array);

    return list.Size() ==  DoublyCircularLinkedList::Node::node_alive;
}

}//namespace


const std::vector<int> SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};
const std::vector<int> EXPECTED_ARRAY = {27, 24, -4, -3, -2, 1, 8, 6, 7, 4, -23, 5, 23, 9, 10, 11, 12, -25, 13, -27};


THE_BENCHMARK(testLinkedList, SAMPLE_ARRAY);

SIMPLE_TEST(testLinkedList, TestSample, EXPECTED_ARRAY, SAMPLE_ARRAY);


THE_BENCHMARK(testLinkedList_ReverseOrder, SAMPLE_ARRAY);

SIMPLE_TEST(testLinkedList_ReverseOrder, TestSample, EXPECTED_ARRAY, SAMPLE_ARRAY);


THE_BENCHMARK(testLinkedList_Size, SAMPLE_ARRAY);

SIMPLE_TEST(testLinkedList_Size, TestSample, true, SAMPLE_ARRAY);
