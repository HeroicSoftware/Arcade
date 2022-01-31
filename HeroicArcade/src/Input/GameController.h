/*
 * GameController.h
 *
 *  Created on: Jan 17, 2022
 *      Author: Jordan Hunt
 */

#ifndef INPUT_GAMECONTROLLER_H_
#define INPUT_GAMECONTROLLER_H_
#include "InputAction.h"
#include <vector>
#include <SDL2/SDL.h>
class GameController
{
public:
    GameController();
    virtual ~GameController();
    InputAction GetActionForKey(InputKey key);
    void AddInputActionForKey(const ButtonAction &buttonAction);
    void ClearAllActions();
    static bool IsButtonPressed(InputState state);
    static bool IsButtonReleased(InputState state);
    // Old-school NES style controller
    static InputKey ActionKey(); // A button
    static InputKey CancelKey(); // B button
    static InputKey LeftKey();   // D-pad Left
    static InputKey RightKey();  // D-pad Right
    static InputKey UpKey();     // D-pad Up
    static InputKey DownKey();   // D-pad Down
    // Mouse
    inline MouseMovedAction &GetMouseMovedAction()
    {
        return mouseMovedAction;
    }
    inline void SetMouseMovedAction(const MouseMovedAction &mouseMovedAction)
    {
        this->mouseMovedAction = mouseMovedAction;
    }
    MouseInputAction GetMouseButtonActionForMouseButtonClick(MouseButton mouseButton);
    void AddMouseButtonActionForMouse(const MouseButtonAction &mouseButtonAction);
    // Three Button Mouse
    static MouseButton LeftMouseButton();
    static MouseButton RightMouseButton();
    static MouseButton MiddleMouseButton();

private:
    std::vector<ButtonAction> buttonActions;
    std::vector<MouseButtonAction> mouseButtonActions;
    MouseMovedAction mouseMovedAction;
};

#endif /* INPUT_GAMECONTROLLER_H_ */
