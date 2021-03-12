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
 */
auto validPoint(const MatrixType &screen, const int x, const int y) {
    return not(x < 0 or x >= static_cast<int>(screen.size()) or
               y < 0 or y >= static_cast<int>(screen.front().size()));
}

void FloodFill_Recursive(MatrixType &screen, const int x, const int y,
                         const int new_color, const int original_color) {
    assert(original_color != new_color);

    if (not validPoint(screen, x, y)) {
        return;
    }

    if (auto &current_color = screen[x][y]; current_color == original_color) {
        current_color = new_color;

        FloodFill_Recursive(screen, x + 1, y, new_color, original_color);
        FloodFill_Recursive(screen, x - 1, y, new_color, original_color);
        FloodFill_Recursive(screen, x, y + 1, new_color, original_color);
        FloodFill_Recursive(screen, x, y - 1, new_color, original_color);
    }
}

auto FloodFill_Recursive(MatrixType screen, const unsigned x, const unsigned y,
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

    auto visited_pixels = std::vector(screen.size(),
                                      std::vector<bool>(screen.front().size(), false));
    std::queue<std::pair<int, int>> points_queue;
    points_queue.push({start_x, start_y});
    visited_pixels[start_x][start_y] = 1;

    while (not points_queue.empty()) {
        const auto [x, y] = points_queue.front();
        points_queue.pop();

        screen[x][y] = new_color;

        const auto visitPixel =
            [&screen = std::as_const(screen), &visited_pixels, &points_queue,
                original_color](const int x, const int y) {
            if (validPoint(screen, x, y) and not visited_pixels[x][y] and
                screen[x][y] == original_color) {
                points_queue.push({x, y});
                visited_pixels[x][y] = true;
            }
        };

        visitPixel(x + 1, y);
        visitPixel(x - 1, y);
        visitPixel(x, y + 1);
        visitPixel(x, y - 1);
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
