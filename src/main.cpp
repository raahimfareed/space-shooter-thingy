#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <cstdlib>
#include <deque>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "Config.hpp"
#include "Utils.hpp"
#include "RenderWindow.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "PlayerBullet.hpp"
#include "EnemyBullet.hpp"
#include "KeyboardHandler.hpp"

bool init();

RenderWindow gWindow;

std::map<const char*, SDL_Texture*> gTextures;
std::map<const char*, Mix_Chunk*> gSfx;
std::vector<Enemy> gEnemies;
std::deque<PlayerBullet> gPlayerBullets;
std::deque<EnemyBullet> gEnemyBullets;

bool gQuit;
bool load = init();

Player gPlayer(gTextures["player-ship"]);

int main()
{
    if (!load)
    {
        printf("Program failed to init");
        SDL_Quit();
    }

    SDL_Event events;
    float accumulator = 0.01f;
    float currentTime = utils::hireTimeInSeconds();

    while (!gQuit)
    {
        int startTicks = SDL_GetTicks();

        float newTime = utils::hireTimeInSeconds();
        float frameTime = newTime - currentTime;

        accumulator += frameTime;

        while (accumulator >= TIME_STEP)
        {
            while (SDL_PollEvent(&events))
            {
                switch(events.type)
                {
                    case SDL_QUIT:
                        gQuit = true;
                        break;
                    case SDL_KEYDOWN:
                        KeyboardHandler::handlePressEvent(events);
                        break;
                    case SDL_KEYUP:
                        KeyboardHandler::handleReleaseEvent(events);
                        break;
                }
            }

            accumulator -= TIME_STEP;

            // const float alpha = accumulator / TIME_STEP;

        }

        if (KeyboardHandler::isPressed(SDLK_ESCAPE))
        {
            gQuit = true;
        }

        if (KeyboardHandler::isPressed(SDLK_a))
        {
            gPlayer.moveLeft();
        }

        if (KeyboardHandler::isPressed(SDLK_d))
        {
            gPlayer.moveRight();
        }

        if (KeyboardHandler::isPressed(SDLK_SPACE))
        {
            gPlayer.fire(gTextures["bullet"], gPlayerBullets, gSfx["jump"]);
        }

        for(Enemy &e: gEnemies)
        {
            e.update();

            if (rand() % 119147 < 500 && e.isAlive())
            {
                e.fire(gTextures["bullet-180"], gEnemyBullets);
            }
        }

        for(PlayerBullet &b: gPlayerBullets)
        {
            b.update(gPlayerBullets, gEnemies, gSfx["hit"]);
        }

        for(EnemyBullet &b: gEnemyBullets)
        {
            b.update(gEnemyBullets, gPlayer);
        }

        gWindow.clear();

        for(PlayerBullet &b: gPlayerBullets)
        {
            if (!b.getHit())
            {
                gWindow.render(b);
            }
        }

        for(EnemyBullet &b: gEnemyBullets)
        {
            if (!b.getHit())
            {
                gWindow.render(b);
            }
        }

        gWindow.render(gPlayer);

        for(Enemy &e: gEnemies)
        {
            if (e.isAlive())
            {
                gWindow.render(e);
            }
        }

        gWindow.display();

        int frameTicks = SDL_GetTicks() - startTicks;
        if (frameTicks < 1000 / gWindow.getRefreshRate())
        {
            SDL_Delay(1000 / gWindow.getRefreshRate() - frameTicks);
        }
    }

    gWindow.cleanUp();
    SDL_Quit();

    return 0;
}

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) > 0)
    {
        printf("SDL_Init() Failed. Error: %s\n", SDL_GetError());
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG)))
    {
        printf("IMG_Init() Failed. Error: %s\n", SDL_GetError());
        return false;
    }

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    gWindow.create("TEH GAYM", WIDTH, HEIGHT);
    gTextures["enemy-ufo"] = gWindow.pLoadTexture("res/textures/enemy/ufo.png");
    gTextures["player-ship"] = gWindow.pLoadTexture("res/textures/player/spaceship.png");
    gTextures["bullet"] = gWindow.pLoadTexture("res/textures/bullets/bullet.png");
    gTextures["bullet-180"] = gWindow.pLoadTexture("res/textures/bullets/bullet-180.png");

    gQuit = false;

    srand((unsigned)time(0));

    gEnemies.push_back(Enemy(gEnemies, gTextures["enemy-ufo"]));
    gEnemies.push_back(Enemy(gEnemies, gTextures["enemy-ufo"]));
    gEnemies.push_back(Enemy(gEnemies, gTextures["enemy-ufo"]));
    gEnemies.push_back(Enemy(gEnemies, gTextures["enemy-ufo"]));

    gSfx["jump"] = Mix_LoadWAV("res/sounds/jump.wav");
    gSfx["fall"] = Mix_LoadWAV("res/sounds/fall.wav");
    gSfx["click"] = Mix_LoadWAV("res/sounds/click.wav");
    gSfx["hit"] = Mix_LoadWAV("res/sounds/hit.wav");

    Mix_PlayChannel(-1, gSfx["click"], 0);

    return true;
}
