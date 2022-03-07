/*
 * Block.h
 *
 *  Created on: Mar 1, 2022
 *      Author: Jordan Hunt
 */

#ifndef GAMES_BREAKOUT_BLOCK_H_
#define GAMES_BREAKOUT_BLOCK_H_
#include "Excluder.h"
#include "Color.h"
#include "Ball.h"
#include "Screen.h"

class Block : public Excluder
{
public:
    Block();
    virtual ~Block();
    static const int UNBREAKABLE = -1;
    void Initialize(const AxisAlignedRectangle &rectangle, int hitpoints, const Color &outlineColor, const Color &fillColor);
    void Draw(Screen &screen);
    void Bounce(Ball &ball, const BoundaryEdge &boundaryEdge);
    void ReduceHitpoints();
    inline int GetHitpoints() const
    {
        return hitPoints;
    }
    inline bool IsDestroyed() const
    {
        return hitPoints == 0;
    }
    inline const Color &GetOutlineColor() const
    {
        return outlineColor;
    }
    inline const Color &GetFillColor() const
    {
        return fillColor;
    }

private:
    Color outlineColor;
    Color fillColor;
    int hitPoints;
};

#endif /* GAMES_BREAKOUT_BLOCK_H_ */
