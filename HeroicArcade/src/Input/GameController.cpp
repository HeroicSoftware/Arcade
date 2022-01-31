/*
 * GameController.cpp
 *
 *  Created on: Jan 17, 2022
 *      Author: Jordan Hunt
 */
#include <GameController.h>
GameController::GameController()
{
    // TODO Auto-generated constructor stub
}
GameController::~GameController()
{
    // TODO Auto-generated destructor stub
}
InputAction GameController::GetActionForKey(InputKey key)
{
    for (const auto &buttonAction : buttonActions)
    {
        if (key == buttonAction.key)
        {
            return buttonAction.action;
        }
    }
    // If there was not a key found return an empty action
    return [](uint32_t, InputState)
    {
    };
}
// Add buttonAction to buttonActions vector
void GameController::AddInputActionForKey(const ButtonAction &buttonAction)
{
    buttonActions.push_back(buttonAction);
}
// Empty all buttonActions from buttonActions vector
void GameController::ClearAllActions()
{
    buttonActions.clear();
}
// Button handling using SDL2/SDL.h for button pressing
bool GameController::IsButtonPressed(InputState state)
{
    return state == SDL_PRESSED;
}
// Button handling using SDL2/SDL.h for button releasing
bool GameController::IsButtonReleased(InputState state)
{
    return state == SDL_RELEASED;
}
// Hardcode action key to its SDL value
InputKey GameController::ActionKey()
{
    // The action key will be 'A'
    return (static_cast<InputKey>(SDLK_a));
}
// Hardcode cancel key to its SDL value
InputKey GameController::CancelKey()
{
    // Cancel key will be 'S'
    return (static_cast<InputKey>(SDLK_s));
}
// Hardcode left arrow key to its SDL value
InputKey GameController::LeftKey()
{
    // D-pad left will be arrow left
    return (static_cast<InputKey>(SDLK_LEFT));
}
// Hardcode right arrow key to its SDL value
InputKey GameController::RightKey()
{
    // D-pad right will be the arrow right
    return (static_cast<InputKey>(SDLK_RIGHT));
}
InputKey GameController::UpKey()
{ // D-pad right will be the arrow up
    return (static_cast<InputKey>(SDLK_RIGHT));
}
InputKey GameController::DownKey()
{ // D-pad down will be the arrow down
    return (static_cast<InputKey>(SDLK_DOWN));
}

MouseInputAction GameController::GetMouseButtonActionForMouseButtonClick(MouseButton mouseButton)
{
    for (const auto &mouseButtonAction : this->mouseButtonActions)
    {
        if (mouseButtonAction.mouseButton == mouseButton)
        {
            return mouseButtonAction.mouseInputAction;
        }
    }
    // If there is no action set for the button then do nothing
    return [](InputState state, const MousePosition &position)
    {
    };
}

void GameController::AddMouseButtonActionForMouse(const MouseButtonAction &mouseButtonAction)
{
    mouseButtonActions.push_back(mouseButtonAction);
}

MouseButton GameController::LeftMouseButton()
{
    return static_cast<MouseButton>(SDL_BUTTON_LEFT);
}

MouseButton GameController::RightMouseButton()
{
    return static_cast<MouseButton>(SDL_BUTTON_RIGHT);
}

MouseButton GameController::MiddleMouseButton()
{
    return static_cast<MouseButton>(SDL_BUTTON_MIDDLE);
}
