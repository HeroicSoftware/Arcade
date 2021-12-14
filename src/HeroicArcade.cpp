//============================================================================
// Name        : HeroicArcade.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include "SDL2/SDL.h"
#include "Color.h"
#include "Screen.h"
const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int WINDOW_SCALE = 2;
int main(int argc, char *argv[]) {
    Screen arcadeScreen;
    arcadeScreen.Initialize(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_SCALE);
    arcadeScreen.Draw(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, Color::Pink());
    arcadeScreen.SwapScreen();
    SDL_Event event;
    bool isRunning = true;
    while (isRunning == true) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            default:
                break;
            }
        }
    }
    SDL_Quit();
    return 0;
}
