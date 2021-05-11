#include "singly_linked_list.h"


namespace {

using ListType = std::forward_list<int>;
using InitializerType = std::initializer_list<ListType::value_type>;

inline auto testCountSize_Iterative(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    return list.CountSize_Iterative();
}


inline auto testCountSize_Recursive(const std::vector<int> &array) {
    SinglyLinkedList list {array};
    return list.CountSize_Recursive();
}


/** Check whether the length of given linked list is Even or Odd
 *
 * @reference   https://www.geeksforgeeks.org/check-whether-the-length-of-given-linked-list-is-even-or-odd/
 */
inline auto IsLengthEven(const ListType &l) {
    auto iter = l.cbegin();
    for (; isThereMoreThanOneElements(iter, l.cend()); std::advance(iter, 2));
    return iter == l.cend();
}


inline auto IsLengthEven_Vector(const std::vector<ListType::value_type> &array) {
    return not(array.size() % 2);
}

}//namespace


constexpr InitializerType EMPTY_ARRAY = {};
constexpr InitializerType SINGLE_ARRAY = {1};
constexpr InitializerType EVEN_ARRAY = {1, 3};
constexpr InitializerType ODD_ARRAY = {1, 2, 3};
constexpr InitializerType SAMPLE_ARRAY {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};


THE_BENCHMARK(testCountSize_Iterative, SAMPLE_ARRAY);

SIMPLE_TEST(testCountSize_Iterative, TestEmpty, EMPTY_ARRAY.size(), EMPTY_ARRAY);
SIMPLE_TEST(testCountSize_Iterative, TestSingle, SINGLE_ARRAY.size(), SINGLE_ARRAY);
SIMPLE_TEST(testCountSize_Iterative, TestEven, EVEN_ARRAY.size(), EVEN_ARRAY);
SIMPLE_TEST(testCountSize_Iterative, TestOdd, ODD_ARRAY.size(), ODD_ARRAY);
SIMPLE_TEST(testCountSize_Iterative, TestSample, SAMPLE_ARRAY.size(), SAMPLE_ARRAY);


THE_BENCHMARK(testCountSize_Recursive, SAMPLE_ARRAY);

SIMPLE_TEST(testCountSize_Recursive, TestEmpty, EMPTY_ARRAY.size(), EMPTY_ARRAY);
SIMPLE_TEST(testCountSize_Recursive, TestSingle, SINGLE_ARRAY.size(), SINGLE_ARRAY);
SIMPLE_TEST(testCountSize_Recursive, TestEven, EVEN_ARRAY.size(), EVEN_ARRAY);
SIMPLE_TEST(testCountSize_Recursive, TestOdd, ODD_ARRAY.size(), ODD_ARRAY);
SIMPLE_TEST(testCountSize_Recursive, TestSample, SAMPLE_ARRAY.size(), SAMPLE_ARRAY);


THE_BENCHMARK(IsLengthEven, SAMPLE_ARRAY);

MUTUAL_SIMPLE_TEST(IsLengthEven_Vector, IsLengthEven, TestEmpty, EMPTY_ARRAY);
MUTUAL_SIMPLE_TEST(IsLengthEven_Vector, IsLengthEven, TestSingle, SINGLE_ARRAY);
MUTUAL_SIMPLE_TEST(IsLengthEven_Vector, IsLengthEven, TestEven, EVEN_ARRAY);
MUTUAL_SIMPLE_TEST(IsLengthEven_Vector, IsLengthEven, TestOdd, ODD_ARRAY);
MUTUAL_SIMPLE_TEST(IsLengthEven_Vector, IsLengthEven, TestSample, SAMPLE_ARRAY);
