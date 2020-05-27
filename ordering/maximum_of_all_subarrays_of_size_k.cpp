#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Sliding Window Maximum (Maximum of all subarrays of size k)
 *
 * @reference   https://www.geeksforgeeks.org/sliding-window-maximum-maximum-of-all-subarrays-of-size-k/
 * @reference   Maximum of all Subarrays of size k using set in C++ STL
 *              https://www.geeksforgeeks.org/maximum-of-all-subarrays-of-size-k-using-set-in-cpp-stl/
 *
 * @reference   Minimum and Maximum of all subarrays of size K using Map
 *              https://www.geeksforgeeks.org/minimum-and-maximum-of-all-subarrays-of-size-k-using-map/
 *
 * @reference   Sum of minimum and maximum elements of all subarrays of size k.
 *              https://www.geeksforgeeks.org/sum-minimum-maximum-elements-subarrays-size-k/
 */
auto MaxOfAllSubarraysOfSizeK_Multiset(const ArrayType &elements, const ArrayType::size_type K) {
    assert(K);
    assert(elements.size() >= K);

    std::multiset<ArrayType::value_type> subarray_set(elements.cbegin(), elements.cbegin() + K);
    ArrayType result = {*subarray_set.crbegin()};
    for (auto i = K; i < elements.size(); ++i) {
        subarray_set.erase(subarray_set.find(elements[i - K]));
        subarray_set.insert(elements[i]);
        result.push_back(*subarray_set.crbegin());
    }

    return result;
}


auto MaxOfAllSubarraysOfSizeK_Deque(const ArrayType &elements, const ArrayType::size_type K) {
    assert(K);
    assert(elements.size() >= K);

    std::deque<ArrayType::size_type> useful_elements_deque;
    ArrayType result;
    for (ArrayType::size_type i = 0; i < elements.size(); ++i) {
        if (i >= K) {
            result.push_back(elements[useful_elements_deque.front()]);

            while ((not useful_elements_deque.empty()) and useful_elements_deque.front() <= i - K) {
                useful_elements_deque.pop_front();
            }
        }

        while ((not useful_elements_deque.empty()) and
               elements[i] >= elements[useful_elements_deque.back()]) {
            useful_elements_deque.pop_back();
        }

        useful_elements_deque.push_back(i);
    }
    result.push_back(elements[useful_elements_deque.front()]);

    return result;
}


/**
 * @reference   Sliding Window Maximum : Set 2
 *              https://www.geeksforgeeks.org/sliding-window-maximum-set-2/
 *
 * @note    Same as the naive solution in Set 1.
 */

}//namespace


const ArrayType SAMPLE1 = {1, 2, 3, 1, 4, 5, 2, 3, 6};
const ArrayType EXPECTED1 = {3, 3, 4, 5, 5, 5, 6};

const ArrayType SAMPLE2 = {8, 5, 10, 7, 9, 4, 15, 12, 90, 13};
const ArrayType EXPECTED2 = {10, 10, 10, 15, 15, 90, 90};


SIMPLE_BENCHMARK(MaxOfAllSubarraysOfSizeK_Multiset, SAMPLE1, 3);

SIMPLE_TEST(MaxOfAllSubarraysOfSizeK_Multiset, TestSAMPLE1, EXPECTED1, SAMPLE1, 3);
SIMPLE_TEST(MaxOfAllSubarraysOfSizeK_Multiset, TestSAMPLE2, EXPECTED2, SAMPLE2, 4);


SIMPLE_BENCHMARK(MaxOfAllSubarraysOfSizeK_Deque, SAMPLE1, 3);

SIMPLE_TEST(MaxOfAllSubarraysOfSizeK_Deque, TestSAMPLE1, EXPECTED1, SAMPLE1, 3);
SIMPLE_TEST(MaxOfAllSubarraysOfSizeK_Deque, TestSAMPLE2, EXPECTED2, SAMPLE2, 4);
