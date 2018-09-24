#include "common_header.h"

#include <unistd.h>

/** Strong Password Suggester Program
 *
 * @reference   https://www.geeksforgeeks.org/strong-password-suggester-program/
 *
 * Given a password entered by the user, check its strength and suggest some password if it is not strong.
 * Criteria for strong password is as follows:
 * A password is strong if it has:
 * 1. At least 8 characters.
 * 2. At least one special char.
 * 3. At least one number.
 * 4. At least one upper and one lower case char.
 */
static const std::string SPECIALS {"@#$_()!"};

struct PasswordCriteria {
    bool lower_case = false;
    bool upper_case = false;
    bool digit = false;
    bool special = false;

    static const std::string::size_type REQUIRED_PASSWORD_LENGTH = 8;

    auto is_strong_password() const {
        return lower_case and upper_case and digit and special;
    }

    static auto is_lower_case(const char c) {
        return c >= LOWERCASE_CHARS.front() and c <= LOWERCASE_CHARS.back();
    }
    static auto is_upper_case(const char c) {
        return c >= UPPERCASE_CHARS.front() and c <= UPPERCASE_CHARS.back();
    }
    static auto is_number(const char c) {
        return c >= DIGIT_CHARS.front() and c <= DIGIT_CHARS.back();
    }
};
auto CheckPassword(const std::string &password) {
    PasswordCriteria criteria;
    for (const auto c : password) {
        if (PasswordCriteria::is_lower_case(c)) {
            criteria.lower_case = true;
        } else if (PasswordCriteria::is_upper_case(c)) {
            criteria.upper_case = true;
        } else if (PasswordCriteria::is_number(c)) {
            criteria.digit = true;
        } else {
            criteria.special = true;
        }
    }

    return criteria;
}
auto RandomChar(const std::string &chars) {
    return chars[Random_Number<std::string::size_type>(0ul, chars.size() - 1ul)];
}
void randomInsertIfNot(const bool criteria, const std::string &char_set, std::string &password) {
    if (not criteria) {
        password.insert(Random_Number<std::string::size_type>(0ul, password.size() - 1ul), 1,
                        RandomChar(char_set));
    }
}
auto FixPassword(const PasswordCriteria &criteria, std::string &password) {
    randomInsertIfNot(criteria.lower_case, LOWERCASE_CHARS, password);
    randomInsertIfNot(criteria.upper_case, UPPERCASE_CHARS, password);
    randomInsertIfNot(criteria.digit, DIGIT_CHARS, password);
    randomInsertIfNot(criteria.special, SPECIALS, password);

    for (auto i = password.size(); i < PasswordCriteria::REQUIRED_PASSWORD_LENGTH; ++i) {
        randomInsertIfNot(false, LOWERCASE_CHARS, password);
    }
}
auto StrongPasswordSuggester(std::string password) {
    const auto criteria = CheckPassword(password);
    FixPassword(criteria, password);
    return password;
}


const std::string VALID_PASSWORD = "Rakesh@1995kumar";
const std::string INVALID_PASSWORD = "keshav123";

SIMPLE_BENCHMARK(StrongPasswordSuggester, INVALID_PASSWORD);
SIMPLE_BENCHMARK(StrongPasswordSuggester, VALID_PASSWORD);

bool testStrongPasswordSuggester(const std::string &password) {
    return CheckPassword(StrongPasswordSuggester(password)).is_strong_password();
}

SIMPLE_TEST(testStrongPasswordSuggester, TestValid, true, VALID_PASSWORD);
SIMPLE_TEST(testStrongPasswordSuggester, TestInvalid, true, INVALID_PASSWORD);
SIMPLE_TEST(testStrongPasswordSuggester, TestShort, true, "aB7@");


#if defined(WANT_TERMINAL_APP) && defined(__linux__)
int main(int argc, char **argv) {
    const auto *passwd = getpass("password:   ");
    const auto new_password = StrongPasswordSuggester({passwd});
    std::cout << "Suggested Strong Password: " << new_password << std::endl;

    return EXIT_SUCCESS;
}
#endif
