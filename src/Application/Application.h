/*
 * Application.h
 *
 *  Created on: Jan 9, 2022
 *      Author: Jordan Hunt
 */

#ifndef APPLICATION_APPLICATION_H_
#define APPLICATION_APPLICATION_H_
#include <SDL2/SDL.h>
#include <stdint.h>
#include <iostream>
#include "Screen.h"
#include <memory>
#include <vector>
#include "Scene.h"
#include <cassert>
#include "InputController.h"
// Forward Declare
struct SDL_Window;

class Application
{
public:
    static Application &Singleton();
    bool Initialize(uint32_t width, uint32_t height, uint32_t magnification);
    void Run();
    inline uint32_t GetWidth() const
    { 
        return applicationScreen.GetWidth();
    }
    inline uint32_t GetHeight() const
    {
        return applicationScreen.GetHeight();
    }
    void PushScene(std::unique_ptr<Scene> scene);
    void PopScene();
    Scene *PeekScene();
    static const std::string &GetBasePath();

private:

    Screen applicationScreen;
    InputController applicationInputController;
    SDL_Window *applicationWindow;
    // Load all the scenes into a stack
    std::vector<std::unique_ptr<Scene>> sceneStack;
};
#endif /* APPLICATION_APPLICATION_H_ */
