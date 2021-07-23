#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <vector>
#include <deque>

#include "Bullet.hpp"

class Enemy;

class PlayerBullet: public Bullet
{
public:
    PlayerBullet(SDL_Texture* pTexture, Vector2f position);
    void update(std::deque<PlayerBullet> &rBullets, std::vector<Enemy> &rEnemies, Mix_Chunk* &rpSfx);
};
