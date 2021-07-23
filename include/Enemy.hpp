#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>
#include <deque>

#include "Config.hpp"
#include "Entity.hpp"
#include "Math.hpp"

class EnemyBullet;

class Enemy: public Entity
{
public:
    Enemy(SDL_Texture* pTexture);
    Enemy(std::vector<Enemy>& enemies, SDL_Texture* pTexture);
    void update();
    void fire(SDL_Texture* pTexture, std::deque<EnemyBullet> &rBullets);
    bool isAlive() const;
    void setAlive(bool alive);

private:
    bool mAlive;
    bool mDirectionRight;
    bool mDirectionDown;
    Vector2f mVelocity;
};