#include "common_header.h"

/** Pretty Columns Print
 * @reference   Ronald Graham, Oren Patashnik, Donald Knuth.
 *              Concrete Mathematics: A Foundation for Computer Science (2nd Edition). Chapter 1.3.
 *
 * We have n short lines of text that we'd like to arrange in m columns. For
 * aesthetic reasons, we want the columns to be arranged in decreasing order
 * of length (actually non-increasing order); and the lengths should be
 * approximately the same --- no two columns should differ by more than one
 * line's worth of text. Furthermore we want to distribute the lines of text
 * column-wise.
 */
std::string PrettyColumnsPrint(const unsigned n, const unsigned m) {
    if (m == 0) {
        return std::string("Columns number cannot be zero.");
    } else {
        std::cout << "Arrange " << n << " short lines of text in " << m << " columns." << std::endl;
        const unsigned short_column_lines = n / m;
        const unsigned long_column_lines = std::ceil(double(n) / double(m));
        const unsigned num_long_columns = n % m;
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
}

#ifdef WANT_TERMINAL_APP
int main(int argc, char **argv) {
    std::cout << PrettyColumnsPrint(37, 5) << std::endl;
}
#endif

SIMPLE_TEST(PrettyColumnsPrint, PrettyColumnsPrint_37_5, std::string(
                "line 1\tline 9\tline 17\tline 24\tline 31\t\n"
                "line 2\tline 10\tline 18\tline 25\tline 32\t\n"
                "line 3\tline 11\tline 19\tline 26\tline 33\t\n"
                "line 4\tline 12\tline 20\tline 27\tline 34\t\n"
                "line 5\tline 13\tline 21\tline 28\tline 35\t\n"
                "line 6\tline 14\tline 22\tline 29\tline 36\t\n"
                "line 7\tline 15\tline 23\tline 30\tline 37\t\n"
                "line 8\tline 16\t\n"), 37, 5);

SIMPLE_TEST(PrettyColumnsPrint, PrettyColumnsPrint_10_5, std::string(
                "line 1\tline 3\tline 5\tline 7\tline 9\t\n"
                "line 2\tline 4\tline 6\tline 8\tline 10\t\n"), 10, 5);
