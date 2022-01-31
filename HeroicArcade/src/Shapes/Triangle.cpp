/*
 * Triangle.cpp
 *
 *  Created on: Dec 17, 2021
 *      Author: Jordan Hunt
 */
#include <Triangle.h>
Triangle::Triangle() : Triangle(Vector2D::Zero, Vector2D::Zero, Vector2D::Zero)
{
    // TODO Auto-generated constructor stub
}
Triangle::Triangle(const Vector2D &point0, const Vector2D &point1, const Vector2D &point2)
{
    points.push_back(point0);
    points.push_back(point1);
    points.push_back(point2);
}
bool Triangle::ContainsPoint(const Vector2D &point) const
{
    // Using this passed in point, assume compare each area
    float thisArea = GetArea();
    float area1 = GetArea(point, GetPoint1(), GetPoint2());
    float area2 = GetArea(GetPoint0(), point, GetPoint2());
    float area3 = GetArea(GetPoint0(), GetPoint1(), point);
    return IsEqual(thisArea, (area1 + area2 + area3));
}
float Triangle::GetArea() const
{
    return GetArea(this->GetPoint0(), this->GetPoint1(), this->GetPoint2());
}
Triangle::~Triangle()
{
    // TODO Auto-generated destructor stub
}
Vector2D Triangle::GetCenterPoint() const
{
    // Calculate "centroid"
    float centerX = (points[0].GetX() + points[1].GetX() + points[2].GetX()) / 3.0f;
    float centerY = (points[0].GetY() + points[1].GetY() + points[2].GetY()) / 3.0f;
    return (Vector2D(centerX, centerY));
}
// This function moves the triangle to a new location by passing what is to be the next centroid of the triangle
void Triangle::MoveTo(const Vector2D &destinationPoint)
{
    // New location
    Vector2D delta = destinationPoint - this->GetCenterPoint();

    points[0] = Vector2D(points[0].GetX() + delta.GetX(), points[0].GetY() + delta.GetY());
    points[1] = Vector2D(points[1].GetX() + delta.GetX(), points[1].GetY() + delta.GetY());
    points[2] = Vector2D(points[2].GetX() + delta.GetX(), points[2].GetY() + delta.GetY());
}
float Triangle::GetArea(const Vector2D &point0, const Vector2D &point1, const Vector2D &point2) const
{
    Vector2D base = point1 - point0;
    Vector2D hypotenuse = point2 - point0;
    Vector2D height = hypotenuse - (hypotenuse.GetDotProduct(base.GetUnitVector()) * base.GetUnitVector());
    float baseTimesHeight = height.Magnitude() * base.Magnitude() / 2;
    return baseTimesHeight;
}
