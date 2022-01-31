/*
 * InputController.h
 *
 *  Created on: Jan 17, 2022
 *      Author: Jordan Hunt
 */

#ifndef INPUT_INPUTCONTROLLER_H_
#define INPUT_INPUTCONTROLLER_H_
#include "InputAction.h"
#include "SDL2/SDL.h"
#include "GameController.h"

class InputController
{
public:
    InputController();
    void Initialize(InputAction quitAction);
    void Update(uint32_t deltaTime);
    void SetGameController(GameController *gameController);
    virtual ~InputController();

private:
    InputAction quitGame;
    GameController *currentController;
};

#endif /* INPUT_INPUTCONTROLLER_H_ */
