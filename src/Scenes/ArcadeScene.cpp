/*
 * ArcadeScene.cpp
 *
 *  Created on: Jan 12, 2022
 *      Author: Jordan Hunt
 */

#include "ArcadeScene.h"

ArcadeScene::ArcadeScene()
{
    // TODO Auto-generated constructor stub
}

ArcadeScene::~ArcadeScene()
{
    // TODO Auto-generated destructor stub
}

void ArcadeScene::Initialize()
{
    // Create a buttonA
    ButtonAction buttonA;
    ButtonAction buttonS;
    // Set the key
    buttonA.key = GameController::ActionKey();
    buttonS.key = GameController::CancelKey();
    // Set the action
    buttonA.action = [](uint32_t deltaTime, InputState state)
    {
        if (GameController::IsButtonPressed(state))
        {
            std::cout << "[ArcadeScene.cpp] - Action button was pressed " << std::endl;
        }
    };
    buttonS.action = [](uint32_t deltaTime, InputState state)
    {
        if (GameController::IsButtonPressed(state))
        {
            std::cout << "[ArcadeScene.cpp] - Cancel button was pressed " << std::endl;
        }
    };
    // Create a mouseActionLeft
    MouseButtonAction mouseActionLeft;
    MouseButtonAction mouseActionMiddle;
    MouseButtonAction mouseActionRight;
    // Set the mouseButton
    mouseActionLeft.mouseButton = GameController::LeftMouseButton(); // Set the mouseActionLeft
    mouseActionLeft.mouseInputAction = [](InputState state, const MousePosition &position)
    {
        if (GameController::IsButtonPressed(state))
        {
            std::cout << "[ArcadeScene.cpp] - Left Mouse button was pressed " << std::endl;
        }
    };
    mouseActionRight.mouseButton = GameController::RightMouseButton(); // Set the mouseActionRight
    mouseActionRight.mouseInputAction = [](InputState state, const MousePosition &position)
    {
        if (GameController::IsButtonPressed(state))
        {
            std::cout << "[ArcadeScene.cpp] - Right Mouse button was pressed " << std::endl;
        }
    };
    mouseActionMiddle.mouseButton = GameController::MiddleMouseButton(); // Set the mouseActionMiddle
    mouseActionMiddle.mouseInputAction = [](InputState state, const MousePosition &position)
    {
        if (GameController::IsButtonPressed(state))
        {
            std::cout << "[ArcadeScene.cpp] - Middle Mouse button was pressed " << std::endl;
        }
    };
    // Set the Action for the key
    gameController.AddInputActionForKey(buttonA);
    gameController.AddInputActionForKey(buttonS);
    // Set the Action for the mouse
    gameController.AddMouseButtonActionForMouse(mouseActionLeft);
    gameController.AddMouseButtonActionForMouse(mouseActionRight);
    gameController.AddMouseButtonActionForMouse(mouseActionMiddle);

    // Mouse movement
    gameController.SetMouseMovedAction([](const MousePosition &mousePosition)
                                       { std::cout << "[ArcadeScene.cpp] - Mouse Position X: " << mousePosition.xPosition << " | Mouse Position Y:  " << mousePosition.yPosition << std::endl; });
}

void ArcadeScene::Update(uint32_t deltaTime)
{
}

void ArcadeScene::Render(Screen &applicationScreen)
{
    // Create the various objects
    Line2D line2D = {Vector2D(0, 0), Vector2D(applicationScreen.GetWidth(), applicationScreen.GetHeight())};
    Line2D line2D2 = {Vector2D(applicationScreen.GetWidth(), 0), Vector2D(0, applicationScreen.GetHeight())};
    Triangle testTriangle = {Vector2D(60, 10), Vector2D(10, 110), Vector2D(110, 110)};
    AxisAlignedRectangle testRectangle = {Vector2D(applicationScreen.GetWidth() / 2 - 25, applicationScreen.GetHeight() / 2 - 25), 50, 50};
    Circle testCircle = {Vector2D(applicationScreen.GetWidth() / 2 + 50, applicationScreen.GetHeight() / 2 + 50), 50};
    testTriangle.MoveTo(Vector2D((applicationScreen.GetWidth() / 2), (applicationScreen.GetHeight() / 2)));

    // Render
    applicationScreen.Draw(line2D, Color::Black());
    applicationScreen.Draw(line2D2, Color::Black());
    applicationScreen.Draw(testTriangle, Color::Orange(), true, Color::Orange());
    applicationScreen.Draw(testRectangle, Color::Pink(), true, Color::Pink());
    applicationScreen.Draw(testCircle, Color(0, 255, 0, 150), true, Color(0, 255, 0, 150));
}

const std::string &ArcadeScene::GetSceneName() const
{
    static std::string sceneName = "Arcade Game Select Scene";
    return sceneName;
}

std::unique_ptr<Scene> ArcadeScene::GetScene(GameList game)
{
    // Start the game based on the Game Selected
    switch (game)
    {
    case TETRIS:
    {
    }
    break;
    case BREAK_OUT:
    {
    }
    break;
    case ASTEROIDS:
    {
    }
    break;
    case HAKMAN:
    {
    }
    break;
    default:
        break;
    }
    return nullptr;
}
