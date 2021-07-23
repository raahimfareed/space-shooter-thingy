#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "RenderWindow.hpp"
#include "Entity.hpp"

RenderWindow::RenderWindow(const char* pTitle, int width, int height)
{
    mpWindow = SDL_CreateWindow(pTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

    if (mpWindow == nullptr)
    {
        printf("Failed to create a window. Error: %s\n", SDL_GetError());
    }

    mpRenderer = SDL_CreateRenderer(mpWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void RenderWindow::create(const char* pTitle, int width, int height)
{
    mpWindow = SDL_CreateWindow(pTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

    if (mpWindow == nullptr)
    {
        printf("Failed to create a window. Error: %s\n", SDL_GetError());
    }

    mpRenderer = SDL_CreateRenderer(mpWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

SDL_Texture* RenderWindow::pLoadTexture(const char* pTexturePath)
{
    SDL_Texture* pTexture = nullptr;

    pTexture = IMG_LoadTexture(mpRenderer, pTexturePath);

    if (pTexture == nullptr)
    {
        printf("Could not load texture. Error: %s\n", SDL_GetError());
    }

    return pTexture;
}

void RenderWindow::clear()
{
    SDL_RenderClear(mpRenderer);
}

void RenderWindow::render(SDL_Texture* pTexture, int srcX, int srcY, int dstX, int dstY)
{
    SDL_Rect source;
    source.x = srcX;
    source.y = srcY;
    source.w = 64;
    source.h = 64;

    SDL_Rect destination;
    destination.x = dstX;
    destination.y = dstY;
    destination.w = 64;
    destination.h = 64;

    SDL_RenderCopy(mpRenderer, pTexture, &source, &destination);
}

void RenderWindow::render(Entity &rEntity)
{
    SDL_Rect source;
    source.x = rEntity.getCurrentFrame().x;
    source.y = rEntity.getCurrentFrame().y;
    source.w = rEntity.getCurrentFrame().w;
    source.h = rEntity.getCurrentFrame().h;
    
    SDL_Rect destination;
    destination.x = rEntity.rGetPosition().mX;
    destination.y = rEntity.rGetPosition().mY;
    destination.w = rEntity.getCurrentFrame().w;
    destination.h = rEntity.getCurrentFrame().h;

    SDL_RenderCopy(mpRenderer, rEntity.prGetTexture(), &source, &destination);
}

void RenderWindow::display()
{
    SDL_RenderPresent(mpRenderer);
}

void RenderWindow::cleanUp()
{
    SDL_DestroyWindow(mpWindow);
}

SDL_Window* RenderWindow::pGetWindow()
{
    return mpWindow;
}

int RenderWindow::getRefreshRate()
{
    int displayIndex = SDL_GetWindowDisplayIndex(mpWindow);
    SDL_DisplayMode mode;

    SDL_GetDisplayMode(displayIndex, 0, &mode);

    return mode.refresh_rate;
}
