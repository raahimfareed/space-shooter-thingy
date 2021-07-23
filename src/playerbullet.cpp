#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <vector>
#include <deque>

#include "PlayerBullet.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"

PlayerBullet::PlayerBullet(SDL_Texture* pTexture, Vector2f position)
    :Bullet(pTexture, position)
{}

void PlayerBullet::update(std::deque<PlayerBullet> &rBullets, std::vector<Enemy> &rEnemies, Mix_Chunk* &rpSfx)
{
    if (mPosition.mY - mVelocity > -70)
    {
        mPosition.mY -= mVelocity;

        for(Enemy &e: rEnemies)
        {
            if (std::abs(e.rGetPosition().mX - mPosition.mX) < 32 && std::abs(e.rGetPosition().mY - mPosition.mY) < 48 && e.isAlive() && !mHit)
            {
                Mix_PlayChannel(-1, rpSfx, 0);
                e.setAlive(false);
                mHit = true;
            }
        }

    }
    else
    {
        rBullets.pop_front();
    }
}