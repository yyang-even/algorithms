#include "singly_linked_list.h"
#include "middle_of_singly_linked_list.h"


namespace {

/** Find middle of singly linked list Recursively
 *
 * @reference   https://www.geeksforgeeks.org/find-middle-singly-linked-list-recursively/
 */
std::forward_list<int>::const_iterator GetMiddleRecursive(const
        std::forward_list<int>::const_iterator cbegin,
        const std::forward_list<int>::const_iterator cend,
        std::forward_list<int>::size_type &n) {
    if (cbegin == cend) {
        n /= 2;
    } else {
        const auto mid = GetMiddleRecursive(std::next(cbegin), cend, ++n);
        if (--n) {
            return mid;
        }
    }
    return cbegin;
}
auto GetMiddleRecursive(const std::forward_list<int> &l) {
    assert(not l.empty());
    std::forward_list<int>::size_type n = 0;
    return *GetMiddleRecursive(l.cbegin(), l.end(), n);
}

const std::vector<int> SINGLE_ARRAY = { 1 };
const std::vector<int> EVEN_ARRAY = { 1, 3 };
const std::vector<int> ODD_ARRAY = { 1, 2, 3 };
const std::vector<int> SAMPLE_ARRAY = {1, 0, 8, 6, 2, 3, 7, 4, 5, 9};


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

auto testGetBeforeMiddleTwoPointersSTL(const std::vector<int> &array) {
    std::forward_list<int> l{array.cbegin(), array.cend()};
    auto before_mid = GetBeforeMiddleTwoPointersSTL(l.cbefore_begin(), l.cbegin(), l.cend());
    return *(++before_mid);
}

auto testGetMiddleRecursive(const std::vector<int> &array) {
    std::forward_list<int> l{array.cbegin(), array.cend()};
    return GetMiddleRecursive(l);
}

}//namespace

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
