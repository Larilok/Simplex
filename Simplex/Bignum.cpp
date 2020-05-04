#include "Bignum.h"

#include <iostream>
using namespace std;

inline Bignum::Bignum() {
    isPositive = true;
    number.push_back(0);
}

Bignum::Bignum(std::string input) {
    if (input[0] == '-') {
        isPositive = false;
        input.erase(0, 1);
    }
    else isPositive = true;
    size_t length = input.length();
    for (size_t i = 0; i < length; ++i) {
        if ((input[input.length() - 1] - 48) > 9) throw std::exception("Input not a num!");
        number.push_back(input[input.length() - 1] - 48);
        input.pop_back();
    }
}

Bignum Bignum::operator-() {
    isPositive = !isPositive;
    return *this;
}

int Bignum::getDigit(int digit) const {
    if (digit > number.size() - 1) return 0;
    return number[digit];
}

void Bignum::handlePositiveCarry() {
    for (int i = 0; i < number.size(); ++i) {
        int carry = number[i] / 10;
        number[i] %= 10;
        if (i == number.size() - 1 && carry != 0) {
            number.push_back(carry);
        }
        else if (carry != 0) {
            number[i + 1] += carry;
        }
    }
}

void Bignum::handleNegativeCarry() {
    for (int i = 0; i < number.size(); ++i) {
        if (number[i] < 0) {
            number[i] += 10;
            number[i + 1]--;
        }
    }
}

void Bignum::removeLeadingZeroes() {
    while (number.size() > 1 && number[number.size() - 1] == 0) number.pop_back();
}

bool Bignum::isZero() const {
    return number.size() == 1 && number[0] == 0;
}

Bignum Bignum::abs(const Bignum& num) {
    Bignum copy(num);
    copy.isPositive = true;
    return copy;
}

std::ostream& operator<<(std::ostream& output, const Bignum& num) {
    output << "The value is: ";
    if (!num.isPositive) output << '-';
    for (long long int i = num.number.size() - 1; i >= 0; --i) {
        output << num.number[i];
    }
    return output;
}

Bignum& Bignum::operator++() {
    if (isPositive) {
        number[0]++;
        handlePositiveCarry();
    }
    else {
        number[0]--;
        handleNegativeCarry();
        removeLeadingZeroes();
    }
    return *this;
}

const Bignum Bignum::operator++(int) {
    Bignum copy(*this);
    ++copy;
    return copy;
}

Bignum& Bignum::operator--() {
    if (isPositive) {
        number[0]--;
        handleNegativeCarry();
        removeLeadingZeroes();
    }
    else {
        number[0]++;
        handlePositiveCarry();
    }
    return *this;
}

const Bignum Bignum::operator--(int) {
    Bignum copy(*this);
    --copy;
    return copy;
}

bool Bignum::operator==(const Bignum& num) const {
    if (this->number.size() != num.number.size()) return false;
    for (int i = 0; i < number.size(); ++i) if (this->number[i] != num.number[i]) return false;
    return true;
}

bool Bignum::operator!=(const Bignum& num) const {
    return !(*this == num);
}

bool Bignum::operator>(const Bignum& num) {
    if (this->isPositive == num.isPositive) {
        int length = 0;
        if (this->number.size() >= num.number.size()) length = this->number.size();
        else length = num.number.size();
        for (int i = length - 1; i >= 0; --i) {
            if (getDigit(i) > num.getDigit(i)) {
                if (!this->isPositive && !num.isPositive) return false;
                return true;
            }
            if (getDigit(i) < num.getDigit(i)) {
                if (!this->isPositive && !num.isPositive) return true;
                return false;
            }
        }
    }
    else if (this->isPositive && !num.isPositive) {
        return true;
    }
    return false;//if this is negative && num is positive
}

bool Bignum::operator<(Bignum& num) {
    return num > * this;
}

bool Bignum::operator>=(Bignum& num) {
    if (*this == num) return true;
    return *this > num;
}

bool Bignum::operator<=(Bignum& num) {
    if (*this == num) return true;
    return num > * this;
}

Bignum::operator bool() const {
    return !isZero();
}

Bignum Bignum::operator+(Bignum& num) {
    if (this->isPositive == num.isPositive) {//both positive or negative
        Bignum result;
        result.number.resize(std::fmax(this->number.size(), num.number.size()));
        for (int i = 0; i < result.number.size(); ++i) {
            result.number[i] = this->getDigit(i) + num.getDigit(i);
        }
        result.handlePositiveCarry();
        if (!this->isPositive && !num.isPositive) result.isPositive = false;
        return result;
    }
    else if (this->isPositive) {//second num negative
        Bignum copy = num;
        copy.isPositive = true;
        return *this - copy;
    }
    else if (!this->isPositive) {//first num negative
        Bignum copy = *this;
        copy.isPositive = true;
        return num - copy;
    }
    return *this;
}

Bignum Bignum::operator-(Bignum& num) {
    if (this->isPositive == num.isPositive) {//both positive or negative
        Bignum result;
        result.number.resize(std::fmax(this->number.size(), num.number.size()));
        if ((this->isPositive && *this < num) || (!this->isPositive && *this > num)) {
            result = num - *this;
            result.isPositive = !result.isPositive;
            return result;
        }
        for (int i = 0; i < result.number.size(); ++i) {
            result.number[i] = this->getDigit(i) - num.getDigit(i);
        }
        result.handleNegativeCarry();
        result.removeLeadingZeroes();
        if (!this->isPositive && !num.isPositive) result.isPositive = false;
        return result;
    }
    else if (this->isPositive) {//second num negative
        Bignum copy = num;
        copy.isPositive = true;
        return *this + copy;
    }
    else if (!this->isPositive) {//first num negative
        Bignum result;
        Bignum copy = *this;
        copy.isPositive = true;
        result = copy + num;
        result.isPositive = false;
        return result;
    }
    return *this;
}

Bignum Bignum::operator*(const Bignum& num) {
    Bignum result;
    result.number.resize(number.size() + num.number.size(), 0);
    for (int i = 0; i < number.size(); ++i) {
        for (int j = 0; j < num.number.size(); ++j) {
            result.number[i + j] += number[i] * num.number[j];
        }
    }
    result.handlePositiveCarry();
    result.removeLeadingZeroes();
    if (this->isPositive != num.isPositive) result.isPositive = false;
    return result;
}

Bignum Bignum::operator/(Bignum& div) {
    if (abs(div) > abs(*this)) return *this;
    Bignum copy(abs(*this));
    Bignum num(abs(div));
    Bignum result("0");
    do {
        copy = copy - num;
        ++result;
    } while (copy >= num);
    if (this->isPositive != div.isPositive) result.isPositive = false;
    return result;
}

Bignum Bignum::operator%(Bignum &div) {
    if(abs(div) > abs(*this)) return *this;
    Bignum copy (abs(*this));
    Bignum num (abs(div));
    do {
    copy = copy - num;
    } while(copy >= num);
    return copy;
}
