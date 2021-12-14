/*
 * Color.cpp
 *
 *  Created on: Dec 11, 2021
 *      Author: Jordan
 */
#include "Color.h"
#include <SDL2/SDL.h>
const SDL_PixelFormat *Color::pixelFormat = nullptr;
void Color::InitializeColorFormat(const SDL_PixelFormat *pixelFormat)
{
    Color::pixelFormat = pixelFormat;
}
Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    SetRGBA(red, green, blue, alpha);
}
Color::~Color()
{
    // TODO Auto-generated destructor stub
}
uint8_t Color::GetAlpha() const
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
    SDL_GetRGBA(this->color, pixelFormat, &red, &green, &blue, &alpha);
    return alpha;
}
void Color::SetAlpha(uint8_t newAlpha)
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
    SDL_GetRGBA(this->color, pixelFormat, &red, &green, &blue, &alpha);
    SetRGBA(red, green, blue, newAlpha);
}
void Color::SetRGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    this->color = SDL_MapRGBA(this->pixelFormat, red, green, blue, alpha);
}
void Color::SetRed(uint8_t newRed)
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
    SDL_GetRGBA(this->color, pixelFormat, &red, &green, &blue, &alpha);
    SetRGBA(newRed, green, blue, alpha);
}
void Color::SetGreen(uint8_t newGreen)
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
    SDL_GetRGBA(this->color, pixelFormat, &red, &green, &blue, &alpha);
    SetRGBA(red, newGreen, blue, alpha);
}
void Color::SetBlue(uint8_t newBlue)
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
    SDL_GetRGBA(this->color, pixelFormat, &red, &green, &blue, &alpha);
    SetRGBA(red, green, newBlue, alpha);
}
uint8_t Color::GetRed() const
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
    SDL_GetRGBA(this->color, pixelFormat, &red, &green, &blue, &alpha);
    return red;
}
uint8_t Color::GetGreen() const
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
    SDL_GetRGBA(this->color, pixelFormat, &red, &green, &blue, &alpha);
    return green;
}
uint8_t Color::GetBlue() const
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
    SDL_GetRGBA(this->color, pixelFormat, &red, &green, &blue, &alpha);
    return blue;
}
