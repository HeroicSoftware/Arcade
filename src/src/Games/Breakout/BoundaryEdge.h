/*
 * BoundaryEdge.h
 *
 *  Created on: Jan 31, 2022
 *      Author: Jordan Hunt
 */

#ifndef GAMES_BREAKOUT_BOUNDARYEDGE_H_
#define GAMES_BREAKOUT_BOUNDARYEDGE_H_

#include "Line2D.h"
#include "Vector2D.h"

enum EdgeType
{
    BOTTOM_EDGE = 0,
    TOP_EDGE,
    LEFT_EDGE,
    RIGHT_EDGE,
    NUMBER_OF_EDGES
};

static const Vector2D UP_DIRECTION = {0, -1};
static const Vector2D DOWN_DIRECTION = {0, 1};
static const Vector2D LEFT_DIRECTION = {-1, 0};
static const Vector2D RIGHT_DIRECTION = {1, 0};

struct BoundaryEdge
{
    Vector2D normal;
    Line2D edge;
};
#endif /* GAMES_BREAKOUT_BOUNDARYEDGE_H_ */
