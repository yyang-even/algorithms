#include "singly_linked_list.h"


namespace {

const std::vector<int> EMPTY_ARRAY {};
const std::vector<int> SINGLE_ARRAY = {1};
const std::vector<int> EVEN_ARRAY = {1, 3};
const std::vector<int> ODD_ARRAY = {1, 2, 3};
const std::vector<int> SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};


auto testCountSize_Iterative(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    return list.CountSize_Iterative();
}


auto testCountSize_Recursive(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    return list.CountSize_Recursive();
}


/** Check whether the length of given linked list is Even or Odd
 *
 * @reference   https://www.geeksforgeeks.org/check-whether-the-length-of-given-linked-list-is-even-or-odd/
 */
auto IsLengthEven(const std::forward_list<int> &l) {
    auto iter = l.cbegin();
    for (; iter != l.cend() and std::next(iter) != l.cend(); std::advance(iter, 2));
    return iter == l.cend();
}
auto testIsLengthEven(const std::vector<int> &array) {
    return IsLengthEven({array.cbegin(), array.cend()});
}

}//namespace


SIMPLE_BENCHMARK(testCountSize_Iterative, SAMPLE_ARRAY);

SIMPLE_TEST(testCountSize_Iterative, TestEmpty, EMPTY_ARRAY.size(), EMPTY_ARRAY);
SIMPLE_TEST(testCountSize_Iterative, TestSingle, SINGLE_ARRAY.size(), SINGLE_ARRAY);
SIMPLE_TEST(testCountSize_Iterative, TestEven, EVEN_ARRAY.size(), EVEN_ARRAY);
SIMPLE_TEST(testCountSize_Iterative, TestOdd, ODD_ARRAY.size(), ODD_ARRAY);
SIMPLE_TEST(testCountSize_Iterative, TestSample, SAMPLE_ARRAY.size(), SAMPLE_ARRAY);


SIMPLE_BENCHMARK(testCountSize_Recursive, SAMPLE_ARRAY);

SIMPLE_TEST(testCountSize_Recursive, TestEmpty, EMPTY_ARRAY.size(), EMPTY_ARRAY);
SIMPLE_TEST(testCountSize_Recursive, TestSingle, SINGLE_ARRAY.size(), SINGLE_ARRAY);
SIMPLE_TEST(testCountSize_Recursive, TestEven, EVEN_ARRAY.size(), EVEN_ARRAY);
SIMPLE_TEST(testCountSize_Recursive, TestOdd, ODD_ARRAY.size(), ODD_ARRAY);
SIMPLE_TEST(testCountSize_Recursive, TestSample, SAMPLE_ARRAY.size(), SAMPLE_ARRAY);


SIMPLE_BENCHMARK(testIsLengthEven, SAMPLE_ARRAY);

SIMPLE_TEST(testIsLengthEven, TestEmpty, not(EMPTY_ARRAY.size() % 2), EMPTY_ARRAY);
SIMPLE_TEST(testIsLengthEven, TestSingle, not(SINGLE_ARRAY.size() % 2), SINGLE_ARRAY);
SIMPLE_TEST(testIsLengthEven, TestEven, not(EVEN_ARRAY.size() % 2), EVEN_ARRAY);
SIMPLE_TEST(testIsLengthEven, TestOdd, not(ODD_ARRAY.size() % 2), ODD_ARRAY);
SIMPLE_TEST(testIsLengthEven, TestSample, not(SAMPLE_ARRAY.size() % 2), SAMPLE_ARRAY);
