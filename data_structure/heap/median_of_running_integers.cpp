#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Median of Stream of Running Integers using STL
 *
 * @reference   https://www.geeksforgeeks.org/median-of-stream-of-running-integers-using-stl/
 * @reference   Median in a stream of integers (running integers)
 *              https://www.geeksforgeeks.org/median-of-stream-of-integers-running-integers/
 * @reference   Section VI. Five Algorithm Approaches.
 *              Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 18.9.
 *
 * Given that integers are being read from a data stream. Find median of all the elements
 * read so far starting from the first integer till the last integer. This is also called
 * Median of Running Integers. The data stream can be any source of data, example: a file,
 * an array of integers, input stream etc.
 * Median can be defined as the element in the data set which separates the higher half of
 * the data sample from the lower half. In other words we can get the median element as,
 * when the input size is odd, we take the middle element of sorted data. If the input size
 * is even, we pick average of middle two elements in sorted stream.
 */
auto MedianOfRunningIntegers(const ArrayType &ints) {
    assert(not ints.empty());
    std::vector<double> outputs;

    std::priority_queue<ArrayType::value_type> smaller_half;
    std::priority_queue<ArrayType::value_type, ArrayType, std::greater<ArrayType::value_type>>
            greater_half;

    double median = ints.front();
    for (const auto n : ints) {
        if (smaller_half.size() == greater_half.size()) {
            if (n < median) {
                smaller_half.push(n);
                median = smaller_half.top();
            } else {
                greater_half.push(n);
                median = greater_half.top();
            }
        } else {
            if (smaller_half.size() > greater_half.size()) {
                if (n < median) {
                    greater_half.push(smaller_half.top());
                    smaller_half.pop();
                    smaller_half.push(n);
                } else {
                    greater_half.push(n);
                }

            } else { //smaller_half.size() < greater_half.size()
                if (n > median) {
                    smaller_half.push(greater_half.top());
                    greater_half.pop();
                    greater_half.push(n);
                } else {
                    smaller_half.push(n);
                }
            }

            median = (smaller_half.top() + greater_half.top()) / 2.0;
        }

        outputs.push_back(median);
    }

    return outputs;
}

}//namespace


const ArrayType SAMPLE_ARRAY = {5, 15, 10, 20, 3};
const std::vector<double> EXPECTED_ARRAY = {5, 10, 10, 12.5, 10};


THE_BENCHMARK(MedianOfRunningIntegers, {7, 8, 5, 6, 3, 7, 5, 1, 5, 6, 7, 6, 4, 6, 2, 1, 3, 4, 6, 5, 7, 8, 9});

SIMPLE_TEST(MedianOfRunningIntegers, TestSample, EXPECTED_ARRAY, SAMPLE_ARRAY);
