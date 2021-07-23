#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Config.hpp"
#include "Bullet.hpp"
#include "Entity.hpp"

Bullet::Bullet(SDL_Texture* pTexture, Vector2f position)
    :mVelocity(10.0f), mHit(false)
{
    mpTexture = pTexture;
    mPosition = Vector2f(position.mX, position.mY);
    mCurrentFrame.x = 0;
    mCurrentFrame.y = 0;
    mCurrentFrame.w = 64;
    mCurrentFrame.h = 64;
}

bool Bullet::getHit() const
{
    return mHit;
}

