#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Entity.hpp"

class RenderWindow
{
public:
    RenderWindow() = default;
    RenderWindow(const char* pTitle, int width, int height);
    void create(const char* pTitle, int width, int height);
    SDL_Texture* pLoadTexture(const char* pTexturePath);
    void clear();
    void render(SDL_Texture* pTexture, int dstX = 0, int dstY = 0, int srcX = 0, int srcY = 0);
    void render(Entity &rEntity);
    void renderCenter(Vector2f position, const char* pText, TTF_Font* pFont, SDL_Color color);
    void display();
    void cleanUp();
    SDL_Window* pGetWindow();
    int getRefreshRate();

private:
    SDL_Window* mpWindow;
    SDL_Renderer* mpRenderer;
};
