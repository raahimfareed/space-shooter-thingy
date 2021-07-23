#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <cstdlib>
#include <deque>

#include "Entity.hpp"
#include "Enemy.hpp"
#include "EnemyBullet.hpp"

Enemy::Enemy(SDL_Texture* pTexture)
    :mAlive(true), mDirectionRight(rand() % 2), mDirectionDown(rand() % 2), mVelocity(Vector2f(5.f, 5.f))
{
    mpTexture = pTexture;
    mPosition = Vector2f((rand() % (WIDTH - 84)) + 20, 20);
    mCurrentFrame.x = 0;
    mCurrentFrame.y = 0;
    mCurrentFrame.w = 64;
    mCurrentFrame.h = 64;
}

Enemy::Enemy(std::vector<Enemy>& enemies, SDL_Texture* pTexture)
    :mAlive(true), mDirectionRight(rand() % 2), mDirectionDown(rand() % 2), mVelocity(Vector2f(5.f, 5.f))
{
    mpTexture = pTexture;

    Vector2f position = Vector2f((rand() % (WIDTH - 84)) + 20, 20);

    bool collision;
    int count = 0;

    do
    {
        collision = false;
        count++;

        for (Enemy& e: enemies)
        {
            if (e.rGetPosition() == position)
            {
                collision = true;
                position.mX = (rand() % (WIDTH - 84)) + 20;
            }
        }
    } while (collision && count < 3);


    mPosition = position;
    mCurrentFrame.x = 0;
    mCurrentFrame.y = 0;
    mCurrentFrame.w = 64;
    mCurrentFrame.h = 64;
}

void Enemy::update()
{
    if (mDirectionRight)
    {
        if (!(mPosition.mX + ((rand() % (int)mVelocity.mX) + 1) > WIDTH - 84))
        {
            mPosition.mX += ((rand() % (int)mVelocity.mX) + 1);
        }
        else
        {
            mDirectionRight = rand() % 2;
        }
    }
    else
    {
        if (!(mPosition.mX - ((rand() % (int)mVelocity.mX) + 1) < 20))
        {
            mPosition.mX -= ((rand() % (int)mVelocity.mX) + 1);
        }
        else
        {
            mDirectionRight = rand() % 2;
        }
    }

    if (mDirectionDown)
    {
        if (!(mPosition.mY + ((rand() % (int)mVelocity.mY) + 1) > HEIGHT / 2))
        {
            mPosition.mY += ((rand() % (int)mVelocity.mY) + 1);
        }
        else
        {
            mDirectionDown = rand() % 2;
        }
    }
    else
    {
        if (!(mPosition.mY - ((rand() % (int)mVelocity.mY) + 1) < 20))
        {
            mPosition.mY -= ((rand() % (int)mVelocity.mY) + 1);
        }
        else
        {
            mDirectionDown = rand() % 2;
        }
    }
}

bool Enemy::isAlive() const
{
    return mAlive;
}

void Enemy::setAlive(bool alive)
{
    mAlive = alive;
}

void Enemy::fire(SDL_Texture* pTexture, std::deque<EnemyBullet> &rBullets)
{
    rBullets.push_back(EnemyBullet(pTexture, mPosition));
}

