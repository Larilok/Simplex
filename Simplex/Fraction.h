#pragma once

#include <vector>
#include "Bignum.h"

class Fraction {
private:
    Bignum numerator;
    Bignum denominator;
    bool isPositive;
public:
    static Fraction abs(const Fraction& num);
    const Bignum& getNumerator() const;
    const Bignum& getDenominator() const;
    Bignum euclideanAlgorithm(Bignum a, Bignum b);
    bool getIsPositive() const;

    void setIsPositive(bool isPositive);

    Fraction();
    Fraction(Bignum num, Bignum denom);
    Fraction operator-();
    Fraction& operator++();
    const Fraction operator++(int);
    Fraction& operator--();
    const Fraction operator--(int);
    bool operator==(const Fraction& frac) const;
    bool operator!=(const Fraction& frac) const;
    explicit operator bool() const;
    Fraction operator+(Fraction& frac);
    Fraction operator-(Fraction& frac);
    Fraction operator*(const Fraction& frac);
    Fraction operator/(Fraction& frac);
    Fraction operator-=(Fraction& frac);
    bool operator>(const Fraction& num);
    bool operator<( Fraction& num);
    friend std::ostream& operator<<(std::ostream& output, const Fraction& frac);
};


