#include "common_header.h"

#include "singly_linked_list.h"


namespace {

auto testDeleteAll() {
    const std::vector<int> SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};
    SinglyLinkedList list {SAMPLE_ARRAY};
    list.DeleteAllOneByOne();
    return SinglyLinkedList::Node::node_alive;
}

auto testDeleteAll_Recursive() {
    const std::vector<int> SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};
    SinglyLinkedList list {SAMPLE_ARRAY};
    list.DeleteAllOneByOne_Recursive();
    return SinglyLinkedList::Node::node_alive;
}

}//namespace


SIMPLE_BENCHMARK(testDeleteAll);

SIMPLE_TEST(testDeleteAll, TestSample, 0u);


SIMPLE_BENCHMARK(testDeleteAll_Recursive);

SIMPLE_TEST(testDeleteAll_Recursive, TestSample, 0u);
