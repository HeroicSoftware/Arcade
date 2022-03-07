/*
 * PADDLE.h
 *
 *  Created on: Feb 9, 2022
 *      Author: Jordan Hunt
 */

#ifndef GAMES_BREAKOUT_PADDLE_H_
#define GAMES_BREAKOUT_PADDLE_H_

#include "Application.h"
#include "Ball.h"
#include "BoundaryEdge.h"
#include "cassert"
#include "Excluder.h"
#include "Screen.h"
#include "Utility.h"
#include <stdint.h>
enum PaddleMovementDirection
{
    LEFT = 1 << 0,
    RIGHT = 1 << 1
};

class Paddle : public Excluder
{
public:
    static const uint32_t WIDTH = 50;
    static const uint32_t HEIGHT = 10;
    void Initialize(const AxisAlignedRectangle &rectangle, const AxisAlignedRectangle &boundsRectangle);
    void Update(uint32_t deltaTime, Ball &ball);
    void Draw(Screen &screen);
    Paddle();
    virtual ~Paddle();
    inline bool IsMovingLeft() const
    {
        return movementDirection == PaddleMovementDirection::LEFT;
    }
    inline bool IsMovingRight() const
    {
        return movementDirection == PaddleMovementDirection::RIGHT;
    }
    inline void StopMovement()
    {
        movementDirection = 0;
    }
    inline void UnsetMovementDirection(PaddleMovementDirection direction)
    {
        movementDirection &= ~direction;
    }
    inline void SetMovementDirection(PaddleMovementDirection direction)
    {
        movementDirection |= direction;
    }
    bool Bounce(Ball &ball);

private:
    uint32_t movementDirection;
    AxisAlignedRectangle confinementBoundary;
    const float VELOCITY = 105.5f;
    const float CORNER_BOUNCE_AMOUNT = .03f;
};

#endif /* GAMES_BREAKOUT_PADDLE_H_ */
