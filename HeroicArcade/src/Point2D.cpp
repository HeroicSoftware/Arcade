#include "Point2D.h"

// Initializer list Constructor
Point2D::Point2D(int x, int y) : x(x), y(y)
{
}
// Default constructor
Point2D::Point2D() : Point2D(0, 0)
{
}
void Point2D::SetPosition(int positionX, int positionY)
{
    this->x = positionX;
    this->y = positionY;
}

void Point2D::Display()
{
    std::cout << "X: " << this->x << ", Y: " << this->y << std::endl;
}

Point2D &Point2D::ReferenceToSelf()
{
    return *this;
}

Point2D *Point2D::PointerToSelf()
{
    return this;
}
