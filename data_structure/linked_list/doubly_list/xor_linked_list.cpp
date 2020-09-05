#include "xor_linked_list.h"


namespace {

const std::vector<int> SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};
const std::vector<int> EXPECTED_ARRAY = {27, -4, 24, -3, -2, -1, 1, 0, 8, 6, 2, 3, 7, 4, 5, 23, 9, 10, 11, 12, 13, 25, -27};


auto testLinkedList_Helper(const std::vector<int> &array) {
    XorLinkedList list {array};

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

    list.PushFront(27);
    list.PushBack(-27);

    return list;
}


auto testLinkedList(const std::vector<int> &array) {
    const auto list = testLinkedList_Helper(array);

    return list.CopyToArray();
}


auto testLinkedList_ReverseOrder(const std::vector<int> &array) {
    const auto list = testLinkedList_Helper(array);

    auto output = list.CopyToArray_Reverse();
    std::reverse(output.begin(), output.end());
    return output;
}


auto testLinkedList_Size(const std::vector<int> &array) {
    const auto list = testLinkedList_Helper(array);

    return list.Size() ==  XorLinkedList::Node::node_alive;
}

}//namespace


SIMPLE_BENCHMARK(testLinkedList, Sample1, SAMPLE_ARRAY);

SIMPLE_TEST(testLinkedList, TestSample, EXPECTED_ARRAY, SAMPLE_ARRAY);


SIMPLE_BENCHMARK(testLinkedList_ReverseOrder, Sample1, SAMPLE_ARRAY);

SIMPLE_TEST(testLinkedList_ReverseOrder, TestSample, EXPECTED_ARRAY, SAMPLE_ARRAY);


SIMPLE_BENCHMARK(testLinkedList_Size, Sample1, SAMPLE_ARRAY);

SIMPLE_TEST(testLinkedList_Size, TestSample, true, SAMPLE_ARRAY);
