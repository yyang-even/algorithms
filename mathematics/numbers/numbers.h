#pragma once

#include "common_header.h"

class LargeInteger {
    typedef std::vector<unsigned char> NumData;
    //Number are stored in reverse digit order
    NumData m_nums;
    friend std::ostream &operator<<(std::ostream &os, const LargeInteger &num);
    static const NumData::size_type BLOCK_SIZE = 8;
public:
    explicit LargeInteger(const std::string &s_num);
    LargeInteger(const LargeInteger &copy, const unsigned block_index);
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
    LargeInteger operator+(const LargeInteger &addend) const;
    LargeInteger operator*(const LargeInteger &multiplicand) const;
    LargeInteger operator*(const unsigned multiplicand) const;
private:
    static void addDigits(unsigned char &add_to, const unsigned char addend, unsigned char &carry);
    bool isZero() const {
        return m_nums.empty() or (m_nums.size() == 1 and m_nums[0] == 0);
    }
    bool isOne() const {
        return m_nums.size() == 1 and m_nums[0] == 1;
    }
};

std::ostream &operator<<(std::ostream &os, const LargeInteger &num);
