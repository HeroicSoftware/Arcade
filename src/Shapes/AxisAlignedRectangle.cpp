/*
 * Rectangle.cpp
 *
 *  Created on: Dec 17, 2021
 *      Author: Jordan Hunt
 */

#include <AxisAlignedRectangle.h>

AxisAlignedRectangle::AxisAlignedRectangle() : AxisAlignedRectangle(Vector2D::Zero, Vector2D::Zero)
{
    // TODO Auto-generated constructor stub
}

AxisAlignedRectangle::AxisAlignedRectangle(const Vector2D &originPoint, unsigned int width, unsigned int height)
{
    points.push_back(originPoint);
    points.push_back(Vector2D((originPoint.GetX() + width - 1), (originPoint.GetY() + height - 1)));
}

AxisAlignedRectangle::AxisAlignedRectangle(const Vector2D &originPoint, const Vector2D &endPoint)
{
    points.push_back(originPoint);
    points.push_back(endPoint);
}

float AxisAlignedRectangle::GetWidth() const
{
    float width = (GetEndPoint().GetX() - GetOriginPoint().GetX() + 1);
    return width;
}

float AxisAlignedRectangle::GetHeight() const
{
    float height = (GetEndPoint().GetY() - GetOriginPoint().GetY() + 1);
    return height;
}

bool AxisAlignedRectangle::Intersects(const AxisAlignedRectangle &otherRectangle) const
{
    bool intersectionLeft = otherRectangle.GetEndPoint().GetX() < GetOriginPoint().GetX();
    bool intersectionTop = otherRectangle.GetOriginPoint().GetY() > GetEndPoint().GetY();
    bool intersectionRight = otherRectangle.GetEndPoint().GetY() < GetOriginPoint().GetY();
    bool interSectionBottom = otherRectangle.GetEndPoint().GetY() > GetEndPoint().GetY();

    // Any of these conditions are true then there would be a intersection
    return !(intersectionLeft || intersectionTop || intersectionRight || interSectionBottom);
}

bool AxisAlignedRectangle::ContainsPoint(const Vector2D &point) const
{
    bool withinX = point.GetX() >= GetOriginPoint().GetX() && point.GetX() <= GetEndPoint().GetX();
    bool withinY = point.GetY() >= GetOriginPoint().GetY() && point.GetY() <= GetEndPoint().GetY();
    return (withinX && withinY);
}

AxisAlignedRectangle AxisAlignedRectangle::Inset(const AxisAlignedRectangle &rectangle, Vector2D &insets)
{
    AxisAlignedRectangle newRectangle = AxisAlignedRectangle((rectangle.GetOriginPoint() + insets), (rectangle.GetWidth() - 2 * insets.GetX()), (rectangle.GetHeight() - 2 * insets.GetY()));
    return newRectangle;
}

Vector2D AxisAlignedRectangle::GetCenterPoint() const
{
    return Vector2D(GetOriginPoint().GetX() + GetWidth() / 2.0f, GetOriginPoint().GetY() + GetHeight() / 2.0f);
}

std::vector<Vector2D> AxisAlignedRectangle::GetPoints() const
{
    std::vector<Vector2D> rectanglePoints;
    rectanglePoints.push_back(points[0]);
    rectanglePoints.push_back(Vector2D(points[1].GetX(), points[0].GetY()));
    rectanglePoints.push_back(points[1]);
    rectanglePoints.push_back(Vector2D(points[0].GetX(), points[1].GetY()));
    return rectanglePoints;
}

AxisAlignedRectangle::~AxisAlignedRectangle()
{
    // TODO Auto-generated destructor stub
}

void AxisAlignedRectangle::MoveTo(const Vector2D &position)
{
    float currentWidth = GetWidth();
    float currentHeight = GetHeight();
    SetOriginPoint(position);
    SetEndingPoint(Vector2D((position.GetX() + currentWidth - 1), (position.GetY() + currentHeight - 1)));
}
