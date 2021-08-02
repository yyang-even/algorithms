#pragma once


template <typename T>
using MatrixTypeTemplate = std::vector<std::vector<T>>;

using MatrixType = MatrixTypeTemplate<int>;


template <typename MatrixType>
static inline constexpr auto
ValidPoint(const MatrixType &screen, const int x, const int y) {
    return not(x < 0 or x >= static_cast<int>(screen.size()) or
               y < 0 or y >= static_cast<int>(screen.front().size()));
}


const std::vector<std::pair<int, int>> DIRECTIONS{{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
