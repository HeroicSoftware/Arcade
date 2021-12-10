/*
 * Fraction.h
 *
 *  Created on: Nov 11, 2021
 *      Author: Heroic
 */
#ifndef FRACTION_H_
#define FRACTION_H_
#include <iostream>
class Fraction
{
public:
    Fraction();
    Fraction(int numerator, int denominator);
    Fraction Add(Fraction otherFraction);
    Fraction Divide(Fraction otherFraction);
    Fraction Multiply(Fraction otherFraction);
    Fraction Subtract(Fraction otherFraction);
    virtual ~Fraction();
    inline int GetDenominator() const
    {
        return this->denominator;
    }
    inline int GetNumerator() const
    {
        return this->numerator;
    }
    void Compare(Fraction otherFraction);
    friend std::ostream &operator<<(std::ostream &consoleOut, const Fraction &fraction);
    void SetDenominator(int denominator);
    void SetNumerator(int numerator);
    // Static variable
    static Fraction oneHalf;
    static Fraction oneThird;
    static Fraction oneFourth;
    static Fraction oneFifth;

private:
    Fraction SimplifyFraction(Fraction someFraction);
    int numerator;
    int denominator;
};
#endif /* FRACTION_H_ */
