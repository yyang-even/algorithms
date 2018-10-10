#pragma once


template <typename ArrayType>
void MergeSort(const typename ArrayType::iterator begin, const typename ArrayType::size_type n,
               const std::function<void(const typename ArrayType::iterator,
                                        const typename ArrayType::iterator,
                                        const typename ArrayType::iterator)> merge) {
    if (n > 1) {
        const auto middle = n >> 1; //floor(n/2)
        const auto middle_begin = begin + middle;
        MergeSort<ArrayType>(begin, middle, merge);
        MergeSort<ArrayType>(middle_begin, n - middle, merge);
        merge(begin, middle_begin, begin + n);
    }
}
