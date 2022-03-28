/*
 * LevelBoundary.h
 *
 *  Created on: Feb 20, 2022
 *      Author: Jordan Hunt
 */

#ifndef GAMES_BREAKOUT_LEVELBOUNDARY_H_
#define GAMES_BREAKOUT_LEVELBOUNDARY_H_
#include "Excluder.h"
#include "Ball.h"
class LevelBoundary
{
    public:
        LevelBoundary();
        LevelBoundary(const AxisAlignedRectangle &boundaryRectangle);
        bool HasCollided(const Ball &ball, BoundaryEdge &edge);
        const AxisAlignedRectangle GetAxisAlignedRectangle() const
        {
            return (includer.GetRectangle());
        }
    private:
        bool HasCollidedWithEdge(const Ball &ball, const BoundaryEdge &edge) const;
        Excluder includer;
};

#endif /* GAMES_BREAKOUT_LEVELBOUNDARY_H_ */
