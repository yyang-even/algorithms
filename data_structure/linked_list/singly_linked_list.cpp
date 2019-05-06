#include "common_header.h"

#include "singly_linked_list.h"


namespace {

const std::vector<int> EMPTY_ARRAY {};
const std::vector<int> SINGLE_ARRAY = {1};
const std::vector<int> EVEN_ARRAY = {1, 3};
const std::vector<int> ODD_ARRAY = {1, 2, 3};
const std::vector<int> SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};
const std::vector<int> EXPECTED_ARRAY = {-9, 111, -6, 11, -5, 44, -1, 33, 1, 8, 6,
                                         2, 3, 7, 4, 23, 9, 10, 16, 777, 17, 19
                                        };
const auto EXPECTED_SIZE = SAMPLE_ARRAY.size();
const std::vector<int> EXPECTED_REVERSE_ARRAY {9, 5, 4, 7, 3, 2, 6, 8, 0, 1};


auto testLinkedListInsert(const std::vector<int> &array) {
    SinglyLinkedList list {array};

    list.InsertFront(-1);

    list.PushBack(10);

    list.Search_Iterative(255);  //non-exist
    list.Search_Recursive(255);  //non-exist

    const auto node = list.Search_Iterative(5);

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
    list.Delete(*list.Search_Recursive(-3)); //head
    list.Delete(*list.Search_Iterative(13)); //tail
    list.InsertFront(-4);
    list.PushBack(14);

    list.Delete(*list.Search_Recursive(-4)); //head
    list.Delete(*list.Search_Iterative(14)); //tail
    list.InsertFront(-5);
    list.PushBack(15);

    list.InsertAt_Simple(3, 33);
    list.InsertAt_Simple(1, 11);   //head
    list.InsertAt_Simple(list.Size() + 1, 77);   //tail
    list.InsertFront(-6);
    list.PushBack(16);

    list.InsertAt_Clever(4, 44);
    list.InsertAt_Clever(1, 111);   //head
    list.InsertAt_Clever(list.Size() + 1, 777);   //tail
    list.InsertFront(-7);
    list.PushBack(17);

    list.DeleteNode_Constrained(*list.Search_Recursive(-7)); //head
    list.DeleteNode_Constrained(*list.Search_Iterative(77));
    list.InsertFront(-8);
    list.PushBack(18);

    list.DeleteLastOfKey(-8); //head
    list.DeleteLastOfKey(18); //tail
    list.DeleteLastOfKey(15);
    list.InsertFront(-9);
    list.PushBack(19);

    return list.CopyToArray();
}

}//namespace


SIMPLE_BENCHMARK(testLinkedListInsert, SAMPLE_ARRAY);

SIMPLE_TEST(testLinkedListInsert, TestSample, EXPECTED_ARRAY, SAMPLE_ARRAY);
