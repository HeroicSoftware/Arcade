/*
 * Circle.h
 *
 *  Created on: Dec 20, 2021
 *      Author: Jordan Hunt
 */

#ifndef SHAPES_CIRCLE_H_
#define SHAPES_CIRCLE_H_

#include "Shape.h"

class Circle : public Shape
{
public:
    Circle();
    Circle(const Vector2D &center, float radius);
    inline virtual Vector2D GetCenterPoint() const override
    {
        return points[0];
    }
    inline float GetRadius() const
    {
        return radius;
    }
    inline void SetRadius(float radius)
    {
        this->radius = radius;
    }
    inline virtual void MoveTo(const Vector2D &position) override
    {
        points[0] = position;
    }
    bool Intersects(const Circle &otherCircle) const;
    bool ContainsPoint(const Vector2D &point) const;
    virtual ~Circle();

private:
    float radius;
};

#endif /* SHAPES_CIRCLE_H_ */
