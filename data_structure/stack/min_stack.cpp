#include "common_header.h"


/** Design a stack that supports getMin()
 *
 * @reference   Design and Implement Special Stack Data Structure | Added Space Optimized Version
 *              https://www.geeksforgeeks.org/design-and-implement-special-stack-data-structure/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 3.2.
 *
 * Design a Data Structure SpecialStack that supports all the stack operations like
 * push(), pop(), isEmpty(), isFull() and an additional operation getMin() which
 * should return minimum element from the SpecialStack. All these operations of
 * SpecialStack must be O(1). To implement SpecialStack, you should only use standard
 * Stack data structure and no other data structure like arrays, list, .. etc.
 */
class MinStack {
public:
    using ValueType = int;

private:
    std::stack<ValueType> value_stack;
    std::stack<ValueType> min_stack;

public:
    auto isEmpty() const {
        assert(value_stack.size() == min_stack.size());

        return value_stack.empty();
    }

    auto Min() const {
        assert(not isEmpty());

        return min_stack.top();
    }

    void Push(const ValueType v) {
        auto min = v;
        if (not isEmpty() and Min() < v) {
            min = Min();
        }

        value_stack.push(v);
        min_stack.push(min);
    }

    auto Pop() {
        assert(not isEmpty());

        const auto result = value_stack.top();
        value_stack.pop();
        min_stack.pop();

        return result;
    }
};


class MinStack_SpaceOptimized {
public:
    using ValueType = int;

private:
    std::stack<ValueType> value_stack;
    std::stack<ValueType> min_stack;

public:
    auto isEmpty() const {
        return value_stack.empty();
    }

    auto Min() const {
        assert(not isEmpty());

        return min_stack.top();
    }

    void Push(const ValueType v) {
        if (isEmpty() or v <= Min()) {
            min_stack.push(v);
        }
        value_stack.push(v);
    }

    auto Pop() {
        assert(not isEmpty());

        const auto result = value_stack.top();
        if (result == Min()) {
            min_stack.pop();
        }
        value_stack.pop();

        return result;
    }
};


/**
 * @reference   Design a stack that supports getMin() in O(1) time and O(1) extra space
 *              https://www.geeksforgeeks.org/design-a-stack-that-supports-getmin-in-o1-time-and-o1-extra-space/
 * @reference   Design a stack to retrieve original elements and return the minimum element in O(1) time and O(1) space
 *              https://www.geeksforgeeks.org/design-a-stack-to-retrieve-original-elements-and-return-the-minimum-element-in-o1-time-and-o1-space/
 */
class MinStack_O1Space {
public:
    using ValueType = int;

private:
    std::stack<ValueType> value_stack;
    ValueType min = 0;

public:
    auto isEmpty() const {
        return value_stack.empty();
    }

    auto Min() const {
        assert(not isEmpty());

        return min;
    }

    void Push(const ValueType v) {
        if (isEmpty()) {
            min = v;
            value_stack.push(v);
        } else {
            if (v < min) {
                value_stack.push(2 * v - min);
                min = v;
            } else {
                value_stack.push(v);
            }
        }
    }

    auto Pop() {
        assert(not isEmpty());

        const auto top = value_stack.top();
        value_stack.pop();
        auto result = top;
        if (top < min) {
            result = min;
            min = 2 * min - top;
        }

        return result;
    }
};

namespace {

using ArrayType = std::vector<std::pair<MinStack::ValueType, MinStack::ValueType>>;

template <typename MinStackType>
auto testMinStack(MinStackType &stack) {
    stack.Push(5);
    stack.Push(4);
    stack.Push(6);
    stack.Push(7);
    stack.Push(3);
    stack.Pop();
    stack.Pop();
    stack.Push(8);
    stack.Push(2);
    stack.Pop();
    stack.Push(1);
    stack.Push(9);

    ArrayType results;
    while (not stack.isEmpty()) {
        const auto min = stack.Min();
        results.emplace_back(min, stack.Pop());
    }

    return results;
}

}//namespace


const ArrayType EXPECTED1 = {{1, 9}, {1, 1}, {4, 8}, {4, 6}, {4, 4}, {5, 5}};


#ifdef WANT_TESTS
#define SimpleMinStackTest(TypeName) namespace {    \
    TEST(MinStackTest, test##TypeName) {            \
        TypeName stack;                             \
        EXPECT_EQ(EXPECTED1, testMinStack(stack));  \
    }                                               \
}
#endif


SimpleMinStackTest(MinStack);


SimpleMinStackTest(MinStack_SpaceOptimized);


SimpleMinStackTest(MinStack_O1Space);
