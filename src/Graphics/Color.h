/*
 * Color.h
 *
 *  Created on: Dec 11, 2021
 *      Author: Jordan Hunt
 */
#ifndef GRAPHICS_COLOR_H_
#define GRAPHICS_COLOR_H_
#include <stdint.h>
// Forward Declaration
struct SDL_PixelFormat;
class Color
{
public:
    static const SDL_PixelFormat *pixelFormat;
    // This function initializes the "pen" in which we will draw the color
    static void InitializeColorFormat(const SDL_PixelFormat *pixelFormat);

    // Blending Equation for AlphaBlending - To make pixels tranparent
    static Color Evaluate1MinusSourceAlpha(const Color &sourceColor, const Color &destinationColor);

    static Color Black()
    {
        return Color(0, 0, 0, 255);
    }
    static Color White()
    {
        return Color(255, 255, 255, 255);
    }
    static Color NostalgiaBlue()
    {
        return Color(100, 149, 237, 255);
    }
    static Color Blue()
    {
        return Color(0, 0, 255, 255);
    }
    static Color Red()
    {
        return Color(255, 0, 0, 255);
    }
    static Color Green()
    {
        return Color(0, 255, 0, 255);
    }
    static Color Yellow()
    {
        return Color(255, 255, 0, 255);
    }
    static Color Magenta()
    {
        return Color(255, 0, 255, 255);
    }
    static Color Cyan()
    {
        return Color(37, 240, 217, 255);
    }
    static Color Pink()
    {
        return Color(255, 192, 203, 255);
    }
    static Color Orange()
    {
        return Color(253, 124, 49, 255);
    }
    Color() : Color(0)
    {
    }
    Color(uint32_t color) : color(color)
    {
    }
    Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
    virtual ~Color();
    inline bool operator==(const Color &otherColor) const
    {
        return (this->color == otherColor.color);
    }
    inline bool operator!=(const Color &otherColor) const
    {
        return !(*this == otherColor.color);
    }
    inline uint32_t GetPixelColor() const
    {
        return this->color;
    }
    uint8_t GetAlpha() const;
    uint8_t GetBlue() const;
    uint8_t GetGreen() const;
    uint8_t GetRed() const;
    void SetAlpha(uint8_t alpha);
    void SetBlue(uint8_t blue);
    void SetGreen(uint8_t green);
    void SetRed(uint8_t red);
    void SetRGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

private:
    uint32_t color;
};
#endif /* GRAPHICS_COLOR_H_ */
