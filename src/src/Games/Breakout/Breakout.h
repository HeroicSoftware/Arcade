/*
 * Breakout.h
 *
 *  Created on: Jan 30, 2022
 *      Author: Jordan Hunt
 */

#ifndef GAMES_BREAKOUT_H_
#define GAMES_BREAKOUT_H_
#include "Application.h"
#include "Game.h"
#include "GameController.h"
#include "Paddle.h"
#include "iostream"
#include "Ball.h"
#include "LevelBoundary.h"
#include "BreakoutGameLevel.h"

class Breakout: public Game
{
    public:
        virtual void Update(uint32_t deltaTime) override;
        virtual void Draw(Screen &screen) override;
        virtual const std::string& GetName() const override;
        virtual void Initialize(GameController &gameController) override;

    private:
        void ResetGame();
        Paddle playerPaddle;
        Ball gameBall;
        LevelBoundary levelBoundary;
        BreakoutGameLevel level;
        const Vector2D INITIAL_BALL_VELOCITY = Vector2D(90, 90);
};

#endif /* GAMES_BREAKOUT_H_ */
