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
    window = SDL_CreateWindow("VillainTech", SDL_WINDOWPOS_CENTERED,
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
