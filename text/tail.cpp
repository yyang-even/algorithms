#include "common_header.h"

#include <fstream>


namespace {

/** Implement your own tail (Read last n lines of a huge file)
 *
 * @reference   https://www.geeksforgeeks.org/implement-your-own-tail-read-last-n-lines-of-a-huge-file/
 *
 * Given a huge file having dynamic data, write a program to read last n lines from the
 * file at any point without reading the entire file. The problem is similar to tail
 * command in linux which displays the last few lines of a file. It is mostly used for
 * viewing log file updates as these updates are appended to the log files.
 *
 * @reference   Gayle Laakmann McDowell. Cracking the Coding Interview, Fifth Edition.
 *              Questions 13.1.
 */
std::string tail(std::ifstream &file, unsigned N) {
    assert(N);

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

auto TestTail() {
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


/**
 * @reference   Program to print last 10 lines
 *              https://www.geeksforgeeks.org/print-last-10-lines-of-a-given-file/
 *
 * Given some text lines in one string, each line is separated by '\n' character. Print
 * the last ten lines. If number of lines is less than 10, then print all lines.
 */
auto TailString_Rfind(const std::string &lines, unsigned K) {
    assert(K);

    auto start_position = std::string::npos;
    while (K--) {
        start_position = lines.rfind('\n', start_position - 1);

        if (start_position == std::string::npos) {
            break;
        }
    }

    if (start_position == std::string::npos) {
        return lines;
    } else {
        return lines.substr(start_position + 1);
    }
}


/**
 * @reference   Program to print last N lines | Set-2
 *              https://www.geeksforgeeks.org/program-to-print-last-n-lines-set-2/
 */
auto TailString_Strtok(std::string lines, const unsigned K) {
    assert(K);

    std::queue<std::string> line_queue;
    for (auto *token = strtok(lines.data(), "\n");
         token; token = strtok(nullptr, "\n")) {
        if (line_queue.size() >= K) {
            line_queue.pop();
        }

        line_queue.push(token);
    }

    if (line_queue.empty()) {
        return lines;
    }

    auto result = line_queue.front();
    for (line_queue.pop(); not line_queue.empty(); line_queue.pop()) {
        result.push_back('\n');
        result.append(line_queue.front());
    }

    return result;
}

}//namespace


SIMPLE_BENCHMARK0(TestTail);

SIMPLE_TEST0(TestTail, TestSAMPLE1, true);


const std::string SAMPLE1 = "str1\nstr2\nstr3\nstr4\nstr5\nstr6\nstr7";


THE_BENCHMARK(TailString_Rfind, SAMPLE1, 5);

SIMPLE_TEST(TailString_Rfind, TestSAMPLE0, "", "", 10);
SIMPLE_TEST(TailString_Rfind, TestSAMPLE1, "str7", SAMPLE1, 1);
SIMPLE_TEST(TailString_Rfind, TestSAMPLE2, SAMPLE1, SAMPLE1, 10);


THE_BENCHMARK(TailString_Strtok, SAMPLE1, 5);

SIMPLE_TEST(TailString_Strtok, TestSAMPLE0, "", "", 10);
SIMPLE_TEST(TailString_Strtok, TestSAMPLE1, "str7", SAMPLE1, 1);
SIMPLE_TEST(TailString_Strtok, TestSAMPLE2, SAMPLE1, SAMPLE1, 10);
