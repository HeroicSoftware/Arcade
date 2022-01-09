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
#include "Line2D.h"
#include "Triangle.h"
#include "AxisAlignedRectangle.h"
#include "Circle.h"
const int SCREEN_WIDTH = 224;
const int SCREEN_HEIGHT = 288;
const int WINDOW_SCALE = 3;
int main(int argc, char *argv[])
{
    Screen arcadeScreen;
    arcadeScreen.Initialize(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_SCALE);
    Line2D line2D =
        {Vector2D(0, 0), Vector2D(SCREEN_WIDTH, SCREEN_HEIGHT)};
    Line2D line2D2 =
        {Vector2D(SCREEN_WIDTH, 0), Vector2D(0, SCREEN_HEIGHT)};
    Triangle testTriangle =
        {Vector2D(60, 10), Vector2D(10, 110), Vector2D(110, 110)};
    AxisAlignedRectangle testRectangle =
        {Vector2D(SCREEN_WIDTH / 2 - 25, SCREEN_HEIGHT / 2 - 25), 50, 50};
    Circle testCircle =
        {Vector2D(SCREEN_WIDTH / 2 + 50, SCREEN_HEIGHT / 2 + 50), 50};
    testTriangle.MoveTo(Vector2D((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2)));
    // Draw two lines that will cross as the center of the screen.
    arcadeScreen.Draw(line2D, Color::Red());
    arcadeScreen.Draw(line2D2, Color::Red());
    // Draw the triangle at the new destination
    arcadeScreen.Draw(testTriangle, Color::Orange(), true, Color::Orange());
    // arcadeScreen.Draw(testRectangle, Color::Pink(), true, Color::Pink());
    // arcadeScreen.Draw(testCircle, Color(0,255,0,150), true, Color(0,255,0,150));
    arcadeScreen.SwapScreen();
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
    SDL_Quit();
    return 0;
}
