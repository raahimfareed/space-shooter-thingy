#pragma once
#include <vector>
#include <deque>

#include "Bullet.hpp"

class Player;

class EnemyBullet: public Bullet
{
public:
    EnemyBullet(SDL_Texture* pTexture, Vector2f position);
    void update(std::deque<EnemyBullet> &rBullets, Player &rPlayer);
};
