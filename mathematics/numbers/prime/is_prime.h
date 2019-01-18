#pragma once

INT_BOOL IsPrimeOptimizedSchoolMethod(const unsigned n) {
    if (n <= 1) {
        return false;
    }
    if (n <= 3) {
        return true;
    }

    if (n % 2 == 0 or n % 3 == 0) {
        return false;
    }

    for (unsigned i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }

    return true;
}
