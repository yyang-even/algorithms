#include "common_header.h"


namespace {

using ArrayType = std::vector<std::string_view>;

/** Unique Email Addresses
 *
 * @reference   https://leetcode.com/problems/unique-email-addresses/
 *
 * Every valid email consists of a local name and a domain name, separated by the '@'
 * sign. Besides lowercase letters, the email may contain one or more '.' or '+'.
 *  For example, in "alice@leetcode.com", "alice" is the local name, and "leetcode.com"
 *      is the domain name.
 * If you add periods '.' between some characters in the local name part of an email
 * address, mail sent there will be forwarded to the same address without dots in the
 * local name. Note that this rule does not apply to domain names.
 *  For example, "alice.z@leetcode.com" and "alicez@leetcode.com" forward to the same
 *      email address.
 * If you add a plus '+' in the local name, everything after the first plus sign will be
 * ignored. This allows certain emails to be filtered. Note that this rule does not apply
 * to domain names.
 *  For example, "m.y+name@email.com" will be forwarded to "my@email.com".
 * It is possible to use both of these rules at the same time. Given an array of strings
 * emails where we send one email to each email[i], return the number of different
 * addresses that actually receive mails.
 */
auto UniqueEmailAddresses(const ArrayType &emails) {
    std::unordered_set<std::string> unique;
    for (const auto an_email : emails) {
        std::string clean_email;
        for (const auto c : an_email) {
            if (c == '+' or c == '@') {
                break;
            }
            if (c != '.') {
                clean_email.push_back(c);
            }
        }

        clean_email.push_back('@');
        for (int i = an_email.size() - 1; i >= 0 and an_email[i] != '@'; --i) {
            clean_email.push_back(an_email[i]);
        }

        unique.insert(clean_email);
    }

    return unique.size();
}

}//namespace


const ArrayType SAMPLE1 = {
    "test.email+alex@leetcode.com",
    "test.e.mail+bob.cathy@leetcode.com",
    "testemail+david@lee.tcode.com"
};

const ArrayType SAMPLE2 = {
    "a@leetcode.com",
    "b@leetcode.com",
    "c@leetcode.com"
};

THE_BENCHMARK(UniqueEmailAddresses, SAMPLE1);

SIMPLE_TEST(UniqueEmailAddresses, TestSAMPLE1, 2, SAMPLE1);
SIMPLE_TEST(UniqueEmailAddresses, TestSAMPLE2, 3, SAMPLE2);
