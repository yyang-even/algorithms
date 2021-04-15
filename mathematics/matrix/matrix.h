#pragma once


template <typename T>
using MatrixTypeTemplate = std::vector<std::vector<T>>;

using MatrixType = MatrixTypeTemplate<int>;


template <typename MatrixType>
static inline auto ValidPoint(const MatrixType &screen, const int x, const int y) {
    return not(x < 0 or x >= static_cast<int>(screen.size()) or
               y < 0 or y >= static_cast<int>(screen.front().size()));
}
