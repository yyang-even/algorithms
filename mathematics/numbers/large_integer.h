#pragma once

#include "common_header.h"


class LargeInteger {

    using NumData = std::vector<unsigned char>;

    //Number are stored in reverse digit order
    NumData m_nums;

    static constexpr inline NumData::size_type BLOCK_SIZE = 8;

    friend std::ostream &operator<<(std::ostream &os, const LargeInteger &num);

public:

    explicit LargeInteger(const std::string_view s_num) {
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

    LargeInteger(const LargeInteger &copy, const unsigned block_index) {
        const auto lower_bound = block_index * BLOCK_SIZE;
        if (lower_bound < copy.m_nums.size()) {
            const auto size_to_copy = std::min(copy.m_nums.size() - lower_bound, BLOCK_SIZE);
            m_nums.resize(size_to_copy);
            std::copy_n(copy.m_nums.begin() + lower_bound, size_to_copy, m_nums.begin());
        }
    }

    LargeInteger() = default;
    LargeInteger(const LargeInteger &copy) = default;
    LargeInteger(LargeInteger &&copy) = default;
    LargeInteger &operator=(const LargeInteger &) = default;


    std::string ToString() const {
        std::string str_num;
        str_num.reserve(m_nums.size());
        for (auto i_digit = m_nums.rbegin(); i_digit != m_nums.rend(); ++i_digit) {
            str_num.push_back(*i_digit + '0');
        }
        return str_num;
    }


    unsigned ToInt() const {
        if (isZero()) {
            return 0;
        }
        return std::stoi(ToString());
    }


    bool operator==(const LargeInteger &compare_to) const {
        if (isZero() and compare_to.isZero()) {
            return true;
        }
        return m_nums == compare_to.m_nums;
    }


    bool operator!=(const LargeInteger &compare_to) const {
        return not(*this == compare_to);
    }


    LargeInteger operator+(const LargeInteger &addend) const {
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


    LargeInteger operator*(const LargeInteger &multiplicand) const {
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

    LargeInteger operator*(const unsigned multiplicand) const {
        if (multiplicand > (std::numeric_limits<unsigned>::max() >> 4)) {
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

private:

    static constexpr inline void
    addDigits(unsigned char &add_to, const unsigned char addend,
              unsigned char &carry) {
        add_to += (addend + carry);
        if (add_to >= 10) {
            add_to -= 10;
            carry = 1;
        } else {
            carry = 0;
        }
    }


    bool isZero() const {
        return m_nums.empty() or (m_nums.size() == 1 and m_nums[0] == 0);
    }


    bool isOne() const {
        return m_nums.size() == 1 and m_nums[0] == 1;
    }
};


inline std::ostream &operator<<(std::ostream &os, const LargeInteger &num) {
    os << num.ToString();
    return os;
}
