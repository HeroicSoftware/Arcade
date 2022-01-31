/*
 * Screen.h
 *
 *  Created on: Dec 13, 2021
 *      Author: Jordan
 */

#ifndef GRAPHICS_SCREEN_H_
#define GRAPHICS_SCREEN_H_
#include <cassert>
#include <SDL2/SDL.h>
#include <stdint.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include "AxisAlignedRectangle.h"
#include "Circle.h"
#include "Color.h"
#include "Line2D.h"
#include "ScreenBuffer.h"
#include "Triangle.h"
#include "Utility.h"
#include "Vector2D.h"
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
    void Draw(const Line2D &line2D, const Color &color);
    void Draw(const Triangle &triangle, const Color &color, bool isFilled = false, const Color &fillColor = Color::White());
    void Draw(const AxisAlignedRectangle &rectangle, const Color &color, bool isFilled = false, const Color &fillColor = Color::White());
    void Draw(const Circle &circle, const Color &color, bool isFilled = false, const Color &fillColor = Color::White());

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
    void FillPolygon(const std::vector<Vector2D> &points, const Color &color);
};
#endif /* GRAPHICS_SCREEN_H_ */
