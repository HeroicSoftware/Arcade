//============================================================================
// Name        : HeroicArcade.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include "SDL2/SDL.h"
const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "[ERROR] - SDL_Init Failed" << std::endl;
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow("VillainTech", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (window == nullptr)
    {
        std::cout << "[ERROR] - Could not create window, SDL Error: "
                  << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_Event event;
    bool isRunning = true;
    while (isRunning == true)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                isRunning = false;
                break;
            default:
                break;
            }
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
