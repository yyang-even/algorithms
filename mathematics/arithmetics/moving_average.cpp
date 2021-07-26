#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;
using OutputType = std::vector<double>;

/** Moving Average from Data Stream
 *
 * @reference   https://goodtecher.com/leetcode-346-moving-average-from-data-stream/
 *
 * Given a stream of integers and a window size, calculate the moving average of all
 * integers in the sliding window.
 */
auto MovingAverage(const ArrayType &elements, const std::size_t K) {
    long sum = 0;
    std::deque<int> q;

    OutputType results;
    for (const auto a_number : elements) {
        sum += a_number;
        q.push_back(a_number);

        if (q.size() > K) {
            sum -= q.front();
            q.pop_front();
        }

        results.push_back(static_cast<double>(sum) / q.size());
    }

    return results;
}

}//namespace


const ArrayType SAMPLE1 = {1, 10, 3, 5};
const OutputType EXPECTED1 = {1.0, 5.5, 14.0 / 3, 6.0};


THE_BENCHMARK(MovingAverage, SAMPLE1, 3);

SIMPLE_TEST(MovingAverage, TestSAMPLE1, EXPECTED1, SAMPLE1, 3);
