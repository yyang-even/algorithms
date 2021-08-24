#pragma once


struct Complex {
    int real = 0;
    int imag = 0;

    explicit constexpr Complex(const std::string_view num) {
        sscanf(num.data(), "%d+%di", &real, &imag);
    }

    constexpr Complex(const int r, const int i): real(r), imag(i) {
    }
};


static inline Complex operator*(const Complex &one, const Complex &another) {
    return {one.real *another.real - one.imag * another.imag,
            one.real *another.imag + one.imag * another.real};
}


static inline auto ToStr(const Complex &c) {
    return std::to_string(c.real) + '+' + std::to_string(c.imag) + 'i';
}
