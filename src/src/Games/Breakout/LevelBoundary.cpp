/*
 * LevelBoundary.cpp
 *
 *  Created on: Feb 20, 2022
 *      Author: Jordan Hunt
 */

#include <Breakout/LevelBoundary.h>

LevelBoundary::LevelBoundary()
{
}

LevelBoundary::LevelBoundary(const AxisAlignedRectangle &boundaryRectangle)
{
    includer.Initialize(boundaryRectangle, true);
}

bool LevelBoundary::HasCollided(const Ball &ball, BoundaryEdge &edge)
{
    for (int i = 0; i < NUMBER_OF_EDGES; i++)
    {
        BoundaryEdge collisionEdge = includer.GetEdge(static_cast<EdgeType>(i));
        if (HasCollidedWithEdge(ball, collisionEdge))
        {
            edge = collisionEdge;
            return true;
        }
    }
    return false;
}

bool LevelBoundary::HasCollidedWithEdge(const Ball &ball, const BoundaryEdge &edge) const
{
    return (edge.edge.MinDistanceFrom(ball.GetPosition()) < ball.GetRadius());
}
