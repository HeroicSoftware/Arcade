/*
 * Fraction.cpp
 *
 *  Created on: Nov 11, 2021
 *      Author: jordan
 */
#include "Fraction.h"
// Default Constructor
Fraction::Fraction() : Fraction(0, 1)
{
}
// Initializer List Constructor
Fraction::Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator)
{
}
// Add two fractions together
Fraction Fraction::Add(Fraction otherFraction)
{
    Fraction newFraction;
    // Check to see if the two fractions have common denominator
    if (this->GetDenominator() == otherFraction.GetDenominator())
    {
        // Setup new fraction to return
        int newNumerator = (this->GetNumerator() + otherFraction.GetNumerator());
        int newDenominator = (this->GetDenominator());
        newFraction.SetNumerator(newNumerator);
        newFraction.SetDenominator(newDenominator);
    }
    else
    {
        // Multiply the numerators by the denominator of the other fraction
        this->SetNumerator(this->GetNumerator() * otherFraction.GetDenominator());
        otherFraction.SetNumerator(otherFraction.GetNumerator() * this->GetDenominator());
        // Add new numerators and set NewFraction.Numerator
        newFraction.SetNumerator(this->GetNumerator() + otherFraction.GetNumerator());
        // Create a common denominator and NewFraction.Denominator
        newFraction.SetDenominator(this->GetDenominator() * otherFraction.GetDenominator());
    }
    return (SimplifyFraction(newFraction));
}
// Subtract one fraction from another
Fraction Fraction::Subtract(Fraction otherFraction)
{
    Fraction newFraction;
    // Check to see if the two fractions have common denominator
    if (this->GetDenominator() == otherFraction.GetDenominator())
    {
        // Setup new fraction to return
        int newNumerator = (this->GetNumerator() - otherFraction.GetNumerator());
        int newDenominator = (this->GetDenominator());
        newFraction.SetNumerator(newNumerator);
        newFraction.SetDenominator(newDenominator);
    }
    else
    {
        // Multiply the numerators by the denominator of the other fraction
        this->SetNumerator(this->GetNumerator() * otherFraction.GetDenominator());
        otherFraction.SetNumerator(otherFraction.GetNumerator() * this->GetDenominator());
        // Add new numerators and set NewFraction.Numerator
        newFraction.SetNumerator(this->GetNumerator() - otherFraction.GetNumerator());
        // Create a common denominator and NewFraction.Denominator
        newFraction.SetDenominator(this->GetDenominator() * otherFraction.GetDenominator());
    }
    return (SimplifyFraction(newFraction));
}
// Multiply two fractions together
Fraction Fraction::Multiply(Fraction otherFraction)
{
    Fraction newFraction;
    int newNumerator = (this->GetNumerator() * otherFraction.GetNumerator());
    int newDenominator = (this->GetDenominator() * otherFraction.GetDenominator());
    newFraction.SetNumerator(newNumerator);
    newFraction.SetDenominator(newDenominator);
    return (SimplifyFraction(newFraction));
}
// Divide two fractions together
Fraction Fraction::Divide(Fraction otherFraction)
{
    // Inverse the otherFraction
    int inverseNumerator = otherFraction.GetDenominator();
    int inverseDenominator = otherFraction.GetNumerator();
    otherFraction.SetNumerator(inverseNumerator);
    otherFraction.SetDenominator(inverseDenominator);
    // Multiply using the inverse fraction
    return (Multiply(otherFraction));
}

void Fraction::Compare(Fraction otherFraction)
{
    if ((this->GetNumerator() * otherFraction.GetDenominator()) > (this->GetDenominator() * otherFraction.GetNumerator()))
    {
        std::cout << "Fraction 1 is greater than Fraction 2" << std::endl;
    }
    else if ((this->GetNumerator() * otherFraction.GetDenominator()) < (this->GetDenominator() * otherFraction.GetNumerator()))
    {
        std::cout << "Fraction 2 is greater than Fraction 1" << std::endl;
    }
    else
    {
        std::cout << "Fraction 1 and Fraction 2 are of equal value" << std::endl;
    }
}

Fraction Fraction::SimplifyFraction(Fraction fractionToSimplify)
{
    int largestValue = 0;
    int numerator = fractionToSimplify.GetNumerator();
    int denominator = fractionToSimplify.GetDenominator();
    if (numerator > denominator)
    {
        largestValue = numerator;
    }
    else
    {
        largestValue = denominator;
    }
    // Find the largest number that will divide both numerator and denominator evenly
    int greatestCommonDivisor = 0;
    for (int i = largestValue; i >= 2; i--)
    {
        if (numerator % i == 0 && denominator % i == 0)
        {
            greatestCommonDivisor = i;
            break;
        }
    }
    if (greatestCommonDivisor != 0)
    {
        numerator /= greatestCommonDivisor;
        denominator /= greatestCommonDivisor;
    }
    Fraction simplifiedFraction(numerator, denominator);
    return simplifiedFraction;
}
Fraction::~Fraction()
{
}

void Fraction::SetDenominator(int denominator)
{
    this->denominator = denominator;
}

void Fraction::SetNumerator(int numerator)
{
    this->numerator = numerator;
}
std::ostream &operator<<(std::ostream &consoleOut, const Fraction &fraction)
{
    consoleOut << fraction.numerator << " / " << fraction.denominator << std::endl;
    return consoleOut;
}
// Static variables
Fraction Fraction::oneHalf = Fraction(1, 2);
Fraction Fraction::oneThird = Fraction(1, 3);
Fraction Fraction::oneFourth = Fraction(1, 4);
Fraction Fraction::oneFifth = Fraction(1, 5);
