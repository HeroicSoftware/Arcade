/*
 * InputAction.h
 *
 *  Created on: Jan 17, 2022
 *      Author: Jordan Hunt
 */

#ifndef INPUT_INPUTACTION_H_
#define INPUT_INPUTACTION_H_
#include <functional>
#include <stdint.h>
/*
 * Abstraction over SDL input
 */
// Type def
using InputKey = uint8_t;
using InputState = uint8_t;
using MouseButton = uint8_t;
// Any InputAction will be of this type
using InputAction = std::function<void(uint32_t deltaTime, InputState)>;

// Map button to key and action related to that key press
struct ButtonAction
{
    InputKey key;
    InputAction action;
};
struct MousePosition
{
    int32_t xPosition;
    int32_t yPosition;
};
// If mouse is moved
using MouseMovedAction = std::function<void(const MousePosition &mousePosition)>;
// If mouse is clicked
using MouseInputAction = std::function<void(InputState mouseState, const MousePosition &mousePosition)>;

struct MouseButtonAction
{
    MouseButton mouseButton;
    MouseInputAction mouseInputAction;
};

#endif /* INPUT_INPUTACTION_H_ */
