#include "common_header.h"


namespace {

/** Student Attendance Record
 *
 * @reference   Student Attendance Record I
 *              https://leetcode.com/problems/student-attendance-record-i/
 *
 * You are given a string s representing an attendance record for a student where each
 * character signifies whether the student was absent, late, or present on that day.
 * The record only contains the following three characters:
 *  'A': Absent.
 *  'L': Late.
 *  'P': Present.
 * The student is eligible for an attendance award if they meet both of the following
 * criteria:
 *  The student was absent ('A') for strictly fewer than 2 days total.
 *  The student was never late ('L') for 3 or more consecutive days.
 * Return true if the student is eligible for an attendance award, or false otherwise.
 */


/**
 * @reference   Student Attendance Record II
 *              https://leetcode.com/problems/student-attendance-record-ii/
 *
 * An attendance record for a student can be represented as a string where each character
 * signifies whether the student was absent, late, or present on that day. The record
 * only contains the following three characters:
 *  'A': Absent.
 *  'L': Late.
 *  'P': Present.
 * Any student is eligible for an attendance award if they meet both of the following
 * criteria:
 *  The student was absent ('A') for strictly fewer than 2 days total.
 *  The student was never late ('L') for 3 or more consecutive days.
 * Given an integer n, return the number of possible attendance records of length n that
 * make a student eligible for an attendance award. The answer may be very large, so
 * return it modulo 10^9 + 7.
 */
constexpr auto StudentAttendanceRecord(const int n) {
    if (n == 1) {
        return 3;
    }

    int A[n] = {1, 2, 4};
    int L[n] = {1, 3};
    int P[n] = {1};
    constexpr auto M = LARGE_PRIME;

    for (int i = 1; i < n; i++) {
        A[i - 1] %= M;
        P[i - 1] %= M;
        L[i - 1] %= M;

        P[i] = ((A[i - 1] + P[i - 1]) % M + L[i - 1]) % M;

        if (i > 1) {
            L[i] = ((A[i - 1] + P[i - 1]) % M + (A[i - 2] + P[i - 2]) % M) % M;
        }

        if (i > 2) {
            A[i] = ((A[i - 1] + A[i - 2]) % M + A[i - 3]) % M;
        }
    }

    return ((A[n - 1] % M + P[n - 1] % M) % M + L[n - 1] % M) % M;
}

}//namespace


THE_BENCHMARK(StudentAttendanceRecord, 10101);

SIMPLE_TEST(StudentAttendanceRecord, TestSAMPLE1, 3, 1);
SIMPLE_TEST(StudentAttendanceRecord, TestSAMPLE2, 8, 2);
SIMPLE_TEST(StudentAttendanceRecord, TestSAMPLE3, 183236316, 10101);
