#pragma once

#include "number_convertion.h"


static inline auto ToDecimal(const std::string &number, const int base,
                             const std::function<int(const char)> to_decimal) {
    int power_of_base = 1;
    int decimal_result = 0;
    for (auto r_iter = number.crbegin(); r_iter != number.crend(); ++r_iter, power_of_base *= base) {
        decimal_result += to_decimal(*r_iter) * power_of_base;
    }

    return decimal_result;
}
