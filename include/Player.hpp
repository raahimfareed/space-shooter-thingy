#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <vector>
#include <deque>

#include "Entity.hpp"

class PlayerBullet;

class Player: public Entity
{
public:
    Player(SDL_Texture* pTexture);
    void moveRight();
    void moveLeft();
    void fire(SDL_Texture* pTexture, std::deque<PlayerBullet> &rBullets, Mix_Chunk* &rpSfx);
    int getLives() const;
    void setLives(int lives);

private:
    int mLives;
    bool mFiring;
    Uint32 mLastFire;
    // bool mRespawnShield;
};
