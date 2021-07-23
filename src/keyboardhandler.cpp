#include <SDL2/SDL.h>
#include <map>

#include "KeyboardHandler.hpp"

std::map<SDL_Keycode, bool> KeyboardHandler::mpKeyState;

void KeyboardHandler::handlePressEvent(SDL_Event &rEvent)
{
    mpKeyState[rEvent.key.keysym.sym] = true;
}

void KeyboardHandler::handleReleaseEvent(SDL_Event &rEvent)
{
    mpKeyState[rEvent.key.keysym.sym] = false;
}

bool KeyboardHandler::isPressed(const SDL_Keycode key)
{
    if (mpKeyState.count(key))
    {
        return mpKeyState[key];
    }

    return false;
}
