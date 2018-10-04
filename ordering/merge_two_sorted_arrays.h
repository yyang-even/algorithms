#pragma once

template<typename ArrayType>
void MergeTwoSortedArrays(const ArrayType &L, const ArrayType &R, typename ArrayType::iterator output_iter){
    auto L_iter = L.cbegin();
    auto R_iter = R.cbegin();
    for (; (L_iter != L.cend()) and (R_iter != R.cend()); ++output_iter) {
        if (*L_iter <= *R_iter) {
            *output_iter = *L_iter++;
        } else {
            *output_iter = *R_iter++;
        }
    }

    output_iter = std::copy(L_iter, L.cend(), output_iter);
    output_iter = std::copy(R_iter, R.cend(), output_iter);
}
