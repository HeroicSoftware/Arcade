/*
 * Circle.cpp
 *
 *  Created on: Dec 20, 2021
 *      Author: Jordan Hunt
 */

#include <Circle.h>
#include <Utility.h>

Circle::Circle() : Circle(Vector2D::Zero, 0)
{
    // TODO Auto-generated constructor stub
}

Circle::Circle(const Vector2D &center, float radius) : radius(radius)
{
    points.push_back(center);
}

// Get the distance between the two center points, if the distance is less than the sum of the two radius then there is an intersection
bool Circle::Intersects(const Circle &otherCircle) const
{
    return (GetCenterPoint().GetDistance(otherCircle.GetCenterPoint()) < (radius + otherCircle.radius));
}

bool Circle::ContainsPoint(const Vector2D &point) const
{
    return IsLessThanOrEqual(GetCenterPoint().GetDistance(point), radius);
}

Circle::~Circle()
{
    // TODO Auto-generated destructor stub
}
