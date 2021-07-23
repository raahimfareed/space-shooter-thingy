#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Entity.hpp"
#include "Math.hpp"

Entity::Entity(Vector2f position, SDL_Texture* pTexture)
    : mPosition(position), mpTexture(pTexture)
{
    mCurrentFrame.x = 0;
    mCurrentFrame.y = 0;
    mCurrentFrame.w = 64;
    mCurrentFrame.h = 64;
}

Vector2f& Entity::rGetPosition()
{
    return mPosition;
}

SDL_Texture*& Entity::prGetTexture()
{
    return mpTexture;
}

SDL_Rect Entity::getCurrentFrame() const
{
    return mCurrentFrame;
}
