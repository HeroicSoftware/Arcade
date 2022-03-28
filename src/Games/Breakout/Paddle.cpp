/*
 * Paddle.cpp
 *
 *  Created on: Feb 9, 2022
 *      Author: Jordan Hunt
 */

#include <Breakout/Paddle.h>

Paddle::Paddle()
{
    // TODO Auto-generated constructor stub
}

void Paddle::Initialize(const AxisAlignedRectangle &rectangle, const AxisAlignedRectangle &boundsRectangle)
{
    // Call parent initializer
    Excluder::Initialize(rectangle);
    this->movementDirection = 0;
    this->confinementBoundary = boundsRectangle;
}

void Paddle::Update(uint32_t deltaTime, Ball &ball)
{
    // Make sure the ball never goes INTO the paddle
    if (GetRectangle().ContainsPoint(ball.GetPosition()))
    {
        Vector2D pointOnEdge;
        ball.MakeFlushWithEdge(GetEdge(BOTTOM_EDGE), pointOnEdge, true);
    }
    if (movementDirection != 0)
    {
        Vector2D movementVector;
        if ((movementDirection & PaddleMovementDirection::LEFT) == PaddleMovementDirection::LEFT && (movementDirection & PaddleMovementDirection::RIGHT) == PaddleMovementDirection::RIGHT)
        {
            movementVector = Vector2D::Zero;
        }
        else if (movementDirection == PaddleMovementDirection::LEFT)
        {
            movementVector = LEFT_DIRECTION;
            std::cout << "[Paddle.cpp] - [LEFT_DIRECTION]" << std::endl;
        }
        else
        {
            movementVector = RIGHT_DIRECTION;
            std::cout << "[Paddle.cpp] - [RIGHT_DIRECTION]" << std::endl;
        }
        Vector2D deltaX = movementVector * VELOCITY * MillisecondsToSeconds(deltaTime);
        MoveBy(deltaX);
        // Keep in window bounds
        const AxisAlignedRectangle &bounds = GetRectangle();
        if (IsGreaterThanOrEqual(confinementBoundary.GetOriginPoint().GetX(), bounds.GetOriginPoint().GetX()))
        {
            MoveTo(Vector2D(confinementBoundary.GetOriginPoint().GetX(), bounds.GetOriginPoint().GetY()));
        }
        else if (IsGreaterThanOrEqual(bounds.GetEndPoint().GetX(), confinementBoundary.GetEndPoint().GetX()))
        {
            MoveTo(Vector2D(confinementBoundary.GetEndPoint().GetX() - bounds.GetWidth(), bounds.GetOriginPoint().GetY()));
        }
    }
}

void Paddle::Draw(Screen &screen)
{
    // Draw the rectangle of the paddle
    screen.Draw(GetRectangle(), Color::Black(), true, Color::Black());
}
bool Paddle::Bounce(Ball &ball)
{
    BoundaryEdge edge;
    if (HasCollided(ball.GetBoundingBox(), edge))
    {
        Vector2D pointOnEdge;
        ball.MakeFlushWithEdge(edge, pointOnEdge, true);
        if (edge.edge == GetEdge(TOP_EDGE).edge)
        {
            float edgeLength = edge.edge.GetLength();
            assert(!IsEqual(edgeLength, 0));
            float topEdgeX = (pointOnEdge.GetX() - edge.edge.GetPoint0().GetX()) / edgeLength;

            if (((topEdgeX <= CORNER_BOUNCE_AMOUNT) && ball.GetVelocity().GetX() > 0) || (topEdgeX >= (1.0f - CORNER_BOUNCE_AMOUNT) && ball.GetVelocity().GetX() < 0))
            {
                ball.SetVelocity(-ball.GetVelocity());
                return true;
            }
        }
        ball.SetVelocity(ball.GetVelocity().GetReflectionVector(edge.normal));
        return true;
    }
    return false;
}
Paddle::~Paddle()
{
    // TODO Auto-generated destructor stub
}
