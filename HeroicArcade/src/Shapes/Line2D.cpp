/*
 * Line2D.cpp
 *
 *  Created on: Dec 13, 2021
 *      Author: Jordan
 */

#include "Line2D.h"

Line2D::Line2D() : Line2D((Vector2D::Zero), (Vector2D::Zero))
{
    // TODO Auto-generated constructor stub
}

Line2D::Line2D(float x0, float y0, float x1, float y1) : Line2D(Vector2D(x0, y0), Vector2D(x1, y1))
{
}

Line2D::Line2D(const Vector2D &point0, const Vector2D &point1) : point0(point0), point1(point1)
{
}

bool Line2D::operator==(const Line2D &line2D) const
{
    return (line2D.GetPoint0() == this->point0 && line2D.GetPoint1() == this->point1);
}

float Line2D::MinDistanceFrom(const Vector2D &vector2D, bool limitToSegment) const
{
    // The distance from the closest point to point0
    return (vector2D.GetDistance(ClosestPoint(vector2D, limitToSegment)));
}

Vector2D Line2D::ClosestPoint(const Vector2D &point, bool limitToSegment) const
{
    Vector2D point0ToPoint = point - point0;
    Vector2D point0ToPoint1 = point1 - point0;
    float length = point0ToPoint1.MagnitudeSquared();
    float dotProduct = point0ToPoint.GetDotProduct(point0ToPoint1);
    float t = dotProduct / length;
    if (limitToSegment)
    {
        t = std::fmax(0.0f, std::fmin(1.0f, t));
    }
    return (point0 + point0ToPoint1 * t);
}

Vector2D Line2D::GetMidpoint() const
{
    return (Vector2D((point0.GetX() + point1.GetX()) / 2, (point0.GetY() + point1.GetY()) / 2));
}

float Line2D::GetSlope() const
{
    float dx = this->point1.GetX() - this->point0.GetX();
    if (fabsf(dx) < EPSILON)
    {
        return 0;
    }
    float dy = this->point1.GetY() - this->point0.GetY();
    float slope = dy / dx;
    return slope;
}

float Line2D::GetLength() const
{
    return (point1.GetDistance(point0));
}

Line2D::~Line2D()
{
    // TODO Auto-generated destructor stub
}
