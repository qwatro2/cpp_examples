#include "rational.h"

int Gcd(int a, int b) {
    if (b == 0) {
        return a;
    }

    return Gcd(b, a % b);
}

void Rational::Set(int64_t numer, int64_t denom) {
    if (denom == 0) {
        throw RationalDivisionByZero{};
    }

    if (numer == 0) {
        numer_ = 0;
        denom_ = 1;
        return;
    }

    auto sgn = numer * denom > 0 ? 1 : -1;

    auto int_numer = static_cast<int>(std::abs(numer));
    auto int_denom = static_cast<int>(std::abs(denom));
    auto gcd = Gcd(int_numer, int_denom);
    numer_ = sgn * (int_numer / gcd);
    denom_ = int_denom / gcd;
}
Rational::Rational() : numer_(0), denom_(1) {
}
Rational::Rational(int value) : numer_(value), denom_(1) {
}
Rational::Rational(int numer, int denom) {
    Set(numer, denom);
}
int Rational::GetNumerator() const {
    return numer_;
}
int Rational::GetDenominator() const {
    return denom_;
}
void Rational::SetNumerator(int value) {
    Set(value, denom_);
}
void Rational::SetDenominator(int value) {
    Set(numer_, value);
}
Rational& operator+=(Rational& lhs, const Rational& rhs) {
    // lhs = a / b; rhs = c / d;
    auto a = lhs.GetNumerator();
    auto b = lhs.GetDenominator();
    auto c = rhs.GetNumerator();
    auto d = rhs.GetDenominator();

    lhs.Set(static_cast<int64_t>(a * d + c * b), static_cast<int64_t>(b * d));
    return lhs;
}
Rational& operator*=(Rational& lhs, const Rational& rhs) {
    // lhs = a / b; rhs = c / d;
    auto a = lhs.GetNumerator();
    auto b = lhs.GetDenominator();
    auto c = rhs.GetNumerator();
    auto d = rhs.GetDenominator();

    lhs.Set(static_cast<int64_t>(a * c), static_cast<int64_t>(b * d));
    return lhs;
}
Rational& operator++(Rational& ratio) {
    // ratio = a / b;
    auto a = ratio.GetNumerator();
    auto b = ratio.GetDenominator();
    ratio.SetNumerator(a + b);
    return ratio;
}
Rational& operator--(Rational& ratio) {
    // ratio = a / b;
    auto a = ratio.GetNumerator();
    auto b = ratio.GetDenominator();
    ratio.SetNumerator(a - b);
    return ratio;
}
std::istream& operator>>(std::istream& is, Rational& ratio) {
    int numer = 0;
    int denom = 1;
    is >> numer;

    if (is.peek() == '/') {
        is.ignore();
        is >> denom;
    }

    ratio.Set(numer, denom);
    return is;
}
Rational operator+(const Rational& ratio) {
    return Rational(ratio.GetNumerator(), ratio.GetDenominator());
}
Rational operator-(const Rational& ratio) {
    return Rational(-ratio.GetNumerator(), ratio.GetDenominator());
}
Rational& operator-=(Rational& lhs, const Rational& rhs) {
    // lhs = a / b; rhs = c / d;
    auto a = lhs.GetNumerator();
    auto b = lhs.GetDenominator();
    auto c = rhs.GetNumerator();
    auto d = rhs.GetDenominator();

    auto new_numer = a * d - c * b;
    auto new_denom = b * d;
    auto gcd = Gcd(new_numer, new_denom);

    lhs.SetNumerator(new_numer / gcd);
    lhs.SetDenominator(new_denom / gcd);
    return lhs;
}
Rational& operator/=(Rational& lhs, const Rational& rhs) {
    // lhs = a / b; rhs = c / d;
    auto a = lhs.GetNumerator();
    auto b = lhs.GetDenominator();
    auto c = rhs.GetNumerator();
    auto d = rhs.GetDenominator();

    auto new_numer = a * d;
    auto new_denom = b * c;
    auto gcd = Gcd(new_numer, new_denom);

    lhs.SetNumerator(new_numer / gcd);
    lhs.SetDenominator(new_denom / gcd);

    return lhs;
}
Rational operator+(const Rational& lhs, const Rational& rhs) {
    // lhs = a / b; rhs = c / d;
    auto a = lhs.GetNumerator();
    auto b = lhs.GetDenominator();
    auto c = rhs.GetNumerator();
    auto d = rhs.GetDenominator();

    return Rational(a * d + b * c, b * d);
}
Rational operator-(const Rational& lhs, const Rational& rhs) {
    // lhs = a / b; rhs = c / d;
    auto a = lhs.GetNumerator();
    auto b = lhs.GetDenominator();
    auto c = rhs.GetNumerator();
    auto d = rhs.GetDenominator();

    return Rational(a * d - b * c, b * d);
}
Rational operator*(const Rational& lhs, const Rational& rhs) {
    // lhs = a / b; rhs = c / d;
    auto a = lhs.GetNumerator();
    auto b = lhs.GetDenominator();
    auto c = rhs.GetNumerator();
    auto d = rhs.GetDenominator();

    return Rational(a * c, b * d);
}
Rational operator/(const Rational& lhs, const Rational& rhs) {
    // lhs = a / b; rhs = c / d;
    auto a = lhs.GetNumerator();
    auto b = lhs.GetDenominator();
    auto c = rhs.GetNumerator();
    auto d = rhs.GetDenominator();

    return Rational(a * d, b * c);
}
Rational operator++(Rational& ratio, int) {
    // ratio = a / b;
    auto a = ratio.GetNumerator();
    auto b = ratio.GetDenominator();
    ratio.SetNumerator(a + b);
    return Rational(a, b);
}
Rational operator--(Rational& ratio, int) {
    // ratio = a / b;
    auto a = ratio.GetNumerator();
    auto b = ratio.GetDenominator();
    ratio.SetNumerator(a - b);
    return Rational(a, b);
}
bool operator<(const Rational& lhs, const Rational& rhs) {
    // lhs = a / b; rhs = c / d;
    auto a = lhs.GetNumerator();
    auto b = lhs.GetDenominator();
    auto c = rhs.GetNumerator();
    auto d = rhs.GetDenominator();

    return a * d < c * b;
}
bool operator>(const Rational& lhs, const Rational& rhs) {
    // lhs = a / b; rhs = c / d;
    auto a = lhs.GetNumerator();
    auto b = lhs.GetDenominator();
    auto c = rhs.GetNumerator();
    auto d = rhs.GetDenominator();

    return a * d > c * b;
}
bool operator<=(const Rational& lhs, const Rational& rhs) {
    // lhs = a / b; rhs = c / d;
    auto a = lhs.GetNumerator();
    auto b = lhs.GetDenominator();
    auto c = rhs.GetNumerator();
    auto d = rhs.GetDenominator();

    return a * d <= c * b;
}
bool operator>=(const Rational& lhs, const Rational& rhs) {
    // lhs = a / b; rhs = c / d;
    auto a = lhs.GetNumerator();
    auto b = lhs.GetDenominator();
    auto c = rhs.GetNumerator();
    auto d = rhs.GetDenominator();

    return a * d >= c * b;
}
bool operator==(const Rational& lhs, const Rational& rhs) {
    // lhs = a / b; rhs = c / d;
    auto a = lhs.GetNumerator();
    auto b = lhs.GetDenominator();
    auto c = rhs.GetNumerator();
    auto d = rhs.GetDenominator();

    return a * d == c * b;
}
bool operator!=(const Rational& lhs, const Rational& rhs) {
    // lhs = a / b; rhs = c / d;
    auto a = lhs.GetNumerator();
    auto b = lhs.GetDenominator();
    auto c = rhs.GetNumerator();
    auto d = rhs.GetDenominator();

    return a * d != c * b;
}
std::ostream& operator<<(std::ostream& os, const Rational& ratio) {
    os << ratio.GetNumerator();
    if (ratio.GetDenominator() != 1) {
        os << '/' << ratio.GetDenominator();
    }
    return os;
}
