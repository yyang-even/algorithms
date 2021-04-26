#include "common_header.h"

#include "counting_sort.h"


namespace {

using ArrayType = std::vector<std::string>;

/**
 * @reference   How to sort an array of dates in C/C++?
 *              https://www.geeksforgeeks.org/how-to-sort-an-array-of-dates-in-cc/
 */
struct Date {
    int day = 0;
    int month = 0;
    int year = 0;
};

inline auto &operator<<(std::ostream &out, const Date &date) {
    return out << '(' << date.day << ", " << date.month << ", " << date.year << ')';
}

inline bool operator==(const Date &lhs, const Date &rhs) {
    return lhs.year == rhs.year and lhs.month == rhs.month and lhs.day == rhs.day;
}

auto SortDates(std::vector<Date> dates) {
    std::sort(dates.begin(), dates.end(), [](const auto & lhs, const auto & rhs) {
        if (lhs.year == rhs.year) {
            if (lhs.month == rhs.month) {
                return lhs.day < rhs.day;
            } else {
                return lhs.month < rhs.month;
            }
        } else {
            return lhs.year < rhs.year;
        }
    });

    return dates;
}


/** Sort an array of string of dates in ascending order
 *
 * @reference   https://www.geeksforgeeks.org/sort-an-array-of-string-of-dates-in-ascending-order/
 *
 * Given an array of strings dates[], the task is to sort these dates in ascending order.
 * Note: Each date is of the form dd mmm yyyy where:
 *     Domain of dd is [0-31].
 *     Domain of mmm is [Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec].
 *     And, yyyy is a four digit integer.
 */
auto ToInt(const std::string &date) {
    assert(date.length() == 11);

    static const std::unordered_map<std::string_view, int> MonthsMap = {
        {"Jan", 1},
        {"Feb", 2},
        {"Mar", 3},
        {"Apr", 4},
        {"May", 5},
        {"Jun", 6},
        {"Jul", 7},
        {"Aug", 8},
        {"Sep", 9},
        {"Oct", 10},
        {"Nov", 11},
        {"Dec", 12}
    };

    const auto day = std::stoi(date.substr(0, 2));
    const auto month = MonthsMap.at(date.substr(3, 3));
    const auto year = std::stoi(date.substr(7, 4));

    return year * 10000 + month * 100 + day;
}

auto SortDateStrings_Int(const ArrayType &dates) {
    std::vector<std::pair<int, ArrayType::const_iterator>> sort_me;
    for (auto iter = dates.cbegin(); iter != dates.cend(); ++iter) {
        sort_me.emplace_back(ToInt(*iter), iter);
    }

    std::sort(sort_me.begin(), sort_me.end(), [](const auto & lhs, const auto & rhs) {
        return lhs.first < rhs.first;
    });

    ArrayType outputs(dates.size());
    std::transform(sort_me.cbegin(), sort_me.cend(), outputs.begin(),
    [](const auto & pair) {
        return *(pair.second);
    });

    return outputs;
}


/** How to efficiently sort a big list dates in 20’s
 *
 * @reference   https://www.geeksforgeeks.org/how-to-efficiently-sort-a-big-list-dates-in-20s/
 */
auto SortDates_RadixSort(std::vector<Date> dates) {
    dates = CountingSort_STL(dates, [](const auto & date) {
        return date.day;
    });
    dates = CountingSort_STL(dates, [](const auto & date) {
        return date.month;
    });

    return CountingSort_STL(dates, [](const auto & date) {
        return date.year;
    });
}

}//namespace


const std::vector<Date> SAMPLE1 = {{20,  1, 2014}, {25,  3, 2010}, { 3, 12, 1676},
    {18, 11, 1982}, {19,  4, 2015}, { 9,  7, 2015}
};
const std::vector<Date> EXPECTED1 = {{ 3, 12, 1676}, {18, 11, 1982}, {25,  3, 2010},
    {20,  1, 2014}, {19,  4, 2015}, { 9,  7, 2015}
};
const std::vector<Date> SAMPLE2 = {{20,  1, 2014}, {25,  3, 2010}, { 3, 12, 2000},
    {18, 11, 2001}, {19,  4, 2015}, { 9,  7, 2005}
};
const std::vector<Date> EXPECTED2 = {{ 3, 12, 2000}, {18, 11, 2001}, { 9,  7, 2005},
    {25,  3, 2010}, {20,  1, 2014}, {19,  4, 2015}
};


SIMPLE_BENCHMARK(SortDates, Sample1, SAMPLE1);

SIMPLE_TEST(SortDates, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(SortDates, TestSAMPLE2, EXPECTED2, SAMPLE2);


const ArrayType SAMPLE3 = { "24 Jul 2017", "25 Jul 2017", "11 Jun 1996",
                            "01 Jan 2019", "12 Aug 2005", "01 Jan 1997"
                          };
const ArrayType EXPECTED3 = {"11 Jun 1996", "01 Jan 1997", "12 Aug 2005",
                             "24 Jul 2017", "25 Jul 2017", "01 Jan 2019"
                            };


SIMPLE_BENCHMARK(SortDateStrings_Int, Sample1, SAMPLE3);

SIMPLE_TEST(SortDateStrings_Int, TestSAMPLE3, EXPECTED3, SAMPLE3);


SIMPLE_BENCHMARK(SortDates_RadixSort, Sample1, SAMPLE1);

SIMPLE_TEST(SortDates_RadixSort, TestSAMPLE1, EXPECTED1, SAMPLE1);
SIMPLE_TEST(SortDates_RadixSort, TestSAMPLE2, EXPECTED2, SAMPLE2);
