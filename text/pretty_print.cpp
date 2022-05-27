#include "common_header.h"


namespace {

using ArrayType = std::vector<int>;

/** Pretty Columns Print
 *
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Section 3.4.
 *
 * We have n short lines of text that we'd like to arrange in m columns. For aesthetic reasons,
 * we want the columns to be arranged in decreasing order of length (actually non-increasing
 * order); and the lengths should be approximately the same --- no two columns should differ by
 * more than one line's worth of text. Furthermore we want to distribute the lines of text
 * column-wise.
 */
inline auto PrettyColumnsPrint(const unsigned n, const unsigned m) {
    assert(m);

    std::cout << "Arrange " << n << " short lines of text in " << m << " columns." << std::endl;
    const unsigned short_column_lines = n / m;
    const unsigned long_column_lines = std::ceil(double(n) / double(m));
    const unsigned num_long_columns = n % m;
    //Use the array to track the current line index of each column.
    std::vector<unsigned> line_indice(m);
    for (unsigned i = 0, line_index = 1; i < m; ++i) {
        line_indice[i] = line_index;
        if (i < num_long_columns) {
            line_index += long_column_lines;
        } else {
            line_index += short_column_lines;
        }
    }

    std::stringstream output;
    for (unsigned i = 0; i < short_column_lines; ++i) {
        for (unsigned j = 0; j < m; ++j) {
            output << "line " << line_indice[j]++ << "\t";
        }
        output << std::endl;
    }

    if (num_long_columns) {
        for (unsigned i = 0; i < num_long_columns; ++i) {
            output << "line " << line_indice[i]++ << "\t";
        }
        output << std::endl;
    }

    return output.str();
}

template<typename T>
inline void GetOneInput(T &input, const std::string_view inputName) {
    std::cout << "Enter \"" << inputName << "\": ";
    std::cin >> input;
    if (!std::cin) {
        std::cout << "Invalid input." << std::endl;
        exit(EXIT_FAILURE);
    }
}


/**
 * @reference   Number of Lines To Write String
 *              https://leetcode.com/problems/number-of-lines-to-write-string/
 *
 * You are given a string s of lowercase English letters and an array widths denoting how many
 * pixels wide each lowercase English letter is. Specifically, widths[0] is the width of 'a',
 * widths[1] is the width of 'b', and so on.
 * You are trying to write s across several lines, where each line is no longer than 100 pixels.
 * Starting at the beginning of s, write as many letters on the first line such that the total
 * width does not exceed 100 pixels. Then, from where you stopped in s, continue writing as many
 * letters as you can on the second line. Continue this process until you have written all of s.
 * Return an array result of length 2 where:
 *  result[0] is the total number of lines.
 *  result[1] is the width of the last line in pixels.
 */
inline auto NumberLinesNeeded(const ArrayType &widths, const std::string_view s) {
    int no_line = 1;
    int line_width = 0;
    for (const auto c : s) {
        const auto w = widths[c - 'a'];
        line_width += w;
        if (line_width > 100) {
            ++no_line;
            line_width = w;
        }
    }

    return std::pair {no_line, line_width};
}

} //namespace


#ifdef WANT_TERMINAL_APP
int main(int, char **) {
    std::cout << "PrettyColumnsPrint(const unsigned n, const unsigned m): " << std::endl;

    unsigned n;
    GetOneInput(n, "n");
    unsigned m;
    GetOneInput(m, "m");

    std::cout << PrettyColumnsPrint(n, m) << std::endl;
    return EXIT_SUCCESS;
}
#endif


SIMPLE_TEST(PrettyColumnsPrint,
            PrettyColumnsPrint_37_5,
            "line 1\tline 9\tline 17\tline 24\tline 31\t\n"
            "line 2\tline 10\tline 18\tline 25\tline 32\t\n"
            "line 3\tline 11\tline 19\tline 26\tline 33\t\n"
            "line 4\tline 12\tline 20\tline 27\tline 34\t\n"
            "line 5\tline 13\tline 21\tline 28\tline 35\t\n"
            "line 6\tline 14\tline 22\tline 29\tline 36\t\n"
            "line 7\tline 15\tline 23\tline 30\tline 37\t\n"
            "line 8\tline 16\t\n",
            37,
            5);

SIMPLE_TEST(PrettyColumnsPrint,
            PrettyColumnsPrint_10_5,
            "line 1\tline 3\tline 5\tline 7\tline 9\t\n"
            "line 2\tline 4\tline 6\tline 8\tline 10\t\n",
            10,
            5);


const ArrayType SAMPLE1 = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
                           10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
const std::pair EXPECTED1 = {3, 60};

const ArrayType SAMPLE2 = {4,  10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
                           10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
const std::pair EXPECTED2 = {2, 4};


THE_BENCHMARK(NumberLinesNeeded, SAMPLE1, "abcdefghijklmnopqrstuvwxyz");

SIMPLE_TEST(NumberLinesNeeded, TestSAMPLE1, EXPECTED1, SAMPLE1, "abcdefghijklmnopqrstuvwxyz");
SIMPLE_TEST(NumberLinesNeeded, TestSAMPLE2, EXPECTED2, SAMPLE2, "bbbcccdddaaa");
