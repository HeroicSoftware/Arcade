/*
 * BreakoutGameLevel.h
 *
 *  Created on: Mar 6, 2022
 *      Author: Jordan Hunt
 */

#ifndef GAMES_BREAKOUT_BREAKOUTGAMELEVEL_H_
#define GAMES_BREAKOUT_BREAKOUTGAMELEVEL_H_

#include "Block.h"
#include <vector>
#include <stdint.h>
#include "Screen.h"
#include "Ball.h"
#include "AxisAlignedRectangle.h"
class BreakoutGameLevel
{
    public:
        BreakoutGameLevel();
        void Initialize(const AxisAlignedRectangle &boundary);
        void Load(const std::vector<Block> &blocks);
        void Update(uint32_t deltaTime, Ball &ball);
        void Draw(Screen &screen);

    private:
        static const int BLOCK_WIDTH = 40;
        static const int BLOCK_HEIGHT = 20;
        std::vector<Block> blocks;
        void CreateDefaultTestLevel(const AxisAlignedRectangle &boundary);
};

#endif /* GAMES_BREAKOUT_BREAKOUTGAMELEVEL_H_ */
