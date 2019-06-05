#include "common_header.h"

#include <fstream>

namespace {

/** Implement your own tail (Read last n lines of a huge file)
 *
 * @reference   https://www.geeksforgeeks.org/implement-your-own-tail-read-last-n-lines-of-a-huge-file/
 *
 * Given a huge file having dynamic data, write a program to read last n lines
 * from the file at any point without reading the entire file. The problem is
 * similar to tail command in linux which displays the last few lines of a file.
 * It is mostly used for viewing log file updates as these updates are appended
 * to the log files.
 */
std::string tail(std::ifstream &file, unsigned N) {
    std::ostringstream output;

    if (file) {
        if (file.seekg(0, std::ios_base::end)) {

            while (file.seekg(-1, std::ios_base::cur)) {
                if (file.peek() == '\n' and not N--) {
                    file.get();
                    break;
                }
            }

            output << file.rdbuf();
        }
    }

    return output.str();
}

INT_BOOL TestTail() {
    const std::string HEAD = "1\n2\n3\n4\n5\n";
    const std::string TAIL = "6\n7\n8\n9\n10\n";
    const auto file_str = HEAD + TAIL;
    const std::string filename = "tail_test.txt";
    {
        std::ofstream file(filename);
        file << file_str;
    }

    std::ifstream file(filename);
    const auto tail_str = tail(file, 5);

    return TAIL == tail_str;
}

}//namespace

SIMPLE_BENCHMARK(TestTail);

SIMPLE_TEST0(TestTail, TestSAMPLE1, TRUE);
