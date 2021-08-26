#include "common_header.h"

#include "mathematics/matrix/matrix.h"


namespace {

/** Flood fill Algorithm – how to implement fill() in paint?
 *
 * @reference   https://www.geeksforgeeks.org/flood-fill-algorithm-implement-fill-paint/
 * @reference   Flood Fill Algorithm
 *              https://www.geeksforgeeks.org/flood-fill-algorithm/
 *
 * In MS-Paint, when we take the brush to a pixel and click, the color of the region of
 * that pixel is replaced with a new selected color. Following is the problem statement
 * to do this task.
 * Given a 2D screen, location of a pixel in the screen and a color, replace color of
 * the given pixel and all adjacent same colored pixels with the given color.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 9.7.
 *
 * @reference   Flood Fill
 *              https://leetcode.com/problems/flood-fill/
 *
 * An image is represented by an m x n integer grid image where image[i][j] represents
 * the pixel value of the image. You are also given three integers sr, sc, and newColor.
 * You should perform a flood fill on the image starting from the pixel image[sr][sc].
 * To perform a flood fill, consider the starting pixel, plus any pixels connected
 * 4-directionally to the starting pixel of the same color as the starting pixel, plus
 * any pixels connected 4-directionally to those pixels (also with the same color), and
 * so on. Replace the color of all of the aforementioned pixels with newColor. Return
 * the modified image after performing the flood fill.
 */
void FloodFill_Recursive(MatrixType &screen, const std::size_t x, const std::size_t y,
                         const int new_color, const int original_color) {
    assert(original_color != new_color);

    if (auto &current_color = screen[x][y]; current_color == original_color) {
        current_color = new_color;

        if (x + 1 < screen.size()) {
            FloodFill_Recursive(screen, x + 1, y, new_color, original_color);
        }
        if (x > 0) {
            FloodFill_Recursive(screen, x - 1, y, new_color, original_color);
        }
        if (y + 1 < screen.front().size()) {
            FloodFill_Recursive(screen, x, y + 1, new_color, original_color);
        }
        if (y > 0) {
            FloodFill_Recursive(screen, x, y - 1, new_color, original_color);
        }
    }
}

inline auto
FloodFill_Recursive(MatrixType screen, const unsigned x, const unsigned y,
                    const int new_color) {
    assert(x < screen.size() and y < screen.front().size());

    if (new_color != screen[x][y]) {
        FloodFill_Recursive(screen, x, y, new_color, screen[x][y]);
    }

    return screen;
}


auto FloodFill_BFS(MatrixType screen, const unsigned start_x, const unsigned start_y,
                   const int new_color) {
    assert(start_x < screen.size() and start_y < screen.front().size());

    const auto original_color = screen[start_x][start_y];
    if (new_color == original_color) {
        return screen;
    }

    const int M = screen.size();
    const int N = screen.front().size();
    std::queue<std::pair<int, int>> points_queue;
    points_queue.push({start_x, start_y});

    while (not points_queue.empty()) {
        const auto [x, y] = points_queue.front();
        points_queue.pop();

        screen[x][y] = new_color;

        if (x > 0 and screen[x - 1][y] == original_color) {
            points_queue.emplace(x - 1, y);
        }
        if (x + 1 < M and screen[x + 1][y] == original_color) {
            points_queue.emplace(x + 1, y);
        }
        if (y > 0 and screen[x][y - 1] == original_color) {
            points_queue.emplace(x, y - 1);
        }
        if (y + 1 < N and screen[x][y + 1] == original_color) {
            points_queue.emplace(x, y + 1);
        }
    }

    return screen;
}

}//namespace


const MatrixType SAMPLE1 = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 0},
    {1, 0, 0, 1, 1, 0, 1, 1},
    {1, 2, 2, 2, 2, 0, 1, 0},
    {1, 1, 1, 2, 2, 0, 1, 0},
    {1, 1, 1, 2, 2, 2, 2, 0},
    {1, 1, 1, 1, 1, 2, 1, 1},
    {1, 1, 1, 1, 1, 2, 2, 1}
};

const MatrixType EXPECTED1 = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 0},
    {1, 0, 0, 1, 1, 0, 1, 1},
    {1, 3, 3, 3, 3, 0, 1, 0},
    {1, 1, 1, 3, 3, 0, 1, 0},
    {1, 1, 1, 3, 3, 3, 3, 0},
    {1, 1, 1, 1, 1, 3, 1, 1},
    {1, 1, 1, 1, 1, 3, 3, 1}
};


THE_BENCHMARK(FloodFill_Recursive, SAMPLE1, 4, 4, 3);

SIMPLE_TEST(FloodFill_Recursive, TestSAMPLE1, EXPECTED1, SAMPLE1, 4, 4, 3);
SIMPLE_TEST(FloodFill_Recursive, TestSAMPLE2, SAMPLE1, SAMPLE1, 4, 4, 2);


THE_BENCHMARK(FloodFill_BFS, SAMPLE1, 4, 4, 3);

SIMPLE_TEST(FloodFill_BFS, TestSAMPLE1, EXPECTED1, SAMPLE1, 4, 4, 3);
SIMPLE_TEST(FloodFill_BFS, TestSAMPLE2, SAMPLE1, SAMPLE1, 4, 4, 2);
