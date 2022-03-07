/*
 * Rectangle.h
 *
 *  Created on: Dec 17, 2021
 *      Author: Jordan Hunt
 */

#ifndef SHAPES_AXISALIGNEDRECTANGLE_H_
#define SHAPES_AXISALIGNEDRECTANGLE_H_
#include "Shape.h"
#include "Utility.h"
#include <cmath>

class AxisAlignedRectangle : public Shape
{
public:
    AxisAlignedRectangle();
    AxisAlignedRectangle(const Vector2D &originPoint, unsigned int width, unsigned int height);
    AxisAlignedRectangle(const Vector2D &originPoint, const Vector2D &endPoint);
    inline void SetOriginPoint(const Vector2D &originPoint)
    {
        points[0] = originPoint;
    }
    inline void SetEndingPoint(const Vector2D &endPoint)
    {
        points[1] = endPoint;
    }
    inline Vector2D GetOriginPoint() const
    {
        return points[0];
    }
    inline Vector2D GetEndPoint() const
    {
        return points[1];
    }

    bool ContainsPoint(const Vector2D &point) const;
    bool Intersects(const AxisAlignedRectangle &otherRectangle) const;
    float GetHeight() const;
    float GetWidth() const;
    static AxisAlignedRectangle Inset(const AxisAlignedRectangle &rectangle, Vector2D &insets);
    virtual void MoveTo(const Vector2D &point) override;
    virtual ~AxisAlignedRectangle();
    virtual std::vector<Vector2D> GetPoints() const override;
    virtual Vector2D GetCenterPoint() const override;
};

#endif /* SHAPES_AXISALIGNEDRECTANGLE_H_ */
