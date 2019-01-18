#include "common_header.h"

#include "singly_linked_list.h"


const std::vector<int> EMPTY_ARRAY {};
const std::vector<int> SINGLE_ARRAY {
    1
};
const std::vector<int> EVEN_ARRAY {
    1, 3
};
const std::vector<int> ODD_ARRAY {
    1, 2, 3
};
const std::vector<int> SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};
const std::vector<int> EXPECTED_ARRAY {
    -7, 111, -6, 11, -5, 44, -1, 33, 1, 8, 6, 2, 3, 7, 4, 23, 9, 10, 15, 77, 16, 777, 17
    };
const auto EXPECTED_SIZE = SAMPLE_ARRAY.size();
const std::vector<int> EXPECTED_REVERSE_ARRAY {9, 5, 4, 7, 3, 2, 6, 8, 0, 1};


auto testLinkedListInsert(const std::vector<int> &array) {
    SinglyLinkedList list {array};

    list.InsertFront(-1);

    list.PushBack(10);

    list.SearchIterative(255);  //non-exist
    list.SearchRecursive(255);  //non-exist

    const auto node = list.SearchIterative(5);

    list.InsertAfter(*node, 23);
    list.InsertFront(-2);
    list.PushBack(12);

    list.Delete(255);   //non-exist
    list.Delete(0);
    list.Delete(-2);    //head
    list.Delete(12);    //tail
    list.InsertFront(-3);
    list.PushBack(13);

    list.Delete(*node);
    list.Delete(*list.SearchRecursive(-3)); //head
    list.Delete(*list.SearchIterative(13)); //tail
    list.InsertFront(-4);
    list.PushBack(14);

    list.Delete(*list.SearchRecursive(-4)); //head
    list.Delete(*list.SearchIterative(14)); //tail
    list.InsertFront(-5);
    list.PushBack(15);

    list.InsertAtSimple(3, 33);
    list.InsertAtSimple(1, 11);   //head
    list.InsertAtSimple(list.Size() + 1, 77);   //tail
    list.InsertFront(-6);
    list.PushBack(16);

    list.InsertAtClever(4, 44);
    list.InsertAtClever(1, 111);   //head
    list.InsertAtClever(list.Size() + 1, 777);   //tail
    list.InsertFront(-7);
    list.PushBack(17);

    return list.CopyToArray();
}

SIMPLE_TEST(testLinkedListInsert, TestSample, EXPECTED_ARRAY, SAMPLE_ARRAY);
