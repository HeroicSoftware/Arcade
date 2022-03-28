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
#include "Circle.h"
enum BreakOutGameState
{
    PLAY_STATE,
    SERVE_STATE,
    GAME_OVER_STATE
};

class Breakout : public Game
{
public:
    virtual void Update(uint32_t deltaTime) override;
    virtual void Draw(Screen &screen) override;
    virtual const std::string &GetName() const override;
    virtual void Initialize(GameController &gameController) override;

private:
    void ResetGame(size_t toLevel = 0);
    void SetToServeState();
    void ReduceLifeByOne();
    bool IsGameOver() const
    {
        return (playerLives < 0);
    }
    bool IsBallBeyondBottomScreenBoundsY() const;
    BreakoutGameLevel &GetCurrentLevel()
    {
        return (levels[currentLevel]);
    }

    Ball gameBall;
    BreakOutGameState currentGameState;
    const float INITIAL_BALL_SPEED = 90.0f;
    const int NUMBER_OF_PLAYER_LIVES = 3;
    const Vector2D INITIAL_BALL_VELOCITY = Vector2D(90, -90);
    float bottomScreenYBounds;
    int playerLives;
    LevelBoundary levelBoundary;
    Paddle playerPaddle;
    size_t currentLevel;
    std::vector<BreakoutGameLevel> levels;
};

#endif /* GAMES_BREAKOUT_H_ */
