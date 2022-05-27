#include "common_header.h"


/** Design a stack that supports getMin()
 *
 * @reference   Design and Implement Special Stack Data Structure | Added Space Optimized Version
 *              https://www.geeksforgeeks.org/design-and-implement-special-stack-data-structure/
 * @reference   Min Stack
 *              https://leetcode.com/problems/min-stack/
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 3.2.
 *
 * Design a Data Structure SpecialStack that supports all the stack operations like push(), pop(),
 * isEmpty(), isFull() and an additional operation getMin() which should return minimum element
 * from the SpecialStack. All these operations of SpecialStack must be O(1). To implement
 * SpecialStack, you should only use standard Stack data structure and no other data structure
 * like arrays, list, .. etc.
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


/**
 * @reference   Tracking current Maximum Element in a Stack
 *              https://www.geeksforgeeks.org/tracking-current-maximum-element-in-a-stack/
 * @reference   Find maximum in a stack in O(1) time and O(1) extra space
 *              https://www.geeksforgeeks.org/find-maximum-in-a-stack-in-o1-time-and-o1-extra-space/
 * @reference   Find maximum in stack in O(1) without using additional stack
 *              https://www.geeksforgeeks.org/find-maximum-in-stack-in-o1-without-using-additional-stack/
 */


/**
 * @reference   Max Stack
 *              https://aaronice.gitbook.io/lintcode/stack/max-stack
 *
 * Design a max stack that supports push, pop, top, peekMax and popMax.
 *  push(x) -- Push element x onto stack.
 *  pop() -- Remove the element on top of the stack and return it.
 *  top() -- Get the element on the top.
 *  peekMax() -- Retrieve the maximum element in the stack.
 *  popMax() -- Retrieve the maximum element in the stack, and remove it. If you find more than
 *  one maximum elements, only remove the top-most one.
 */
class MaxStack {
    using StackType = std::list<std::pair<int, int>>;
    StackType value_max_stack;
    std::unordered_map<int, std::vector<StackType::const_iterator>> hash;

public:
    auto peekMax() const {
        return value_max_stack.back().second;
    }

    void push(const int x) {
        int max = x;
        if (not value_max_stack.empty() and peekMax() > x) {
            max = peekMax();
        }

        value_max_stack.emplace_back(x, max);
        hash[x].push_back(std::prev(value_max_stack.cend()));
    }

    auto top() const {
        return value_max_stack.back().first;
    }

    auto pop() {
        const auto x = top();
        value_max_stack.pop_back();

        hash[x].pop_back();
        if (hash[x].empty()) {
            hash.erase(x);
        }

        return x;
    }

    auto popMax() {
        const auto max = peekMax();
        value_max_stack.erase(hash[max].back());
        hash[max].pop_back();
        if (hash[max].empty()) {
            hash.erase(max);
        }

        return max;
    }
};


namespace {

using ArrayType = std::vector<std::pair<MinStack::ValueType, MinStack::ValueType>>;

template<typename MinStackType>
constexpr auto testMinStack(MinStackType &stack) {
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


inline auto testMaxStack() {
    MaxStack stack;

    std::vector<int> result;

    stack.push(5);
    stack.push(1);
    stack.push(5);
    result.push_back(stack.top());
    stack.push(4);
    result.push_back(stack.popMax());
    result.push_back(stack.pop());
    result.push_back(stack.top());
    result.push_back(stack.peekMax());
    result.push_back(stack.pop());
    result.push_back(stack.top());

    return result;
}

} //namespace


const ArrayType EXPECTED1 = {{1, 9}, {1, 1}, {4, 8}, {4, 6}, {4, 4}, {5, 5}};


#ifdef WANT_TESTS
#define SimpleMinStackTest(TypeName)               \
    namespace {                                    \
    TEST(MinStackTest, test##TypeName) {           \
        TypeName stack;                            \
        EXPECT_EQ(EXPECTED1, testMinStack(stack)); \
    }                                              \
    }


SimpleMinStackTest(MinStack);


SimpleMinStackTest(MinStack_SpaceOptimized);


SimpleMinStackTest(MinStack_O1Space);
#endif


const std::vector EXPECTED1Max = {5, 5, 4, 1, 5, 1, 5};


SIMPLE_TEST0(testMaxStack, TestSample1, EXPECTED1Max);
