#include "common_header.h"

#include "numbers.h"

LargeInteger::LargeInteger(const std::string &s_num) {
    m_nums.reserve(s_num.size());
    //Number are stored in reverse digit order
    for (auto c_digit = s_num.rbegin(); c_digit != s_num.rend(); ++c_digit) {
        if (*c_digit >= '0' and * c_digit <= '9') {
            m_nums.emplace_back(*c_digit - '0');
        } else {
            m_nums.clear();
        }
    }
}

LargeInteger LargeInteger::operator+(const LargeInteger &addend) const {
    const LargeInteger *larger = nullptr;
    const LargeInteger *smaller = nullptr;
    if (m_nums.size() < addend.m_nums.size()) {
        larger = &addend;
        smaller = this;
    } else {
        larger = this;
        smaller = &addend;
    }

    LargeInteger result(*larger);

    if (smaller->isZero()) {
        return result;
    }

    unsigned char carry = 0;
    std::vector<unsigned char>::size_type i = 0;
    for (; i < smaller->m_nums.size(); ++i) {
        addDigits(result.m_nums[i], smaller->m_nums[i], carry);
    }
    while (carry) {
        if (i == result.m_nums.size()) {
            result.m_nums.emplace_back(carry);
            break;
        } else {
            addDigits(result.m_nums[i], 0, carry);
        }
        ++i;
    }

    return result;
}

void LargeInteger::addDigits(unsigned char &add_to, const unsigned char addend,
                             unsigned char &carry) {
    add_to += (addend + carry);
    if (add_to >= 10) {
        add_to -= 10;
        carry = 1;
    } else {
        carry = 0;
    }
}

std::ostream &operator<<(std::ostream &os, const LargeInteger &num) {
    std::string str_num;
    str_num.reserve(num.m_nums.size());
    for (auto i_digit = num.m_nums.rbegin(); i_digit != num.m_nums.rend(); ++i_digit) {
        str_num.push_back(*i_digit + '0');
    }
    os << str_num;
    return os;
}

LargeInteger LargeInteger::operator*(const LargeInteger &multiplicand) const {
    const LargeInteger *larger = nullptr;
    const LargeInteger *smaller = nullptr;
    if (m_nums.size() < multiplicand.m_nums.size()) {
        larger = &multiplicand;
        smaller = this;
    } else {
        larger = this;
        smaller = &multiplicand;
    }

    LargeInteger result;

    for (std::vector<unsigned char>::size_type i = 0; i < smaller->m_nums.size(); ++i) {
        auto temp = *larger * smaller->m_nums[i];
        temp.m_nums.insert(temp.m_nums.begin(), i, 0);
        result = result + temp;
    }

    return result;
}

LargeInteger LargeInteger::operator*(const unsigned char multiplicand) const {
    if (multiplicand > 9) {
        return *this * LargeInteger(std::to_string(multiplicand));
    }

    if (multiplicand == 1) {
        return *this;
    }
    LargeInteger result;
    if (multiplicand == 0) {
        return result;
    }

    unsigned char temp = 0;
    unsigned char carry = 0;

    for (auto digit : m_nums) {
        temp = digit * multiplicand + carry;

        if (temp > 10) {
            carry = temp / 10;
            temp %= 10;
        } else {
            carry = 0;
        }
        result.m_nums.emplace_back(temp);
    }
    if (carry) {
        result.m_nums.emplace_back(carry);
    }

    return result;
}

//Test cases
LargeInteger AddLargeIntegers(const LargeInteger &a, const LargeInteger &b) {
    return a + b;
}

LargeInteger MultiplyLargeIntegers(const LargeInteger &a, const LargeInteger &b) {
    return a * b;
}


SIMPLE_BENCHMARK(AddLargeIntegers, LargeInteger("0"), LargeInteger("0"));
SIMPLE_BENCHMARK(AddLargeIntegers, LargeInteger("0"), LargeInteger("10000000"));

SIMPLE_TEST(AddLargeIntegers, TestSAMPLE1, LargeInteger("0"), LargeInteger("0"), LargeInteger("0"));
SIMPLE_TEST(AddLargeIntegers, TestSAMPLE2, LargeInteger("17"), LargeInteger("8"),
            LargeInteger("9"));
SIMPLE_TEST(AddLargeIntegers, TestSAMPLE3, LargeInteger("210"), LargeInteger("10"),
            LargeInteger("200"));
SIMPLE_TEST(AddLargeIntegers, TestSAMPLE4, LargeInteger("1000000000000000"),
            LargeInteger("999999999999999"), LargeInteger("1"));

SIMPLE_BENCHMARK(MultiplyLargeIntegers, LargeInteger("0"), LargeInteger("0"));
SIMPLE_BENCHMARK(MultiplyLargeIntegers, LargeInteger("1"), LargeInteger("10000000"));
SIMPLE_BENCHMARK(MultiplyLargeIntegers, LargeInteger("18"), LargeInteger("10000000"));

SIMPLE_TEST(MultiplyLargeIntegers, TestSAMPLE1, LargeInteger("0"), LargeInteger("0"),
            LargeInteger("0"));
SIMPLE_TEST(MultiplyLargeIntegers, TestSAMPLE2, LargeInteger("72"), LargeInteger("8"),
            LargeInteger("9"));
SIMPLE_TEST(MultiplyLargeIntegers, TestSAMPLE3, LargeInteger("2000"), LargeInteger("10"),
            LargeInteger("200"));
SIMPLE_TEST(MultiplyLargeIntegers, TestSAMPLE4, LargeInteger("999999999999999"),
            LargeInteger("999999999999999"), LargeInteger("1"));
SIMPLE_TEST(MultiplyLargeIntegers, TestSAMPLE5, LargeInteger("216"), LargeInteger("18"),
            LargeInteger("12"));
