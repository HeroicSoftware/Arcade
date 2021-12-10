#include <iostream>

class Point2D
{
public:
    Point2D();             // Default constructor
    Point2D(int x, int y); // Non-default constructor
    void SetPosition(int positionX, int positionY);
    void Display();

    Point2D &ReferenceToSelf();
    Point2D *PointerToSelf();

    int GetX() const
    {
        return x;
    }

    void SetX(int x)
    {
        this->x = x;
    }

    int GetY() const
    {
        return y;
    }

    void SetY(int y)
    {
        this->y = y;
    }

private:
    int x;
    int y;
};

