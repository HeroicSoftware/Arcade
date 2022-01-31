/*
 * Screen.cpp
 *
 *  Created on: Dec 13, 2021
 *      Author: Jordan
 */
#include <Screen.h>
Screen::Screen() : width(0), height(0), window(nullptr), windowSurface(nullptr)
{
    // TODO Auto-generated constructor stub
}
Screen::~Screen()
{
    // Destroy the window I created
    if (window)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}
SDL_Window *Screen::Initialize(uint32_t width, uint32_t height, uint32_t windowScale)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "[Screen.cpp] - [ERROR] - SDL_Init Failed" << std::endl;
    }
    this->width = width;
    this->height = height;
    // Create the window
    window = SDL_CreateWindow("Gallant Electronic Systems Interactive Entertainment Cabinet", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width * windowScale, this->height * windowScale, 0);
    // If there is no error creating the window get the surface from that window
    if (window)
    {
        // Get the surface from the window
        windowSurface = SDL_GetWindowSurface(window);
        SDL_PixelFormat *pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
        Color::InitializeColorFormat(pixelFormat);
        this->clearColor = Color::NostalgiaBlue();
        // Create and clear the backBuffer
        backBuffer.Initialize(pixelFormat->format, this->width, this->height);
        backBuffer.Clear(this->clearColor);
    }
    // If there is an error creating the windows
    else
    {
        std::cout << "[Screen.cpp] - [ERROR] - Could not create window, SDL Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    return window;
}
void Screen::SwapScreen()
{
    assert(window);
    // Check if the window is initialized
    if (window)
    {
        ClearScreen();
        // Copy from one surface to another
        SDL_BlitScaled(backBuffer.GetSurface(), nullptr, windowSurface, nullptr);
        // Update the surface after the draw
        SDL_UpdateWindowSurface(window);
        // Clear the backBuffer for next swap
        backBuffer.Clear(clearColor);
    }
    else
    {
        std::cout << "[Screen.cpp] - [ERROR] - Unable to SwapScreen() window not initialized" << std::endl;
    }
}
void Screen::Draw(int x, int y, const Color &color)
{
    assert(window);
    if (window)
    {
        // Draw the color
        backBuffer.SetPixel(color, x, y);
    }
    else
    {
        std::cout << "[Screen.cpp] - [ERROR] - Unable to Draw()  window not initialized" << std::endl;
    }
}
void Screen::Draw(const Vector2D &vector2D, const Color &color)
{
    // Check if there is a window, if so draw the Vector with the color
    assert(window);
    if (window)
    {
        // Draw the color
        backBuffer.SetPixel(color, vector2D.GetX(), vector2D.GetY());
    }
    else
    {
        std::cout << "[Screen.cpp] - [ERROR] - Unable to Draw()  window not initialized" << std::endl;
    }
}
void Screen::Draw(const AxisAlignedRectangle &rectangle, const Color &color, bool isFilled, const Color &fillColor)
{
    if (isFilled == true)
    {
        FillPolygon(rectangle.GetPoints(), fillColor);
    }
    std::vector<Vector2D> rectanglePoints = rectangle.GetPoints();
    Line2D point0ToPoint1 = Line2D(rectanglePoints[0], rectanglePoints[1]);
    Line2D point1ToPoint2 = Line2D(rectanglePoints[1], rectanglePoints[2]);
    Line2D point2ToPoint3 = Line2D(rectanglePoints[2], rectanglePoints[3]);
    Line2D point3ToPoint0 = Line2D(rectanglePoints[3], rectanglePoints[0]);
    Draw(point0ToPoint1, color);
    Draw(point1ToPoint2, color);
    Draw(point2ToPoint3, color);
    Draw(point3ToPoint0, color);
}
void Screen::ClearScreen()
{
    // Check there is a window if so, clear the screen
    if (window)
    {
        SDL_FillRect(windowSurface, nullptr, clearColor.GetPixelColor());
    }
    else
    {
        std::cout << "[Screen.cpp] - [ERROR] - Unable to ClearScreen() window not initialized" << std::endl;
    }
}
void Screen::Draw(const Line2D &line2D, const Color &color)
{
    assert(window);
    // Check there is a window if so, draw the line
    if (window)
    {
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
        if (run >= rise)
        {
            // Go along with the X
            int decision = rise - run / 2;
            while (x0 != x1)
            {
                if (decision >= 0)
                {
                    decision -= run;
                    y0 += incrementY;
                }
                decision += rise;
                x0 += incrementX;
                Draw(x0, y0, color);
            }
        }
        else
        {
            // Go along with the Y
            int decision = run - rise / 2;
            while (y0 != y1)
            {
                if (decision >= 0)
                {
                    decision -= rise;
                    x0 += incrementX;
                }
                decision += run;
                y0 += incrementY;
                Draw(x0, y0, color);
            }
        }
    }
    else
    {
        std::cout << "[Screen.cpp] - [ERROR] - Unable to Draw() window not initialized" << std::endl;
    }
}
void Screen::Draw(const Triangle &triangle, const Color &color, bool isFilled, const Color &fillColor)
{
    if (isFilled == true)
    {
        FillPolygon(triangle.GetPoints(), fillColor);
    }
    Line2D point0TPoint1 = Line2D(triangle.GetPoint0(), triangle.GetPoint1());
    Line2D point1ToPoint2 = Line2D(triangle.GetPoint1(), triangle.GetPoint2());
    Line2D point2ToPoint0 = Line2D(triangle.GetPoint2(), triangle.GetPoint0());
    Draw(point0TPoint1, color);
    Draw(point1ToPoint2, color);
    Draw(point2ToPoint0, color);
}
void Screen::Draw(const Circle &circle, const Color &color, bool isFilled, const Color &fillColor)
{
    static unsigned int NUMBER_OF_CIRCLE_SEGMENTS = 30;
    std::vector<Vector2D> circlePoints;
    std::vector<Line2D> lines;
    float angle = TWO_PI / float(NUMBER_OF_CIRCLE_SEGMENTS);
    // Move point0 and point1 around the circle and draw lines between them
    Vector2D point0 = Vector2D(circle.GetCenterPoint().GetX() + circle.GetRadius(), circle.GetCenterPoint().GetY());
    Vector2D point1 = point0;
    Line2D nextLineToDraw;
    for (unsigned int i = 0; i < NUMBER_OF_CIRCLE_SEGMENTS; i++)
    {
        // Rotate about the the center
        point1.Rotate(angle, circle.GetCenterPoint());
        nextLineToDraw.SetPoint1(point1);
        nextLineToDraw.SetPoint0(point0);
        lines.push_back(nextLineToDraw);
        // Set point0 to the point1 for the next iteration
        point0 = point1;
        circlePoints.push_back(point0);
    }
    if (isFilled == true)
    {
        FillPolygon(circlePoints, fillColor);
    }
    else
    {
        for (const Line2D &line : lines)
        {
            Draw(line, color);
        }
    }
}
void Screen::FillPolygon(const std::vector<Vector2D> &points, const Color &color)
{
    if (points.size() > 0)
    {
        float top = points[0].GetY();
        float bottom = points[0].GetY();
        float right = points[0].GetX();
        float left = points[0].GetX();
        // Find the most extreme points on the polygon
        for (size_t i = 1; i < points.size(); i++)
        {
            if (points[i].GetY() < top)
            {
                top = points[i].GetY();
            }
            if (points[i].GetY() > bottom)
            {
                bottom = points[i].GetY();
            }
            if (points[i].GetX() < left)
            {
                left = points[i].GetX();
            }
            if (points[i].GetX() > right)
            {
                right = points[i].GetX();
            }
        }
        // Go through polygon top to bottom
        for (int pixelY = top; pixelY < bottom; pixelY++)
        {
            std::vector<float> nodeXVector;
            size_t j = points.size() - 1;
            for (size_t i = 0; i < points.size(); i++)
            {
                float pointIY = points[i].GetY();
                float pointJY = points[j].GetY();
                if ((pointIY <= (float)pixelY && pointJY > (float)pixelY) || (pointJY <= (float)pixelY && pointIY > (float)pixelY))
                {
                    float denominator = pointJY - pointIY;
                    if (IsEqual(denominator, 0))
                    {
                        continue;
                    }
                    else
                    {
                        float x = points[i].GetX() + (pixelY - pointIY) / (denominator) * (points[j].GetX() - points[i].GetX());
                        nodeXVector.push_back(x);
                    }
                }
                j = i;
            }
            std::sort(nodeXVector.begin(), nodeXVector.end(), std::less<>());
            for (size_t k = 0; k < nodeXVector.size(); k += 2)
            {
                if (nodeXVector[k] > right)
                {
                    break;
                }
                // Bound X values so they don't go out of bounds
                if (nodeXVector[k + 1] > left)
                {
                    if (nodeXVector[k] < left)
                    {
                        nodeXVector[k] = left;
                    }
                    if (nodeXVector[k + 1] > right)
                    {
                        nodeXVector[k + 1] = right;
                    }
                    // Draw the line
                    for (int pixelX = nodeXVector[k]; pixelX < nodeXVector[k + 1]; pixelX++)
                    {
                        Draw(pixelX, pixelY, color);
                    }
                }
            }
        }
    }
}
