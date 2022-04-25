#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Peeking Iterator
 *
 * @reference   https://leetcode.com/problems/peeking-iterator/
 *
 * Design an iterator that supports the peek operation on an existing iterator in addition
 * to the hasNext and the next operations.
 * Implement the PeekingIterator class:
 *  PeekingIterator(Iterator<int> nums) Initializes the object with the given integer
 *      iterator iterator.
 *  int next() Returns the next element in the array and moves the pointer to the next
 *      element.
 *  boolean hasNext() Returns true if there are still elements in the array.
 *  int peek() Returns the next element in the array without moving the pointer.
 * Note: Each language may have a different implementation of the constructor and Iterator,
 * but they all support the int next() and boolean hasNext() functions.
 * Follow up: How would you extend your design to be generic and work with all types, not
 * just integer?
 */
class Iterator {
    const ArrayType *data = nullptr;
    std::size_t index = 0;
public:
    Iterator(const ArrayType &nums) noexcept: data(&nums) {
    }

    int next() noexcept {
        return (*data)[index++];
    }

    auto hasNext() const noexcept {
        return index != data->size();
    }
};

class PeekingIterator : public Iterator {
public:
    using Iterator::Iterator;

    int peek() const noexcept {
        return Iterator(*this).next();
    }
};

inline auto testIterator(const ArrayType &nums) {
    Iterator iter(nums);

    ArrayType result;
    while (iter.hasNext()) {
        result.push_back(iter.next());
    }

    return result;
}

inline auto testPeekingIterator(const ArrayType &nums) {
    PeekingIterator iter(nums);

    ArrayType result;
    ArrayType peek_result;
    while (iter.hasNext()) {
        peek_result.push_back(iter.peek());
        result.push_back(iter.next());
    }

    return result == peek_result;
}

}//namespace


const ArrayType SAMPLE1 = {1, 2, 3};


SIMPLE_TEST(testIterator, TestSAMPLE1, SAMPLE1, SAMPLE1);


SIMPLE_TEST(testPeekingIterator, TestSAMPLE1, true, SAMPLE1);
