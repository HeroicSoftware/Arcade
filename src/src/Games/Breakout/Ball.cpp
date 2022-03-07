/*
 * Ball.cpp
 *
 *  Created on: Feb 17, 2022
 *      Author: Jordan Hunt
 */

#include <Breakout/Ball.h>

const float Ball::RADIUS = 5.0f;
Ball::Ball() : Ball(Vector2D::Zero, RADIUS)
{
    // TODO Auto-generated constructor stub
}

Ball::Ball(const Vector2D &position, float radius) : boundingBox((position - Vector2D(radius, radius)), ((radius * 2.0f) - .5f), ((radius * 2.0f) - .5f)), velocity(Vector2D::Zero)
{
}

void Ball::Update(uint32_t deltaTime)
{
    boundingBox.MoveByDeltaOffset(velocity * MillisecondsToSeconds(deltaTime));
}

void Ball::Draw(Screen &screen)
{
    Circle circle = { boundingBox.GetCenterPoint(), GetRadius() };
    screen.Draw(circle, Color::Black(), true, Color::Black());
}

void Ball::MakeFlushWithEdge(const BoundaryEdge &edge, Vector2D &pointOnEdge, bool limitToEdge)
{
    if (edge.normal == DOWN_DIRECTION)
    {
        boundingBox.MoveTo(Vector2D(boundingBox.GetOriginPoint().GetX(), edge.edge.GetPoint0().GetY() + edge.normal.GetY()));
    }
    else if (edge.normal == UP_DIRECTION)
    {
        boundingBox.MoveTo(Vector2D(boundingBox.GetOriginPoint().GetX(), edge.edge.GetPoint0().GetY() - boundingBox.GetHeight()));
    }
    else if (edge.normal == RIGHT_DIRECTION)
    {
        boundingBox.MoveTo(Vector2D(edge.edge.GetPoint0().GetX() + edge.normal.GetX(), boundingBox.GetOriginPoint().GetY()));
    }
    else if (edge.normal == LEFT_DIRECTION)
    {
        boundingBox.MoveTo(Vector2D(edge.edge.GetPoint0().GetX() - boundingBox.GetWidth(), boundingBox.GetOriginPoint().GetY()));
    }
    pointOnEdge = edge.edge.ClosestPoint(boundingBox.GetCenterPoint(), limitToEdge);
}

void Ball::MoveTo(const Vector2D &point)
{
    boundingBox.MoveTo(point - Vector2D(GetRadius(), GetRadius()));
}
void Ball::Bounce(const BoundaryEdge &edge)
{
    Vector2D bouncedOffOfEdge;
    MakeFlushWithEdge(edge, bouncedOffOfEdge, false);
    velocity = velocity.GetReflectionVector(edge.normal);
}

Ball::~Ball()
{
    // TODO Auto-generated destructor stub
}
