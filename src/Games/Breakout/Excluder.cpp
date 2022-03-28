/*
 * Excluder.cpp
 *
 *  Created on: Jan 31, 2022
 *      Author: Jordan Hunt
 */
#include "Excluder.h"

Excluder::Excluder()
{
    // TODO Auto-generated constructor stub
}
void Excluder::Initialize(const AxisAlignedRectangle &rectangle, bool reverseNormals)
{
    this->rectangle = rectangle;
    this->reverseNormals = reverseNormals;
    CreateEdges();
}
bool Excluder::HasCollided(const AxisAlignedRectangle &otherRectangle, BoundaryEdge &boundaryEdge) const
{
    if (rectangle.Intersects(otherRectangle))
    {
        float yMin =
                rectangle.GetOriginPoint().GetY() >= (otherRectangle.GetOriginPoint().GetY()) ? rectangle.GetOriginPoint().GetY() : otherRectangle.GetOriginPoint().GetY();
        float yMax =
                rectangle.GetEndPoint().GetY() <= otherRectangle.GetEndPoint().GetY() ? rectangle.GetEndPoint().GetY() : otherRectangle.GetEndPoint().GetY();
        float ySize = yMax - yMin;
        float xMin =
                rectangle.GetOriginPoint().GetX() >= otherRectangle.GetOriginPoint().GetX() ? rectangle.GetOriginPoint().GetX() : otherRectangle.GetOriginPoint().GetX();
        float xMax =
                rectangle.GetEndPoint().GetX() <= otherRectangle.GetEndPoint().GetX() ? rectangle.GetEndPoint().GetX() : otherRectangle.GetEndPoint().GetX();
        float xSize = xMax - xMin;
        // Figuring out much overlap there is between the two objects
        if (xSize > ySize)
        {
            if (otherRectangle.GetCenterPoint().GetY() > rectangle.GetCenterPoint().GetY())
            {
                boundaryEdge = edges[BOTTOM_EDGE];
            }
            else
            {
                boundaryEdge = edges[TOP_EDGE];
            }
        }
        // Collided left or right
        else
        {
            if (otherRectangle.GetCenterPoint().GetX() < rectangle.GetCenterPoint().GetX())
            {
                boundaryEdge = edges[LEFT_EDGE];
            }
            else
            {
                boundaryEdge = edges[RIGHT_EDGE];
            }
        }
        return true;
    }
    return false;
}
Vector2D Excluder::GetCollisionOffset(const AxisAlignedRectangle &otherRectangle) const
{
    BoundaryEdge edge;
    Vector2D offSet = Vector2D::Zero;
    if (HasCollided(otherRectangle, edge) == true)
    {
        float yMin =
                rectangle.GetOriginPoint().GetY() >= (otherRectangle.GetOriginPoint().GetY()) ? rectangle.GetOriginPoint().GetY() : otherRectangle.GetOriginPoint().GetY();
        float yMax =
                rectangle.GetEndPoint().GetY() <= otherRectangle.GetEndPoint().GetY() ? rectangle.GetEndPoint().GetY() : otherRectangle.GetEndPoint().GetY();
        float ySize = yMax - yMin;
        float xMin =
                rectangle.GetOriginPoint().GetX() >= otherRectangle.GetOriginPoint().GetX() ? rectangle.GetOriginPoint().GetX() : otherRectangle.GetOriginPoint().GetX();
        float xMax =
                rectangle.GetEndPoint().GetX() <= otherRectangle.GetEndPoint().GetX() ? rectangle.GetEndPoint().GetX() : otherRectangle.GetEndPoint().GetX();
        float xSize = xMax - xMin;
        if (!IsEqual(edge.normal.GetY(), 0))
        {
            offSet = (ySize + 1) * edge.normal;
        }
        else
        {
            offSet = (xSize + 1) * edge.normal;
        }
    }
    return offSet;
}
void Excluder::MoveBy(const Vector2D &delta)
{
    rectangle.MoveByDeltaOffset(delta);
    CreateEdges();
}
void Excluder::MoveTo(const Vector2D &point)
{
    rectangle.MoveTo(point);
    CreateEdges();
}
const BoundaryEdge& Excluder::GetEdge(EdgeType edge) const
{
    assert(edge != NUMBER_OF_EDGES);
    return edges[edge];
}
Excluder::~Excluder()
{
    // TODO Auto-generated destructor stub
}
void Excluder::CreateEdges()
{
    edges[TOP_EDGE].edge = { rectangle.GetOriginPoint().GetX(), rectangle.GetOriginPoint().GetY(), rectangle.GetEndPoint().GetX(), rectangle.GetOriginPoint().GetY() };
    edges[TOP_EDGE].normal = UP_DIRECTION;
    edges[LEFT_EDGE].edge = { rectangle.GetOriginPoint().GetX(), rectangle.GetOriginPoint().GetY(), rectangle.GetOriginPoint().GetX(), rectangle.GetEndPoint().GetY() };
    edges[LEFT_EDGE].normal = LEFT_DIRECTION;
    edges[BOTTOM_EDGE].edge = { rectangle.GetOriginPoint().GetX(), rectangle.GetEndPoint().GetY(), rectangle.GetEndPoint().GetX(), rectangle.GetEndPoint().GetY() };
    edges[BOTTOM_EDGE].normal = DOWN_DIRECTION;
    edges[RIGHT_EDGE].edge = { rectangle.GetEndPoint().GetX(), rectangle.GetOriginPoint().GetY(), rectangle.GetEndPoint().GetX(), rectangle.GetEndPoint().GetY() };
    edges[RIGHT_EDGE].normal = RIGHT_DIRECTION;
    if (reverseNormals)
    {
        for (auto &edge : edges)
        {
            // Negate the normal if it is reversed
            edge.normal = -edge.normal;
        }
    }
}
