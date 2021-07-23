#pragma once

struct Vector2f
{
    Vector2f();
    Vector2f(float x, float y);
    void print();
    bool operator == (const Vector2f& v2f) const;

    float mX, mY;
};