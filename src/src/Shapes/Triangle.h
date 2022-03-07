/*
 * Triangle.h
 *
 *  Created on: Dec 17, 2021
 *      Author: Jordan Hunt
 */

#ifndef SHAPES_TRIANGLE_H_
#define SHAPES_TRIANGLE_H_
#include "Shape.h"
#include <cmath>
#include "Utility.h"

class Triangle : public Shape
{
public:
    Triangle();
    Triangle(const Vector2D &point0, const Vector2D &point1, const Vector2D &point2);
    inline void SetPoint0(const Vector2D &point0)
    {
        points[0] = point0;
    }
    inline void SetPoint1(const Vector2D &point1)
    {
        points[1] = point1;
    }
    inline void SetPoint2(const Vector2D &point2)
    {
        points[2] = point2;
    }
    inline Vector2D GetPoint0() const
    {
        return points[0];
    }
    inline Vector2D GetPoint1() const
    {
        return points[1];
    }
    inline Vector2D GetPoint2() const
    {
        return points[2];
    }
    bool ContainsPoint(const Vector2D &point) const;
    float GetArea() const;
    virtual ~Triangle();
    virtual Vector2D GetCenterPoint() const override;
    virtual void MoveTo(const Vector2D &point) override;

private:
    float GetArea(const Vector2D &point0, const Vector2D &point1, const Vector2D &point2) const;
};
#endif /* SHAPES_TRIANGLE_H_ */
