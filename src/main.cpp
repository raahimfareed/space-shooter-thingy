#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <cstdlib>
#include <deque>
#include <cmath>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

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
std::map<const char*, SDL_Color> gColors;
std::map<const char*, TTF_Font*> gFonts;
std::vector<Enemy> gEnemies;
std::deque<PlayerBullet> gPlayerBullets;
std::deque<EnemyBullet> gEnemyBullets;

bool gQuit;
bool load = init();
bool gMainMenu;

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

        if (gMainMenu)
        {
            if (SDL_GetTicks() < 2500)
            {
                gWindow.clear();
                gWindow.renderCenter(Vector2f(0, std::sin(SDL_GetTicks()/100)), "TEH GAYM", gFonts["24"], gColors["white"]);
                gWindow.display();
            }
            else
            {
                gWindow.clear();
                gWindow.renderCenter(Vector2f(0, std::sin(SDL_GetTicks()/100)), "Press Return to Start", gFonts["16"], gColors["white"]);
                gWindow.display();

                if (KeyboardHandler::isPressed(SDLK_RETURN))
                {
                    gMainMenu = false;
                }
            }
        }


        if (!gMainMenu)
        {
            if (gPlayer.getLives() == 0)
            {
                gWindow.clear();
                gWindow.renderCenter(Vector2f(0, std::sin(SDL_GetTicks()/100)), "You died!", gFonts["32"], gColors["red"]);
                gWindow.display();
            }

            if (gPlayer.getLives() > 0)
            {
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
                    gPlayer.fire(gTextures["bullet"], gPlayerBullets, gSfx["pew"]);
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
                    b.update(gPlayerBullets, gEnemies, gSfx["bam"]);
                }

                for(EnemyBullet &b: gEnemyBullets)
                {
                    b.update(gEnemyBullets, gPlayer);
                }

                gWindow.clear();

                gWindow.render(Vector2f(0, 20), "Lives: ", gFonts["16"], gColors["black"]);
                gWindow.render(Vector2f(50, 20), std::to_string(gPlayer.getLives()).c_str(), gFonts["16"], gColors["white"]);


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
            }
        }


        int frameTicks = SDL_GetTicks() - startTicks;
        if (frameTicks < 1000 / gWindow.getRefreshRate())
        {
            SDL_Delay(1000 / gWindow.getRefreshRate() - frameTicks);
        }
    }

    gWindow.cleanUp();
    TTF_Quit();
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

    if (TTF_Init() == -1)
    {
        printf("TTF_Init() Failed. Error: %s\n", SDL_GetError());
    }

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    gWindow.create("TEH GAYM", WIDTH, HEIGHT);
    gTextures["enemy-ufo"] = gWindow.pLoadTexture("res/textures/enemy/ufo.png");
    gTextures["player-ship"] = gWindow.pLoadTexture("res/textures/player/spaceship.png");
    gTextures["bullet"] = gWindow.pLoadTexture("res/textures/bullets/bullet.png");
    gTextures["bullet-180"] = gWindow.pLoadTexture("res/textures/bullets/bullet-180.png");

    gQuit = false;
    gMainMenu = true;

    srand((unsigned)time(0));

    gEnemies.push_back(Enemy(gEnemies, gTextures["enemy-ufo"]));
    gEnemies.push_back(Enemy(gEnemies, gTextures["enemy-ufo"]));
    gEnemies.push_back(Enemy(gEnemies, gTextures["enemy-ufo"]));
    gEnemies.push_back(Enemy(gEnemies, gTextures["enemy-ufo"]));

    gSfx["pew"] = Mix_LoadWAV("res/sounds/pew.wav");
    gSfx["peepoo"] = Mix_LoadWAV("res/sounds/peepoo.wav");
    gSfx["bam"] = Mix_LoadWAV("res/sounds/bam.wav");

    gColors["white"] = {255, 255, 255};
    gColors["black"] = {0, 0, 0};
    gColors["red"] = {128, 0, 0};

    gFonts["32"] = TTF_OpenFont("res/fonts/cocogoose.ttf", 32);
	gFonts["32-outline"] = TTF_OpenFont("res/fonts/cocogoose.ttf", 32);
	gFonts["24"] = TTF_OpenFont("res/fonts/cocogoose.ttf", 24);
	gFonts["16"] = TTF_OpenFont("res/fonts/cocogoose.ttf", 16);
	gFonts["8"] = TTF_OpenFont("res/fonts/cocogoose.ttf", 8);
    TTF_SetFontOutline(gFonts["32-outline"], 3); 

    Mix_PlayChannel(-1, gSfx["peepoo"], 0);

    return true;
}
