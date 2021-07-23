#include <iostream>
#include "Math.hpp"

Vector2f::Vector2f()
    : mX(0.0f), mY(0.0f)
{}

Vector2f::Vector2f(float x, float y)
    : mX(x), mY(y)
{}

void Vector2f::print()
{
    printf("X: %f, Y: %f\n", mX, mY);
}

bool Vector2f::operator == (const Vector2f& v2f) const
{
    if (mX == v2f.mX && mY == v2f.mY)
    {
        return true;
    }

    return false;
}
