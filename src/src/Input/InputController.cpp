/*
 * InputController.cpp
 *
 *  Created on: Jan 17, 2022
 *      Author: Jordan Hunt
 */
#include <InputController.h>
InputController::InputController() : quitGame(nullptr), currentController(nullptr)
{
}
void InputController::Initialize(InputAction quitAction)
{
    quitGame = quitAction;
}
void InputController::Update(uint32_t deltaTime)
{
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        switch (sdlEvent.type)
        {
        case SDL_QUIT:
        {
            quitGame(deltaTime, SDL_PRESSED);
        }
        case SDL_MOUSEMOTION:
        {
            if (currentController)
            {
                if (MouseMovedAction mouseMoved = currentController->GetMouseMovedAction())
                {
                    MousePosition position;
                    position.xPosition = sdlEvent.motion.x;
                    position.yPosition = sdlEvent.motion.y;
                    mouseMoved(position);
                }
            }
            break;
        }
        case SDL_MOUSEBUTTONUP:
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (currentController)
            {
                MouseInputAction mouseAction = currentController->GetMouseButtonActionForMouseButtonClick(static_cast<MouseButton>(sdlEvent.button.button));
                MousePosition position;
                position.xPosition = sdlEvent.motion.x;
                position.yPosition = sdlEvent.motion.y;
                mouseAction(static_cast<InputState>(sdlEvent.button.state), position);
            }
            break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            // When the player presses a key, get the action for that key
            if (currentController)
            {
                InputAction action = currentController->GetActionForKey(sdlEvent.key.keysym.sym);
                // Call the action for the action
                action(deltaTime, static_cast<InputState>(sdlEvent.key.state));
            }
            break;
        default:
            break;
        }
    }
}
void InputController::SetGameController(GameController *gameController)
{
    currentController = gameController;
}
InputController::~InputController()
{
    // TODO Auto-generated destructor stub
}
