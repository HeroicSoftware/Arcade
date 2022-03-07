/*
 * Block.cpp
 *
 *  Created on: Mar 1, 2022
 *      Author: Jordan Hunt
 */

#include <Breakout/Block.h>

Block::Block() : outlineColor(Color::White()), fillColor(Color::White()), hitPoints(1)
{
}

Block::~Block()
{
    // TODO Auto-generated destructor stub
}

void Block::Initialize(const AxisAlignedRectangle &rectangle, int hitpoints, const Color &outlineColor, const Color &fillColor)
{
    Excluder::Initialize(rectangle);
    this->hitPoints = hitPoints;
    this->outlineColor = outlineColor;
    this->fillColor = fillColor;
}

void Block::Draw(Screen &screen)
{
    screen.Draw(GetRectangle(), outlineColor, true, fillColor);
}

void Block::Bounce(Ball &ball, const BoundaryEdge &edge)
{
    ball.Bounce(edge);
}

void Block::ReduceHitpoints()
{
    if (hitPoints > 0)
    {
        hitPoints--;
    }
}
