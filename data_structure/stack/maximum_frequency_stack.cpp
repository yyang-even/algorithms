#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;
using OperationArray = std::vector<std::pair<bool, int>>;

/** Maximum Frequency Stack
 *
 * @reference   https://leetcode.com/problems/maximum-frequency-stack/
 *
 * Design a stack-like data structure to push elements to the stack and pop the most frequent
 * element from the stack.
 * Implement the FreqStack class:
 *  FreqStack() constructs an empty frequency stack.
 *  void push(int val) pushes an integer val onto the top of the stack.
 *  int pop() removes and returns the most frequent element in the stack.
 *      If there is a tie for the most frequent element, the element closest to the stack's top
 *      is removed and returned.
 */
class FreqStack {
public:
    void push(const int v) {
        const auto f = ++m_frequency[v];
        if (f > m_max_frequency)
            m_max_frequency = f;
        m_group[f].push(v);
    }

    int pop() {
        auto &max_group = m_group[m_max_frequency];
        const auto v = max_group.top();
        max_group.pop();
        --m_frequency[v];
        if (max_group.empty()) {
            --m_max_frequency;
        }

        return v;
    }

private:
    std::unordered_map<int, int> m_frequency;
    std::unordered_map<int, std::stack<int>> m_group;
    int m_max_frequency = 0;
};

auto testFreqStack(const OperationArray &operations) {
    FreqStack s;
    ArrayType result;
    for (const auto &[is_push, v] : operations) {
        if (is_push) {
            s.push(v);
        } else {
            result.push_back(s.pop());
        }
    }

    return result;
}

} //namespace


const OperationArray SAMPLE1 = {{true, 5},
                                {true, 7},
                                {true, 5},
                                {true, 7},
                                {true, 4},
                                {true, 5},
                                {false, 0},
                                {false, 0},
                                {false, 0},
                                {false, 0}};
const ArrayType EXPECTED1 = {5, 7, 5, 4};


THE_BENCHMARK(testFreqStack, SAMPLE1);

SIMPLE_TEST(testFreqStack, TestSAMPLE1, EXPECTED1, SAMPLE1);
