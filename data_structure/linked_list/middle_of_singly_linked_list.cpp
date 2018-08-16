#include "3rdParty/prettyprint.hpp"

#include "singly_linked_list.h"


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


auto testGetMidSize(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    return list.GetMidSize();
}

auto testGetMidTwoPointers(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    return list.GetMidTwoPointers();
}

auto testGetMidOdd(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    return list.GetMidOdd();
}

SIMPLE_TEST(testGetMidSize, TestSingle, SINGLE_ARRAY[SINGLE_ARRAY.size() / 2], SINGLE_ARRAY);
SIMPLE_TEST(testGetMidSize, TestEven, EVEN_ARRAY[EVEN_ARRAY.size() / 2], EVEN_ARRAY);
SIMPLE_TEST(testGetMidSize, TestOdd, ODD_ARRAY[ODD_ARRAY.size() / 2], ODD_ARRAY);
SIMPLE_TEST(testGetMidSize, TestSample, SAMPLE_ARRAY[SAMPLE_ARRAY.size() / 2], SAMPLE_ARRAY);

SIMPLE_TEST(testGetMidTwoPointers, TestSingle, SINGLE_ARRAY[SINGLE_ARRAY.size() / 2], SINGLE_ARRAY);
SIMPLE_TEST(testGetMidTwoPointers, TestEven, EVEN_ARRAY[EVEN_ARRAY.size() / 2], EVEN_ARRAY);
SIMPLE_TEST(testGetMidTwoPointers, TestOdd, ODD_ARRAY[ODD_ARRAY.size() / 2], ODD_ARRAY);
SIMPLE_TEST(testGetMidTwoPointers, TestSample, SAMPLE_ARRAY[SAMPLE_ARRAY.size() / 2], SAMPLE_ARRAY);

SIMPLE_TEST(testGetMidOdd, TestSingle, SINGLE_ARRAY[SINGLE_ARRAY.size() / 2], SINGLE_ARRAY);
SIMPLE_TEST(testGetMidOdd, TestEven, EVEN_ARRAY[EVEN_ARRAY.size() / 2], EVEN_ARRAY);
SIMPLE_TEST(testGetMidOdd, TestOdd, ODD_ARRAY[ODD_ARRAY.size() / 2], ODD_ARRAY);
SIMPLE_TEST(testGetMidOdd, TestSample, SAMPLE_ARRAY[SAMPLE_ARRAY.size() / 2], SAMPLE_ARRAY);
