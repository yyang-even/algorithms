#pragma once


using MatrixType = std::vector<std::vector<int>>;


static inline auto ValidPoint(const MatrixType &screen, const int x, const int y) {
    return not(x < 0 or x >= static_cast<int>(screen.size()) or
               y < 0 or y >= static_cast<int>(screen.front().size()));
}

