#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <deque>

#include "Config.hpp"
#include "Player.hpp"
#include "Math.hpp"
#include "Entity.hpp"
#include "PlayerBullet.hpp"

Player::Player(SDL_Texture* pTexture)
    :Entity(Vector2f(WIDTH / 2 - 32, HEIGHT - (64 + 20)), pTexture), mLives(3), mFiring(false), mLastFire(0)
{}

void Player::moveRight()
{
    if (!(mPosition.mX + VELOCITY_X > WIDTH - (64 + 20)))
    {
        mPosition.mX += VELOCITY_X;
    }

}

void Player::moveLeft()
{
    if (!(mPosition.mX - VELOCITY_X < 20))
    {
        mPosition.mX -= VELOCITY_X;
    }
}

void Player::fire(SDL_Texture* pTexture, std::deque<PlayerBullet> &rBullets, Mix_Chunk* &rpSfx)
{
    mFiring = false;
    if ((float)(SDL_GetTicks() - mLastFire) * 0.001f < 0.5f)
    {
        mFiring = true;
    }

    if (!mFiring)
    {
        rBullets.push_back(PlayerBullet(pTexture, mPosition));
        Mix_PlayChannel(-1, rpSfx, 0);
        mLastFire = SDL_GetTicks();
    }
}

int Player::getLives() const
{
    return mLives;
}

void Player::setLives(int lives)
{
    mLives = lives;
}
