#include "common_header.h"

#include "singly_linked_list.h"


namespace {

inline auto testDeleteAll() {
    const std::vector<int> SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};
    SinglyLinkedList list {SAMPLE_ARRAY};
    list.DeleteAllOneByOne();
    return SinglyLinkedList::Node::node_alive;
}

inline auto testDeleteAll_Recursive() {
    const std::vector<int> SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};
    SinglyLinkedList list {SAMPLE_ARRAY};
    list.DeleteAllOneByOne_Recursive();
    return SinglyLinkedList::Node::node_alive;
}

}//namespace


SIMPLE_BENCHMARK0(testDeleteAll);

SIMPLE_TEST(testDeleteAll, TestSample, 0);


SIMPLE_BENCHMARK0(testDeleteAll_Recursive);

SIMPLE_TEST(testDeleteAll_Recursive, TestSample, 0);
