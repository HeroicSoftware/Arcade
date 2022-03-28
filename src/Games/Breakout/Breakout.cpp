/*
 * Breakout.cpp
 *
 *  Created on: Jan 30, 2022
 *      Author: Jordan Hunt
 */
#include "Breakout.h"
void Breakout::Update(uint32_t deltaTime)
{
    if (currentGameState == SERVE_STATE)
    {
        playerPaddle.Update(deltaTime, gameBall);
        SetToServeState();
        std::cout << "[Breakout.cpp] - [UPDATE] - {SERVE_STATE}" << std::endl;
    }
    else if (currentGameState == PLAY_STATE)
    {
        std::cout << "[Breakout.cpp] - [UPDATE] - {PLAY_STATE}" << std::endl;
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
        GetCurrentLevel().Update(deltaTime, gameBall);
        // If the ball goes behind the player paddle don't bounce reduce playerLives
        if (IsBallBeyondBottomScreenBoundsY())
        {
            ReduceLifeByOne();
            if (!IsGameOver())
            {
                SetToServeState();
            }
            else
            {
                std::cout << "[Breakout.cpp] - [UPDATE] - [Game Over]" << std::endl;
                currentGameState = GAME_OVER_STATE;
            }
        }
        // If the current level is complete then move on to the next one
        else if (GetCurrentLevel().IsLevelComplete())
        {
            currentLevel = (currentLevel + 1) % levels.size();
            ResetGame(currentLevel);
        }
    }
    std::cout << "[Breakout.cpp] - [UPDATE]" << std::endl;
}
void Breakout::Draw(Screen &screen)
{
    std::cout << "[Breakout.cpp] - [DRAW]" << std::endl;
    playerPaddle.Draw(screen);
    gameBall.Draw(screen);
    GetCurrentLevel().Draw(screen);
    screen.Draw(levelBoundary.GetAxisAlignedRectangle(), Color::NostalgiaBlue());
    // Draw player lives
    Line2D cutOff{Vector2D(0, bottomScreenYBounds), Vector2D(Application::Singleton().GetWidth(), bottomScreenYBounds)};
    screen.Draw(cutOff, Color::Red());
    Circle lifeCircle = {Vector2D(7, Application::Singleton().GetHeight() - 10), 5};
    for (int i = 0; i < playerLives; i++)
    {
        screen.Draw(lifeCircle, Color::Pink(), true, Color::Pink());
        lifeCircle.MoveByDeltaOffset(Vector2D(20, 0));
    }
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
    levels = BreakoutGameLevel::LoadLevelsFromFile(Application::GetBasePath() + "Assets\\BreakoutLevels.txt");
    ResetGame();

    // Serve the ball
    ButtonAction serveAction;
    serveAction.key = GameController::ActionKey();
    serveAction.action = [this](uint32_t deltaTime, InputState state)
    {
        if (currentGameState == SERVE_STATE)
        {
            if (GameController::IsButtonPressed(state))
            {
                currentGameState = PLAY_STATE;
                if (playerPaddle.IsMovingLeft())
                {
                    gameBall.SetVelocity(Vector2D(-INITIAL_BALL_SPEED, -INITIAL_BALL_SPEED));
                }
                else
                {
                    gameBall.SetVelocity(Vector2D(INITIAL_BALL_SPEED, -INITIAL_BALL_SPEED));
                }
            }
        }
        else if (currentGameState == GAME_OVER_STATE)
        {
            if (GameController::IsButtonPressed(state))
            {
                ResetGame();
            }
        }
    };

    gameController.AddInputActionForKey(serveAction);
    ButtonAction leftKeyAction;
    ButtonAction rightKeyAction;
    leftKeyAction.key = GameController::LeftKey();
    rightKeyAction.key = GameController::RightKey();
    leftKeyAction.action = [this](uint32_t deltaTime, InputState state)
    {
        if (currentGameState == PLAY_STATE || currentGameState == SERVE_STATE)
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
        }
    };
    rightKeyAction.action = [this](uint32_t deltaTime, InputState state)
    {
        if (currentGameState == PLAY_STATE || currentGameState == SERVE_STATE)
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
        }
    };
    gameController.AddInputActionForKey(rightKeyAction);
    gameController.AddInputActionForKey(leftKeyAction);
}
void Breakout::ResetGame(size_t toLevel)
{
    levels = BreakoutGameLevel::LoadLevelsFromFile(Application::GetBasePath() + "Assets\\BreakoutLevels.txt");
    bottomScreenYBounds = Application::Singleton().GetHeight() - (2 * Paddle::HEIGHT);
    playerLives = NUMBER_OF_PLAYER_LIVES;
    currentLevel = toLevel;
    AxisAlignedRectangle paddleRectangle = {Vector2D((Application::Singleton().GetWidth() / 2) - (Paddle::WIDTH / 2), (Application::Singleton().GetHeight()) - (3 * Paddle::HEIGHT)), Paddle::WIDTH, Paddle::HEIGHT};
    AxisAlignedRectangle levelBoundaryRectangle = {Vector2D::Zero, Application::Singleton().GetWidth(), Application::Singleton().GetHeight()};
    // Create level boundary
    levelBoundary = {levelBoundaryRectangle};
    playerPaddle.Initialize(paddleRectangle, levelBoundaryRectangle);
    gameBall.MoveTo(Vector2D(Application::Singleton().GetWidth() / 2, Application::Singleton().GetHeight() * .75f));
    SetToServeState();
}

void Breakout::SetToServeState()
{
    currentGameState = SERVE_STATE;
    gameBall.Stop();
    gameBall.MoveTo(Vector2D(playerPaddle.GetRectangle().GetCenterPoint().GetX(), playerPaddle.GetRectangle().GetOriginPoint().GetY() - gameBall.GetRadius() - 1));
}
bool Breakout::IsBallBeyondBottomScreenBoundsY() const
{
    return (gameBall.GetPosition().GetY() > bottomScreenYBounds);
}
void Breakout::ReduceLifeByOne()
{
    if (playerLives >= 0)
    {
        playerLives--;
    }
}
