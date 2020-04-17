#include "Fraction.h"


Fraction::Fraction() {}

Fraction::Fraction(Bignum num, Bignum denom) {
    if (denom == Bignum("0")) throw std::exception("Tried dividing by zero");
    Bignum GCD = euclideanAlgorithm(num, denom);
    Bignum absGCD = GCD;
    absGCD.isPositive = true;
    if (absGCD > Bignum("1")) {
        num = num / GCD;
        denom = denom / GCD;
    }
    numerator = num;
    denominator = denom;
    if (numerator.isPositive != denominator.isPositive) isPositive = false;
    else isPositive = true;
}

Fraction Fraction::operator-() {
    isPositive = !isPositive;
    return *this;
}

Bignum Fraction::euclideanAlgorithm(Bignum a, Bignum b) {
    Bignum c;
    while (b) {
        c = a % b;
        a = b;
        b = c;
    }
    return a;
}

std::ostream& operator<<(std::ostream& output, const Fraction& frac) {
    if (!frac.isPositive) output << "- ";
    for (long long int i = frac.numerator.number.size() - 1; i >= 0; --i) {
        output << frac.numerator.number[i];
    }
    output << "/";
    for (long long int i = frac.denominator.number.size() - 1; i >= 0; --i) {
        output << frac.denominator.number[i];
    }
    return output;
}

Fraction& Fraction::operator++() {
    if (isPositive) ++numerator;
    else --numerator;
    return *this;
}
const Fraction Fraction::operator++(int) {
    Fraction copy(*this);
    ++copy;
    return copy;
}

Fraction& Fraction::operator--() {
    if (isPositive) --numerator;
    else ++numerator;
    return *this;
}

const Fraction Fraction::operator--(int) {
    Fraction copy(*this);
    --copy;
    return copy;
}

bool Fraction::operator==(const Fraction& frac) const {
    if (numerator == frac.numerator && denominator == frac.denominator && isPositive == frac.isPositive) return true;
    return false;
}

bool Fraction::operator!=(const Fraction& frac) const {
    return !(*this == frac);
}

Fraction::operator bool() const {
    if (numerator != Bignum("0") && denominator != Bignum("0")) return true;
    return false;
}

Fraction Fraction::operator+(Fraction& frac) {
    if (this->numerator == Bignum("0")) return Fraction(frac.numerator, frac.denominator);
    if (frac.numerator == Bignum("0")) return (*this);
    Bignum thisNum;
    Bignum thisDenom;
    Bignum fracNum;
    if (denominator != frac.denominator) {
        thisNum = this->numerator * frac.denominator;
        thisDenom = this->denominator * frac.denominator;
        fracNum = frac.numerator * this->denominator;
    }
    else {
        thisNum = this->numerator;
        thisDenom = this->denominator;
        fracNum = frac.numerator;
    }
    Bignum numer;
    numer = thisNum + fracNum;
    if (!numer.isPositive && !this->isPositive) numer.isPositive = !numer.isPositive;
    return Fraction(numer, thisDenom);
}

Fraction Fraction::operator-(Fraction& frac) {
    Bignum thisNum;
    Bignum thisDenom;
    Bignum fracNum;
    if (denominator != frac.denominator) {
        thisNum = this->numerator * frac.denominator;
        thisDenom = this->denominator * frac.denominator;
        fracNum = frac.numerator * this->denominator;
    }
    else {
        thisNum = this->numerator;
        thisDenom = this->denominator;
        fracNum = frac.numerator;
    }
    Bignum numer;
    numer = thisNum - fracNum;
    if (!numer.isPositive && !this->isPositive) numer.isPositive = !numer.isPositive;
    return Fraction(numer, thisDenom);
}

Fraction Fraction::operator*(const Fraction& frac) {
    Bignum numerator = this->numerator * frac.numerator;
    Bignum denominator = this->denominator * frac.denominator;
    Fraction result(numerator, denominator);
    if (isPositive != frac.isPositive) result.isPositive = false;
    else result.isPositive = true;
    return result;
}

Fraction Fraction::operator/(Fraction& frac) {
    Bignum numerator = this->numerator * frac.denominator;
    Bignum denominator = this->denominator * frac.numerator;
    Fraction result(numerator, denominator);
    if (isPositive != frac.isPositive) result.isPositive = false;
    else result.isPositive = true;
    return result;
}

Fraction Fraction::operator+=(Fraction& frac)
{
	return *this + frac;
}

Fraction Fraction::operator-=(Fraction& frac)
{
    return *this - frac;
}

bool Fraction::operator>(const Fraction& num)
{
    if (this->isPositive == num.isPositive) {
        if (this->numerator * num.denominator > this->denominator * num.numerator) return true;
        else return false;
    }
    else if (this->isPositive && !num.isPositive) {
        return true;
    }
    return false;//if this is negative && num is positive
}

bool Fraction::operator<(Fraction& num)
{
    return num > *this;
}

bool Fraction::getIsPositive() const {
    return isPositive;
}

void Fraction::setIsPositive(bool isPositive) {
    Fraction::isPositive = isPositive;
}

Fraction Fraction::abs(const Fraction& num)
{
    Fraction copy(num);
    copy.isPositive = true;
    return copy;
}

const Bignum& Fraction::getNumerator() const {
    return numerator;
}

const Bignum& Fraction::getDenominator() const {
    return denominator;
}