/*
 * Screen.cpp
 *
 *  Created on: Dec 13, 2021
 *      Author: Jordan
 */
#include <Screen.h>
Screen::Screen() : width(0), height(0), window(nullptr), windowSurface(nullptr) {
    // TODO Auto-generated constructor stub
}
Screen::~Screen() {
    // Destroy the window I created
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}
SDL_Window* Screen::Initialize(uint32_t width, uint32_t height, uint32_t windowScale) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO)) {
        std::cout << "[ERROR] - SDL_Init Failed" << std::endl;
    }
    this->width = width;
    this->height = height;
    // Create the window
    window = SDL_CreateWindow("GallantGameEngine", SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, this->width * windowScale, this->height * windowScale, 0);
    // If there is no error creating the window get the surface from that window
    if (window) {
        // Get the surface from the window
        windowSurface = SDL_GetWindowSurface(window);
        SDL_PixelFormat *pixelFormat = windowSurface->format;
        Color::InitializeColorFormat(pixelFormat);
        this->clearColor = Color::NostalgiaBlue();
        // Create and clear the backBuffer
        backBuffer.Initialize(pixelFormat->format, this->width, this->height);
        backBuffer.Clear(this->clearColor);
    }
    // If there is an error creating the windows
    else {
        std::cout << "[ERROR] - Could not create window, SDL Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    return window;
}
void Screen::SwapScreen() {
    assert(window);
    // Check if the window is initialized
    if (window) {
        ClearScreen();
        // Copy from one surface to another
        SDL_BlitScaled(backBuffer.GetSurface(), nullptr, windowSurface, nullptr);
        // Update the surface after the draw
        SDL_UpdateWindowSurface(window);
        // Clear the backBuffer for next swap
        backBuffer.Clear(clearColor);
    }
    else {
        std::cout << "[ERROR] - Unable to SwapScreen() window not initialized" << std::endl;
    }
}
void Screen::Draw(int x, int y, const Color &color) {
    assert(window);
    if (window) {
        // Draw the color
        backBuffer.SetPixel(color, x, y);
    }
    else {
        std::cout << "[ERROR] - Unable to Draw()  window not initialized" << std::endl;
    }
}
void Screen::Draw(const Vector2D &vector2D, const Color &color) {
    // Check if there is a window, if so draw the Vector with the color
    assert(window);
    if (window) {
        // Draw the color
        backBuffer.SetPixel(color, vector2D.GetX(), vector2D.GetY());
    }
    else {
        std::cout << "[ERROR] - Unable to Draw()  window not initialized" << std::endl;
    }
}
void Screen::ClearScreen() {
    // Check there is a window if so, clear the screen
    if (window) {
        SDL_FillRect(windowSurface, nullptr, clearColor.GetPixelColor());
    }
    else {
        std::cout << "[ERROR] - Unable to ClearScreen() window not initialized" << std::endl;
    }
}

void Screen::Draw(const Line2D &line2D, const Color &color) {
    assert(window);
    // Check there is a window if so, draw the line
    if (window) {
        int run;
        int rise;
        int x0 = roundf(line2D.GetPoint0().GetX());
        int x1 = roundf(line2D.GetPoint1().GetX());
        int y0 = roundf(line2D.GetPoint0().GetY());
        int y1 = roundf(line2D.GetPoint1().GetY());

        // Find the slope
        run = x1 - x0;
        rise = y1 - y0;
        signed const char incrementX((run > 0) - (run < 0)); // Evaluate to 1 or -1
        signed const char incrementY((rise > 0) - (rise < 0));

        // Get read of floating point math
        run = abs(run) * 2;
        rise = abs(rise) * 2;
        Draw(x0, y0, color);
        if (run >= rise) {
            // Go along with the X
            int decision = rise - run / 2;
            while (x0 != x1) {
                if (decision >= 0) {
                    decision -= run;
                    y0 += incrementY;
                }
                decision += rise;
                x0 += incrementX;
                Draw(x0, y0, color);
            }
        }
        else {
            // Go along with the Y
            int decision = run - rise / 2;
            while (y0 != y1) {
                if (decision >= 0) {
                    decision -= rise;
                    x0 += incrementX;
                }
                decision += run;
                y0 += incrementY;
                Draw(x0, y0, color);
            }
        }
    }
    else {
        std::cout << "[ERROR] - Unable to Draw() window not initialized" << std::endl;
    }
}
