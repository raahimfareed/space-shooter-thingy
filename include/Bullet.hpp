#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Entity.hpp"
#include "Math.hpp"

class Bullet: public Entity
{
public:
    Bullet(SDL_Texture* pTexture, Vector2f position);
    void update();
    bool getHit() const;
protected:
    float mVelocity;
    bool mHit;
};