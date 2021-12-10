//============================================================================
// Name        : HeroicArcade.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include "Time.h"
#include "Fraction.h"
#include "Vector2D.h"
#include "Point2D.h"
using namespace std;
const Vector2D Vector2D::Zero;
int main(int argc, char *argv[]) {
    Point2D myPoint(5, 7);
    Point2D &referencePoint = myPoint.ReferenceToSelf();
    Point2D *pointerPoint = myPoint.PointerToSelf();
    referencePoint.Display();
    pointerPoint->Display();
    cout << "Point's address: " << &myPoint << endl;
    cout << "ReferencePoint is referencing: " << &referencePoint << endl;
    cout << "PointerPoint is pointing to " << pointerPoint << endl;
    Fraction fraction1(3, 4);
    Fraction fraction2(1, 2);
    Fraction fraction3 = fraction1.Divide(fraction2);
    cout << fraction3 << endl;
    fraction3.Compare(fraction1); // Fraction 3 should be greater than fraction 1
    Vector2D vector(10, 5);
    cout << vector << endl;
    Vector2D newVector(7, 9);
    cout << -newVector << endl;
    cout << newVector * 7 << endl;
    return 0;
}
