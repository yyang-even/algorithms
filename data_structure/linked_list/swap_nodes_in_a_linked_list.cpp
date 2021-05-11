#include "common_header.h"

#include "singly_list/singly_linked_list.h"


namespace {

const std::vector<int> SAMPLE_ARRAY {10, 15, 12, 13, 20, 14};


inline auto testSwapNodes(const int x, const int y) {
    SinglyLinkedList list{SAMPLE_ARRAY};
    list.Swap(x, y);

    list.InsertFront(-1);
    list.PushBack(100);

    return list.CopyToArray();
}


inline auto testSwapNodes_Clever(const int x, const int y) {
    SinglyLinkedList list{SAMPLE_ARRAY};
    list.Swap_Clever(x, y);

    list.InsertFront(-1);
    list.PushBack(100);

    return list.CopyToArray();
}

}//namespace


const std::vector<int> EXPECTED_ARRAY1 = {-1, 10, 15, 20, 13, 12, 14, 100};
const std::vector<int> EXPECTED_ARRAY2 = {-1, 20, 15, 12, 13, 10, 14, 100};  //head
const std::vector<int> EXPECTED_ARRAY3 = {-1, 10, 15, 13, 12, 20, 14, 100};  //adjacent
const std::vector<int> EXPECTED_ARRAY4 = {-1, 10, 14, 12, 13, 20, 15, 100};  //tail


THE_BENCHMARK(testSwapNodes, 12, 20);

SIMPLE_TEST(testSwapNodes, TestSample1, EXPECTED_ARRAY1, 12, 20);
SIMPLE_TEST(testSwapNodes, TestSample2, EXPECTED_ARRAY2, 10, 20);
SIMPLE_TEST(testSwapNodes, TestSample3, EXPECTED_ARRAY3, 12, 13);
SIMPLE_TEST(testSwapNodes, TestSample4, EXPECTED_ARRAY4, 15, 14);


THE_BENCHMARK(testSwapNodes_Clever, 12, 20);

SIMPLE_TEST(testSwapNodes_Clever, TestSample1, EXPECTED_ARRAY1, 12, 20);
SIMPLE_TEST(testSwapNodes_Clever, TestSample2, EXPECTED_ARRAY2, 10, 20);
SIMPLE_TEST(testSwapNodes_Clever, TestSample3, EXPECTED_ARRAY3, 12, 13);
SIMPLE_TEST(testSwapNodes_Clever, TestSample4, EXPECTED_ARRAY4, 15, 14);
