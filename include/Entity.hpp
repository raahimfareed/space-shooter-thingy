#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Math.hpp"

class Entity
{
public:
    Entity() = default;
    Entity(Vector2f position, SDL_Texture* pTexture);
    Vector2f& rGetPosition();
    SDL_Texture*& prGetTexture();
    SDL_Rect getCurrentFrame() const;

protected:
    Vector2f mPosition;
    SDL_Rect mCurrentFrame;
    SDL_Texture* mpTexture;
};
