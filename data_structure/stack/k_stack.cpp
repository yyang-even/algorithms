#include "common_header.h"


/** Implement two stacks in an array
 *
 * @reference   Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein.
 *              Introduction to Algorithms, Third Edition. Section 10.1. Exercises 10.1-2.
 * @reference   https://www.geeksforgeeks.org/implement-two-stacks-in-an-array/
 */
class OneArrayTwoStacks {
    using ValueType = int;

    std::size_t CAPACITY;
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
    std::size_t K;
    std::size_t CAPACITY;
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


auto clearStack(kStacks &one_k_stacks, const std::size_t stack_index) {
    std::vector<kStacks::ValueType> results;
    while (not one_k_stacks.isEmpty(stack_index)) {
        results.push_back(one_k_stacks.Pop(stack_index));
    }

    return results;
}

}//namespace


const std::vector<int> EXPECTED_TWO_STACKS_ARRAY {1, 2, 8, 7, 5, 4};


SIMPLE_TEST0(testOneArrayTwoStacks, TestSample, EXPECTED_TWO_STACKS_ARRAY);


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
