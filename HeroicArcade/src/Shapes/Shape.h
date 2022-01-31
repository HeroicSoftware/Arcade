/*
 * Shape.h
 *
 *  Created on: Dec 17, 2021
 *      Author: Jordan Hunt
 */

#ifndef SHAPES_SHAPE_H_
#define SHAPES_SHAPE_H_
#include "Vector2D.h"
#include <vector>

class Shape
{
public:
    // Pure Virtual Methods
    virtual Vector2D GetCenterPoint() const = 0;
    virtual void MoveTo(const Vector2D &point) = 0;
    virtual ~Shape();
    inline virtual std::vector<Vector2D> GetPoints() const
    {
        return points;
    }
    void MoveByDeltaOffset(const Vector2D &deltaOffset);

protected:
    std::vector<Vector2D> points;
};

#endif /* SHAPES_SHAPE_H_ */
