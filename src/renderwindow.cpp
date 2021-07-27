#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Config.hpp"
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
    SDL_SetRenderDrawColor(mpRenderer, 90, 90, 90, 255);
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

void RenderWindow::renderCenter(Vector2f position, const char* pText, TTF_Font* pFont, SDL_Color color)
{
    SDL_Surface* pSurfaceMessage = TTF_RenderText_Blended(pFont, pText, color);
    SDL_Texture* pMessage = SDL_CreateTextureFromSurface(mpRenderer,  pSurfaceMessage);

    SDL_Rect source;
    source.x = 0;
    source.y = 0;
    source.w = pSurfaceMessage->w;
    source.h = pSurfaceMessage->h;

    SDL_Rect destination;
    destination.x = WIDTH/2 - source.w/2 + position.mX;
    destination.y = HEIGHT/2 - source.h/2 + position.mY;
    destination.w = source.w;
    destination.h = source.h;

    SDL_RenderCopy(mpRenderer, pMessage, &source, &destination);
    SDL_FreeSurface(pSurfaceMessage);
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
