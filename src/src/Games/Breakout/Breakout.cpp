/*
 * Breakout.cpp
 *
 *  Created on: Jan 30, 2022
 *      Author: Jordan Hunt
 */
#include "Breakout.h"
void Breakout::Update(uint32_t deltaTime)
{
    playerPaddle.Update(deltaTime, gameBall);
    gameBall.Update(deltaTime);
    BoundaryEdge edge;
    // If there is a bounce exit the update
    if (playerPaddle.Bounce(gameBall))
    {
        std::cout << "[Breakout.cpp] - [UPDATE] - [Ball bounce with playerPaddle]" << std::endl;
        return;
    }
    if (levelBoundary.HasCollided(gameBall, edge))
    {
        gameBall.Bounce(edge);
        std::cout << "[Breakout.cpp] - [UPDATE] - [Ball bounce with wall]" << std::endl;
        return;
    }
    level.Update(deltaTime, gameBall);
    std::cout << "[Breakout.cpp] - [UPDATE]" << std::endl;
}
void Breakout::Draw(Screen &screen)
{
    std::cout << "[Breakout.cpp] - [DRAW]" << std::endl;
    playerPaddle.Draw(screen);
    gameBall.Draw(screen);
    level.Draw(screen);
    screen.Draw(levelBoundary.GetAxisAlignedRectangle(), Color::NostalgiaBlue());
}
const std::string &Breakout::GetName() const
{
    static std::string name = "Block Breaker SDL-X";
    return name;
}
void Breakout::Initialize(GameController &gameController)
{
    std::cout << "[Breakout.cpp] - [INITIALIZE]" << std::endl;
    gameController.ClearAllActions();
    ResetGame();
    ButtonAction leftKeyAction;
    ButtonAction rightKeyAction;
    leftKeyAction.key = GameController::LeftKey();
    rightKeyAction.key = GameController::RightKey();
    leftKeyAction.action = [this](uint32_t deltaTime, InputState state)
    {
        if (GameController::IsButtonPressed(state))
        {
            playerPaddle.SetMovementDirection(PaddleMovementDirection::LEFT);
            std::cout << "[Breakout.cpp] - [LEFT KEY PRESSED]" << std::endl;
        }
        else
        {
            playerPaddle.UnsetMovementDirection(PaddleMovementDirection::LEFT);
        }
    };
    rightKeyAction.action = [this](uint32_t deltaTime, InputState state)
    {
        if (GameController::IsButtonPressed(state))
        {
            playerPaddle.SetMovementDirection(PaddleMovementDirection::RIGHT);
            std::cout << "[Breakout.cpp] - [RIGHT KEY PRESSED]" << std::endl;
        }
        else
        {
            playerPaddle.UnsetMovementDirection(PaddleMovementDirection::RIGHT);
        }
    };
    gameController.AddInputActionForKey(rightKeyAction);
    gameController.AddInputActionForKey(leftKeyAction);
}
void Breakout::ResetGame()
{
    AxisAlignedRectangle paddleRectangle = {Vector2D((Application::Singleton().GetWidth() / 2) - (Paddle::WIDTH / 2), (Application::Singleton().GetHeight()) - (3 * Paddle::HEIGHT)), Paddle::WIDTH, Paddle::HEIGHT};
    AxisAlignedRectangle levelBoundaryRectangle = {Vector2D::Zero, Application::Singleton().GetWidth(), Application::Singleton().GetHeight()};
    // Create level boundary
    levelBoundary = {levelBoundaryRectangle};
    playerPaddle.Initialize(paddleRectangle, levelBoundaryRectangle);
    gameBall.MoveTo(Vector2D(Application::Singleton().GetWidth() / 2, Application::Singleton().GetHeight() / 2));
    gameBall.SetVelocity(INITIAL_BALL_VELOCITY);
    level.Initialize(levelBoundaryRectangle);
}
