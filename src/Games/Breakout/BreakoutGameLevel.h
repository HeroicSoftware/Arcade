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
#include "Application.h"
#include "FileCommandLoader.h"
class BreakoutGameLevel
{
public:
    BreakoutGameLevel();
    void Initialize(const AxisAlignedRectangle &boundary);
    void Load(const std::vector<Block> &blocks);
    void Update(uint32_t deltaTime, Ball &ball);
    void Draw(Screen &screen);
    static std::vector<BreakoutGameLevel> LoadLevelsFromFile(const std::string &filePath);
    bool IsLevelComplete() const;

private:
    static const int BLOCK_WIDTH = 20;
    static const int BLOCK_HEIGHT = 5;
    void CreateDefaultTestLevel(const AxisAlignedRectangle &boundary);
    std::vector<Block> blocks;
};

#endif /* GAMES_BREAKOUT_BREAKOUTGAMELEVEL_H_ */
