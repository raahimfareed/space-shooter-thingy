#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>
#include <deque>

#include "Config.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include "EnemyBullet.hpp"

EnemyBullet::EnemyBullet(SDL_Texture* pTexture, Vector2f position)
    :Bullet(pTexture, position)
{}

void EnemyBullet::update(std::deque<EnemyBullet> &rBullets, Player &rPlayer)
{
    if (mPosition.mY + mVelocity < HEIGHT + 70)
    {
        mPosition.mY += mVelocity;

        if (std::abs(rPlayer.rGetPosition().mX - mPosition.mX) < 32 && std::abs(rPlayer.rGetPosition().mY - mPosition.mY) < 48 && rPlayer.getLives() > 0 && !mHit)
        {
            rPlayer.setLives(rPlayer.getLives() - 1);
            mHit = true;
        }
    }
    else
    {
        rBullets.pop_front();
    }
}