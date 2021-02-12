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
 * @reference   Stack Data Structure (Introduction and Program)
 *              https://www.geeksforgeeks.org/stack-data-structure-introduction-program/
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
 *              Introduction to Algorithms, Third Edition. Section 10.1. Exercises 10.1-2.
 * @reference   https://www.geeksforgeeks.org/implement-two-stacks-in-an-array/
 */
class OneArrayTwoStacks {
    using ValueType = int;

    const std::size_t CAPACITY;
    std::vector<ValueType> buffer;
    int top1 = -1;
    int top2;

public:
    OneArrayTwoStacks(const std::size_t cap = 2048):
        CAPACITY(cap), buffer(cap, 0), top2(cap) {}

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
        assert(static_cast<std::size_t>(top2) < CAPACITY);

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
 *              Introduction to Algorithms, Third Edition. Section 6.5. Exercises 6.5-7.
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


/** How to efficiently implement k stacks in a single array?
 *
 * @reference   https://www.geeksforgeeks.org/efficiently-implement-k-stacks-single-array/
 *
 * Create a data structure kStacks that represents k stacks. Implementation of kStacks
 * should use only one array, i.e., k stacks should use the same array for storing
 * elements. Following functions must be supported by kStacks.
 *  push(int x, int sn) -> pushes x to stack number 'sn' where sn is from 0 to k-1
 *  pop(int sn) -> pops an element from stack number 'sn' where sn is from 0 to k-1
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 3.1.
 */
class kStacks {
public:
    using ValueType = int;

private:
    const std::size_t K;
    const std::size_t CAPACITY;
    std::vector<ValueType> buffer;
    std::vector<int> tops;
    std::vector<int> nexts;
    int free_list_begin = 0;

public:
    kStacks(const std::size_t k = 3, const std::size_t cap = 2048):
        K(k), CAPACITY(cap), buffer(cap, 0), tops(k, -1), nexts(cap, 0) {
        for (std::size_t i = 0; i < cap; ++i) {
            nexts[i] = i + 1;
        }
        nexts.back() = -1;
    }

    auto isFull() const {
        return free_list_begin == -1;
    }

    auto isEmpty(const std::size_t stack_index) const {
        return tops[stack_index] == -1;
    }

    auto Push(const std::size_t stack_index, const ValueType v) {
        if (isFull()) {
            return false;
        }

        const auto original_free_begin = free_list_begin;
        free_list_begin = nexts[original_free_begin];
        nexts[original_free_begin] = tops[stack_index];
        tops[stack_index] = original_free_begin;

        buffer[original_free_begin] = v;

        return true;
    }

    auto Pop(const std::size_t stack_index) {
        assert(not isEmpty(stack_index));

        const auto stack_top = tops[stack_index];
        tops[stack_index] = nexts[stack_top];
        nexts[stack_top] = free_list_begin;
        free_list_begin = stack_top;

        return buffer[stack_top];
    }
};

namespace {

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


auto testListStack() {
    return testStackHelper<ListStack>();
}


auto testPushCostlyTwoQueueStack() {
    return testStackHelper<PushCostlyTwoQueueStack>();
}


auto testPopCostlyTwoQueueStack() {
    return testStackHelper<PopCostlyTwoQueueStack>();
}


auto testPushCostlyOneQueueStack() {
    return testStackHelper<PushCostlyOneQueueStack>();
}


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


auto testHeapStack() {
    return testStackHelper<HeapStack>();
}


auto clearStack(kStacks &one_k_stacks, const std::size_t stack_index) {
    std::vector<kStacks::ValueType> results;
    while (not one_k_stacks.isEmpty(stack_index)) {
        results.push_back(one_k_stacks.Pop(stack_index));
    }

    return results;
}

}//namespace


#ifdef WANT_TESTS
TEST(kStacksTests, TestSanity) {
    kStacks three_stacks{3};
    three_stacks.Push(1, 11);
    three_stacks.Push(1, 12);
    three_stacks.Push(1, 13);
    three_stacks.Push(0, 1);
    three_stacks.Push(2, 21);
    three_stacks.Push(1, 14);
    three_stacks.Push(2, 22);
    three_stacks.Push(0, 2);
    three_stacks.Push(0, 3);
    three_stacks.Push(1, 15);
    three_stacks.Pop(1);
    three_stacks.Pop(1);
    three_stacks.Push(1, 16);
    three_stacks.Push(0, 4);
    three_stacks.Push(0, 5);
    three_stacks.Push(2, 23);
    three_stacks.Pop(0);
    three_stacks.Pop(1);
    three_stacks.Pop(2);
    three_stacks.Pop(1);
    three_stacks.Push(1, 17);
    three_stacks.Push(0, 6);
    three_stacks.Push(2, 24);

    const std::vector<kStacks::ValueType> EXPECTED0 = {6, 4, 3, 2, 1};
    EXPECT_EQ(EXPECTED0, clearStack(three_stacks, 0));

    const std::vector<kStacks::ValueType> EXPECTED1 = {17, 12, 11};
    EXPECT_EQ(EXPECTED1, clearStack(three_stacks, 1));

    const std::vector<kStacks::ValueType> EXPECTED2 = {24, 22, 21};
    EXPECT_EQ(EXPECTED2, clearStack(three_stacks, 2));
}
#endif


SIMPLE_TEST0(testArrayStack, TestSample, EXPECTED_ARRAY);


SIMPLE_TEST0(testListStack, TestSample, EXPECTED_ARRAY);


SIMPLE_TEST0(testPushCostlyTwoQueueStack, TestSample, EXPECTED_ARRAY);


SIMPLE_TEST0(testPopCostlyTwoQueueStack, TestSample, EXPECTED_ARRAY);


SIMPLE_TEST0(testPushCostlyOneQueueStack, TestSample, EXPECTED_ARRAY);


SIMPLE_TEST0(testOneArrayTwoStacks, TestSample, EXPECTED_TWO_STACKS_ARRAY);


SIMPLE_TEST0(testHeapStack, TestSample, EXPECTED_ARRAY);
