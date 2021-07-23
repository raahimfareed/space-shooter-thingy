#pragma once
#include <SDL2/SDL.h>

#include <map>

struct KeyboardHandler
{
public:
    static void handlePressEvent(SDL_Event &rEvent);
    static void handleReleaseEvent(SDL_Event &rEvent);
    static bool isPressed(const SDL_Keycode key);

    static std::map<SDL_Keycode, bool> mpKeyState;
};
