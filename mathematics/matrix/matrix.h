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


static inline auto
ForEachDirection(const int M, const int N,
                 const int row, const int column,
                 const std::function<void(int, int)> visitor) {
    for (const auto [delta_r, delta_c] : DIRECTIONS) {
        const auto new_r = row + delta_r;
        const auto new_c = column + delta_c;
        if (new_r >= 0 and new_c >= 0 and new_r < M and new_c < N) {
            visitor(new_r, new_c);
        }
    }
}
