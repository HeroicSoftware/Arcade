/*
 * Screen.h
 *
 *  Created on: Dec 13, 2021
 *      Author: Jordan
 */
#ifndef GRAPHICS_SCREEN_H_
#define GRAPHICS_SCREEN_H_
#include <stdint.h>
#include <SDL2/SDL.h>
#include "ScreenBuffer.h"
#include "Color.h"
#include "Vector2D.h"
#include <cassert>
class Screen
{
public:
    Screen();
    virtual ~Screen();
    SDL_Window *Initialize(uint32_t width, uint32_t height, uint32_t windowScale);
    void SwapScreen();
    inline void SetClear(const Color &clearColor)
    {
        this->clearColor = clearColor;
    }
    inline uint32_t GetWidth() const
    {
        return this->width;
    }
    inline uint32_t GetHeight() const
    {
        return this->height;
    }
    // Draw Methods
    void Draw(int x, int y, const Color &color);
    void Draw(const Vector2D &vector2D, const Color &color);

private:
    // Don't allow copies of this screen
    Screen(const Screen &screen);
    Screen &operator=(const Screen &screen);

    Color clearColor;
    ScreenBuffer backBuffer;
    uint32_t width;
    uint32_t height;
    SDL_Window *window;
    SDL_Surface *windowSurface;
    void ClearScreen();
};
#endif /* GRAPHICS_SCREEN_H_ */
