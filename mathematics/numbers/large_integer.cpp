#include "common_header.h"

#include "numbers.h"

const LargeInteger::NumData::size_type LargeInteger::BLOCK_SIZE;

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

LargeInteger::LargeInteger(const LargeInteger &source, const unsigned block_index) {
    auto lower_bound = block_index * BLOCK_SIZE;
    if (lower_bound < source.m_nums.size()) {
        auto size_to_copy = std::min(source.m_nums.size() - lower_bound, BLOCK_SIZE);
        m_nums.resize(size_to_copy);
        std::copy_n(source.m_nums.begin() + lower_bound, size_to_copy, m_nums.begin());
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
    NumData::size_type i = 0;
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
    os << num.ToString();
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
    for (NumData::size_type i = 0; i <= smaller->m_nums.size() / BLOCK_SIZE; ++i) {
        auto temp = *larger * LargeInteger(*smaller, i).ToInt();
        temp.m_nums.insert(temp.m_nums.begin(), i * BLOCK_SIZE, 0);
        result = result + temp;
    }

    return result;
}

LargeInteger LargeInteger::operator*(const unsigned multiplicand) const {
    if (multiplicand > (UINT_MAX >> 4)) {
        return *this * LargeInteger(std::to_string(multiplicand));
    }

    if (multiplicand == 1) {
        return *this;
    }
    if (multiplicand == 0) {
        return LargeInteger {};
    }

    LargeInteger result(*this);
    unsigned carry = 0;
    unsigned product = 0;
    for (auto &digit : result.m_nums) {
        product = digit * multiplicand + carry;
        digit = product % 10;
        carry = product / 10;
    }
    while (carry) {
        result.m_nums.emplace_back(carry % 10);
        carry /= 10;
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
SIMPLE_TEST(MultiplyLargeIntegers, TestSAMPLE6, LargeInteger("134959936636921125"),
            LargeInteger("521694835"), LargeInteger("258695175"));
