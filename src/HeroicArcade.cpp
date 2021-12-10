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
void SetPixel(SDL_Surface *surface, int color, int x, int y);
size_t GetIndex(SDL_Surface *surface, int row, int colmun);
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
    // Canvas where all the drawing and updates will be made
    SDL_Surface *windowSurface = SDL_GetWindowSurface(window);
    int drawColor = 0xFF0000;
    SetPixel(windowSurface, drawColor, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    // Update the surface after the draw
    SDL_UpdateWindowSurface(window);
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
void SetPixel(SDL_Surface *surface, int color, int x, int y)
{
    // Nothing can access the surface at this moment
    SDL_LockSurface(surface);
    int *pixels = (int *)surface->pixels;
    size_t pixelIndex = GetIndex(surface, y, x);
    pixels[pixelIndex] = color;
    SDL_UnlockSurface(surface);
}
size_t GetIndex(SDL_Surface *surface, int row, int colmun)
{
    return (row * surface->w + colmun);
}
