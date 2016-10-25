#include "common_header.h"

unsigned gcd(unsigned m, unsigned n);

class LargeInteger {
    //Number are stored in reverse digit order
    std::vector<unsigned char> m_nums;
    friend std::ostream &operator<<(std::ostream &os, const LargeInteger &num);

public:
    explicit LargeInteger(const std::string &s_num);
    LargeInteger() = default;
    LargeInteger(const LargeInteger &copy) = default;
    LargeInteger(LargeInteger &&copy) = default;
    LargeInteger &operator=(const LargeInteger &) = default;

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
    LargeInteger operator*(const unsigned char multiplicand) const;
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
