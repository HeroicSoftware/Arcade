/*
 * ScreenBuffer.h
 *
 *  Created on: Dec 12, 2021
 *      Author: Jordan
 */

#ifndef GRAPHICS_SCREENBUFFER_H_
#define GRAPHICS_SCREENBUFFER_H_

#include <stdint.h>
#include <Color.h>
#include <SDL2/SDL.h>
#include <cassert>
struct SDL_Surface;

class ScreenBuffer
{
public:
    ScreenBuffer();
    ScreenBuffer(const ScreenBuffer &screenBuffer);
    ScreenBuffer &operator=(const ScreenBuffer &screenBuffer);
    virtual ~ScreenBuffer();

    inline SDL_Surface *GetSurface()
    {
        return (this->surface);
    }
    void Initialize(uint32_t format, uint32_t width, uint32_t height);
    void Clear(const Color &color = Color::Black());
    void SetPixel(const Color &color, int x, int y);

private:
    SDL_Surface *surface;
    uint32_t GetIndex(int row, int colmun);
};

#endif /* GRAPHICS_SCREENBUFFER_H_ */
