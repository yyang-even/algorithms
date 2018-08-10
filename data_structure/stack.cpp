#include "common_header.h"

#include <forward_list>

#include "3rdParty/prettyprint.hpp"

/** Implementing Stack using Arrays
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 10.1.
 * @reference   Stack Data Structure (Introduction and Program)
 *              https://www.geeksforgeeks.org/stack-data-structure-introduction-program/
 */
class ArrayStack {
    using ValueType = int;
    std::vector<ValueType> buffer;

public:
    void Push(const ValueType v) {
        buffer.push_back(v);
    }

    void Pop() {
        buffer.pop_back();
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
 *              Introduction to Algorithms, Third Edition. Chapter 10.1. Exercises 10.1-2.
 * @reference   Stack Data Structure (Introduction and Program)
 *              https://www.geeksforgeeks.org/stack-data-structure-introduction-program/
 */
class ListStack {
    using ValueType = int;
    std::forward_list<ValueType> buffer;

public:
    void Push(const ValueType v) {
        buffer.push_front(v);
    }

    void Pop() {
        buffer.pop_front();
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
 *              Introduction to Algorithms, Third Edition. Chapter 10.1. Exercises 10.1-7.
 * @reference   https://www.geeksforgeeks.org/implement-stack-using-queue/
 */
class PushCostlyTwoQueueStack {
    using ValueType = int;
    std::queue<ValueType> push_queue, pop_queue;

    public:
    void Push(const ValueType v) {
        push_queue.push(v);

        while(not pop_queue.empty()){
            push_queue.push(pop_queue.front());
            pop_queue.pop();
        }

        push_queue.swap(pop_queue);
    }

    void Pop() {
        pop_queue.pop();
    }

    auto Empty() const {
        return pop_queue.empty();
    }
};

class PopCostlyTwoQueueStack {
    using ValueType = int;
    std::queue<ValueType> push_queue, pop_queue;

    public:
    void Push(const ValueType v) {
        push_queue.push(v);
    }

    void Pop() {
        while(push_queue.size() != 1) {
            pop_queue.push(push_queue.front());
            push_queue.pop();
        }

        //const auto v = push_queue.front();
        push_queue.pop();
        pop_queue.swap(push_queue);
        //return v;
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
        for(auto i = q.size() - 1; i != 0; --i) {
            q.push(q.front());
            q.pop();
        }
    }

    void Pop() {
        q.pop();
    }

    auto Empty() const {
        q.empty();
    }
};


const std::vector<int> EXPECTED_ARRAY {7, 6, 3, 2, 1, 0};

template <typename Stack>
auto testStackHelper() {
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
        output.push_back(stack.Peek());
        stack.Pop();
    }

    return output;
}

auto testArrayStack() {
    return testStackHelper<ArrayStack>();
}

SIMPLE_TEST0(testArrayStack, TestSample, EXPECTED_ARRAY);


auto testListStack() {
    return testStackHelper<ListStack>();
}

SIMPLE_TEST0(testListStack, TestSample, EXPECTED_ARRAY);


auto testPushCostlyTwoQueueStack() {
    return testStackHelper<PushCostlyTwoQueueStack>();
}

SIMPLE_TEST0(testPushCostlyTwoQueueStack, TestSample, EXPECTED_ARRAY);


auto testPopCostlyTwoQueueStack() {
    return testStackHelper<PopCostlyTwoQueueStack>();
}

SIMPLE_TEST0(testPopCostlyTwoQueueStack, TestSample, EXPECTED_ARRAY);


auto testPushCostlyOneQueueStack() {
    return testStackHelper<PushCostlyOneQueueStack>();
}

SIMPLE_TEST0(testPushCostlyOneQueueStack, TestSample, EXPECTED_ARRAY);
