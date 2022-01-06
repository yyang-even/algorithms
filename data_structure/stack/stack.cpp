#include "common_header.h"


/** Implementing Stack using Arrays
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 10.1.
 * @reference   Stack Data Structure (Introduction and Program)
 *              https://www.geeksforgeeks.org/stack-data-structure-introduction-program/
 * @reference   Difference between Stack and Queue Data Structures
 *              https://www.geeksforgeeks.org/difference-between-stack-and-queue-data-structures/
 * @reference   LIFO (Last-In-First-Out) approach in Programming
 *              https://www.geeksforgeeks.org/lifo-last-in-first-out-approach-in-programming/
 */
class ArrayStack {
    using ValueType = int;
    std::vector<ValueType> buffer;

public:
    void Push(const ValueType v) {
        buffer.push_back(v);
    }

    auto Pop() {
        const auto v = buffer.back();
        buffer.pop_back();
        return v;
    }

    auto Peek() const {
        return buffer.back();
    }

    auto Empty() const {
        return buffer.empty();
    }
};


/** Implementing Stack using Linked List
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 10.1. Exercises 10.1-2.
 * @reference   John Mongan, Eric Giguere, Noah Kindler.
 *              Programming Interviews Exposed, Third Edition. Chapter 4.
 * @reference   Implement a stack using singly linked list
 *              https://www.geeksforgeeks.org/implement-a-stack-using-singly-linked-list/
 */
class ListStack {
    using ValueType = int;
    std::forward_list<ValueType> buffer;

public:
    void Push(const ValueType v) {
        buffer.push_front(v);
    }

    auto Pop() {
        const auto v = buffer.front();
        buffer.pop_front();
        return v;
    }

    auto Peek() const {
        return buffer.front();
    }

    auto Empty() const {
        return buffer.empty();
    }
};


/** Implement Stack using Queues
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 10.1. Exercises 10.1-7.
 * @reference   https://www.geeksforgeeks.org/implement-stack-using-queue/
 * @reference   Implement Stack using Queues
 *              https://leetcode.com/problems/implement-stack-using-queues/
 *
 * Implement a last-in-first-out (LIFO) stack using only two queues. The implemented
 * stack should support all the functions of a normal stack (push, top, pop, and empty).
 * Implement the MyStack class:
 *  void push(int x) Pushes element x to the top of the stack.
 *  int pop() Removes the element on the top of the stack and returns it.
 *  int top() Returns the element on the top of the stack.
 *  boolean empty() Returns true if the stack is empty, false otherwise.
 * Follow-up: Can you implement the stack using only one queue?
 */
class PushCostlyTwoQueueStack {
    using ValueType = int;
    std::queue<ValueType> push_queue, pop_queue;

public:
    void Push(const ValueType v) {
        push_queue.push(v);

        while (not pop_queue.empty()) {
            push_queue.push(pop_queue.front());
            pop_queue.pop();
        }

        push_queue.swap(pop_queue);
    }

    auto Pop() {
        const auto v = pop_queue.front();
        pop_queue.pop();
        return v;
    }

    auto Empty() const {
        return pop_queue.empty();
    }

    auto Peek() {
        pop_queue.front();
    }
};

class PopCostlyTwoQueueStack {
    using ValueType = int;
    std::queue<ValueType> push_queue, pop_queue;

public:
    void Push(const ValueType v) {
        push_queue.push(v);
    }

    auto Pop() {
        while (push_queue.size() != 1) {
            pop_queue.push(push_queue.front());
            push_queue.pop();
        }

        const auto v = push_queue.front();
        push_queue.pop();
        pop_queue.swap(push_queue);
        return v;
    }

    auto Empty() const {
        return push_queue.empty();
    }
};


/** Implement a stack using single queue
 *
 * @reference   https://www.geeksforgeeks.org/implement-a-stack-using-single-queue/
 */
class PushCostlyOneQueueStack {
    using ValueType = int;
    std::queue<ValueType> q;

public:
    void Push(const ValueType v) {
        q.push(v);
        for (auto i = q.size() - 1; i != 0; --i) {
            q.push(q.front());
            q.pop();
        }
    }

    auto Pop() {
        const auto v = q.front();
        q.pop();
        return v;
    }

    auto Empty() const {
        return q.empty();
    }

    auto Peek() {
        q.front();
    }
};


/** Implement stack using priority queue or heap
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 6.5. Exercises 6.5-7.
 * @reference   How to implement stack using priority queue or heap?
 *              https://www.geeksforgeeks.org/implement-stack-using-priority-queue-or-heap/
 */
class HeapStack {
    using ValueType = int;
    using KeyValuePair = std::pair<std::size_t, ValueType>;

    std::size_t index = 0;

    std::priority_queue<KeyValuePair, std::vector<KeyValuePair>, std::function<bool(const KeyValuePair &, const KeyValuePair &)>>
    queue{[](const auto & lhs, const auto & rhs) {
            return lhs.first < rhs.first;
        }};

public:
    void Push(const ValueType v) {
        queue.push(std::pair(index++, v));
    }

    auto Pop() {
        assert(not queue.empty());

        const auto v = queue.top().second;
        queue.pop();
        return v;
    }

    auto Empty() const {
        return queue.empty();
    }
};

namespace {

const std::vector<int> EXPECTED_ARRAY {7, 6, 3, 2, 1, 0};

template <typename Stack>
constexpr auto testStackHelper() {
    Stack stack;
    stack.Push(0);
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);
    stack.Push(4);
    stack.Push(5);
    stack.Pop();
    stack.Pop();
    stack.Push(6);
    stack.Push(7);

    std::vector<int> output;
    while (not stack.Empty()) {
        output.push_back(stack.Pop());
    }

    return output;
}


inline auto testArrayStack() {
    return testStackHelper<ArrayStack>();
}


inline auto testListStack() {
    return testStackHelper<ListStack>();
}


inline auto testPushCostlyTwoQueueStack() {
    return testStackHelper<PushCostlyTwoQueueStack>();
}


inline auto testPopCostlyTwoQueueStack() {
    return testStackHelper<PopCostlyTwoQueueStack>();
}


inline auto testPushCostlyOneQueueStack() {
    return testStackHelper<PushCostlyOneQueueStack>();
}


inline auto testHeapStack() {
    return testStackHelper<HeapStack>();
}


/**
 * @reference   Build an Array With Stack Operations
 *              https://leetcode.com/problems/build-an-array-with-stack-operations/
 *
 * You are given an array target and an integer n. In each iteration, you will read a
 * number from list = [1, 2, 3, ..., n]. Build the target array using the following
 * operations:
 *  "Push": Reads a new element from the beginning list, and pushes it in the array.
 *  "Pop": Deletes the last element of the array.
 *  If the target array is already built, stop reading more elements.
 * Return a list of the operations needed to build target. The test cases are generated
 * so that the answer is unique.
 */

}//namespace


SIMPLE_TEST0(testArrayStack, TestSample, EXPECTED_ARRAY);


SIMPLE_TEST0(testListStack, TestSample, EXPECTED_ARRAY);


SIMPLE_TEST0(testPushCostlyTwoQueueStack, TestSample, EXPECTED_ARRAY);


SIMPLE_TEST0(testPopCostlyTwoQueueStack, TestSample, EXPECTED_ARRAY);


SIMPLE_TEST0(testPushCostlyOneQueueStack, TestSample, EXPECTED_ARRAY);


SIMPLE_TEST0(testHeapStack, TestSample, EXPECTED_ARRAY);
