/*
 * ScreenBuffer.cpp
 *
 *  Created on: Dec 12, 2021
 *      Author: Jordan
 */

#include <ScreenBuffer.h>

ScreenBuffer::ScreenBuffer() : surface(nullptr)
{
}

ScreenBuffer::ScreenBuffer(const ScreenBuffer &screenBuffer)
{
    // Create a surface
    this->surface = SDL_CreateRGBSurfaceWithFormat(0, screenBuffer.surface->w, screenBuffer.surface->h, 0,
                                                   screenBuffer.surface->format->format);
    // Copy all the pixel from screenBuffer.surface to surfaces
    SDL_BlitSurface(screenBuffer.surface, nullptr, surface, nullptr);
}
ScreenBuffer::~ScreenBuffer()
{
    if (this->surface)
    {
        SDL_FreeSurface(this->surface);
    }
}
ScreenBuffer &ScreenBuffer::operator=(const ScreenBuffer &screenBuffer)
{
    if (this == &screenBuffer)
    {
        return *this;
    }
    // If surface is not null, free the surface
    if (this->surface != nullptr)
    {
        SDL_FreeSurface(this->surface);
        this->surface = nullptr;
    }

    if (screenBuffer.surface != nullptr)
    {
        // Create a surface
        this->surface = SDL_CreateRGBSurfaceWithFormat(0, screenBuffer.surface->w, screenBuffer.surface->h, 0,
                                                       screenBuffer.surface->format->format);
        // Copy all the pixel from screenBuffer.surface to surfaces
        SDL_BlitSurface(screenBuffer.surface, nullptr, surface, nullptr);
    }
    return *this;
}

void ScreenBuffer::Initialize(uint32_t format, uint32_t width, uint32_t height)
{
    this->surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 0, format);
    this->Clear();
}

void ScreenBuffer::Clear(const Color &color)
{
    assert(this->surface);
    if (surface)
    {
        SDL_FillRect(this->surface, nullptr, color.GetPixelColor());
    }
}

uint32_t ScreenBuffer::GetIndex(int row, int colmun)
{
    assert(this->surface);
    if (this->surface != 0)
    {
        return (row * this->surface->w + colmun);
    }
    else
    {
        return 0;
    }
}

void ScreenBuffer::SetPixel(const Color &color, int x, int y)
{
    assert(this->surface);
    if (this->surface && ((y < this->surface->h) && (y >= 0) && (x >= 0) && (x < this->surface->w)))
    {
        // Nothing can access the surface at this moment
        SDL_LockSurface(this->surface);
        uint32_t *pixels = (uint32_t *)this->surface->pixels;
        size_t pixelIndex = GetIndex(y, x);
        pixels[pixelIndex] = color.GetPixelColor();
        SDL_UnlockSurface(this->surface);
    }
}
