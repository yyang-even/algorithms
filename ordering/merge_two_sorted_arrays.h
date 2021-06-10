#pragma once


template<typename InputIter, typename OutputIter, typename Compare>
static inline constexpr void
MergeTwoSortedArrays(InputIter L_citer, const InputIter L_cend,
                     InputIter R_citer, const InputIter R_cend,
                     OutputIter output_iter, const Compare compare) {

    for (; (L_citer != L_cend) and (R_citer != R_cend); ++output_iter) {
        if (compare(*L_citer, *R_citer)) {
            *output_iter = *L_citer++;
        } else {
            *output_iter = *R_citer++;
        }
    }

    output_iter = std::copy(L_citer, L_cend, output_iter);
    output_iter = std::copy(R_citer, R_cend, output_iter);
}

template<typename ArrayType>
static inline constexpr void
MergeTwoSortedArrays(const ArrayType &L, const ArrayType &R,
                     typename ArrayType::iterator output_iter) {
    MergeTwoSortedArrays(L.cbegin(), L.cend(), R.cbegin(), R.cend(), output_iter,
                         std::less<typename ArrayType::value_type>());
}

template<typename ArrayType>
static inline constexpr void
MergeTwoSortedArrays_Reverse(const ArrayType &L, const ArrayType &R,
                             typename ArrayType::iterator output_iter) {
    MergeTwoSortedArrays(L.crbegin(), L.crend(), R.crbegin(), R.crend(), output_iter,
                         std::greater<typename ArrayType::value_type>());
}
