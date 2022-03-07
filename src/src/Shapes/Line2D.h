/*
 * Line.h
 *
 *  Created on: Dec 13, 2021
 *      Author: Jordan
 */

#ifndef SHAPES_LINE2D_H_
#define SHAPES_LINE2D_H_
#include "Vector2D.h"
#include "Utility.h"
class Line2D
{
public:
    Line2D();
    Line2D(float x0, float y0, float x1, float y1);
    Line2D(const Vector2D &point0, const Vector2D &point1);
    inline const Vector2D &GetPoint0() const
    {
        return this->point0;
    }
    inline const Vector2D &GetPoint1() const
    {
        return this->point1;
    }
    inline void SetPoint0(const Vector2D &point0)
    {
        this->point0 = point0;
    }
    inline void SetPoint1(const Vector2D &point1)
    {
        this->point1 = point1;
    }
    bool operator==(const Line2D &line2D) const;
    float MinDistanceFrom(const Vector2D &vector2D, bool limitToSegment = false) const;
    Vector2D ClosestPoint(const Vector2D &point, bool limitToSegment = false) const;
    Vector2D GetMidpoint() const;
    float GetSlope() const;
    float GetLength() const;
    virtual ~Line2D();

private:
    Vector2D point0;
    Vector2D point1;
};

#endif /* SHAPES_LINE2D_H_ */
