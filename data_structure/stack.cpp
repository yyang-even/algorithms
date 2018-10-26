#include "common_header.h"

#include <forward_list>
#include <queue>


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
 *              Introduction to Algorithms, Third Edition. Chapter 10.1. Exercises 10.1-7.
 * @reference   https://www.geeksforgeeks.org/implement-stack-using-queue/
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


/** Implement two stacks in an array
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 10.1. Exercises 10.1-2.
 * @reference   https://www.geeksforgeeks.org/implement-two-stacks-in-an-array/
 */
class OneArrayTwoStacks {
    using ValueType = int;

    const std::size_t CAPACITY;
    std::vector<ValueType> buffer;
    int top1 = -1;
    int top2;

public:
    OneArrayTwoStacks(const std::size_t cap = 2048) : CAPACITY(cap), buffer(cap, 0), top2(cap) {}

    void Push1(const ValueType v) {
        assert(top1 < top2 - 1);

        buffer[++top1] = v;
    }

    void Push2(const ValueType v) {
        assert(top1 < top2 - 1);

        buffer[--top2] = v;
    }

    auto Pop1() {
        assert(top1 >= 0);

        const auto v = buffer[top1--];
        return v;
    }

    auto Pop2() {
        assert(top2 < CAPACITY);

        const auto v = buffer[top2++];
        return v;
    }

    auto CopyToArray() const {
        return buffer;
    }
};


/** Implement stack using priority queue or heap
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Chapter 6.5. Exercises 6.5-7.
 * @reference   How to implement stack using priority queue or heap?
 *              https://www.geeksforgeeks.org/implement-stack-using-priority-queue-or-heap/
 */
class HeapStack {
    using ValueType = int;
    using KeyValuePair = std::pair<std::size_t, ValueType>;

    std::priority_queue<KeyValuePair, std::vector<KeyValuePair>, std::function<bool(const KeyValuePair &, const KeyValuePair &)>>
    queue{[](const auto & lhs, const auto & rhs) {
            return lhs.first < rhs.first;
        }};

public:
    void Push(const ValueType v) {
        queue.push(std::make_pair(queue.size(), v));
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
        output.push_back(stack.Pop());
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


auto testOneArrayTwoStacks() {
    OneArrayTwoStacks stacks{6};
    stacks.Push1(1);
    stacks.Push1(2);
    stacks.Push1(3);
    stacks.Push2(4);
    stacks.Push2(5);
    stacks.Push2(6);
    stacks.Pop1();
    stacks.Pop2();
    stacks.Push2(7);
    stacks.Push2(8);

    return stacks.CopyToArray();
}

const std::vector<int> EXPECTED_TWO_STACKS_ARRAY {1, 2, 8, 7, 5, 4};

SIMPLE_TEST0(testOneArrayTwoStacks, TestSample, EXPECTED_TWO_STACKS_ARRAY);


auto testHeapStack() {
    return testStackHelper<HeapStack>();
}

SIMPLE_TEST0(testHeapStack, TestSample, EXPECTED_ARRAY);
