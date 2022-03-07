/*
 * Ball.h
 *
 *  Created on: Feb 17, 2022
 *      Author: Jordan Hunt
 */

#ifndef GAMES_BREAKOUT_BALL_H_
#define GAMES_BREAKOUT_BALL_H_
#include <stdint.h>
#include "AxisAlignedRectangle.h"
#include "Screen.h"
#include "BoundaryEdge.h"
class Ball
{
public:
    Ball();
    Ball(const Vector2D &position, float radius);
    void Update(uint32_t deltaTime);
    void Draw(Screen &screen);
    void MakeFlushWithEdge(const BoundaryEdge &edge, Vector2D &pointOnEdge, bool limitToEdge);
    inline void Stop()
    {
        velocity = Vector2D::Zero;
    }
    void MoveTo(const Vector2D &point);
    inline const AxisAlignedRectangle GetBoundingBox() const
    {
        return boundingBox;
    }
    inline void SetVelocity(const Vector2D &velocity)
    {
        this->velocity = velocity;
    }
    inline Vector2D GetVelocity() const
    {
        return velocity;
    }
    inline float GetRadius() const
    {
        return (boundingBox.GetWidth() / 2.0f);
    }
    inline Vector2D GetPosition() const
    {
        return (boundingBox.GetCenterPoint());
    }
    void Bounce(const BoundaryEdge &edge);
    virtual ~Ball();

private:
    AxisAlignedRectangle boundingBox;
    Vector2D velocity;
    static const float RADIUS;
};

#endif /* GAMES_BREAKOUT_BALL_H_ */
