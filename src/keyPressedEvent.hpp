#pragma once

#include "ecs.hpp"
#include "event.hpp"
#include <SDL2/SDL.h>

class KeyPressedEvent : public Event {
public:
	SDL_Keycode symbol;
	KeyPressedEvent(SDL_Keycode symbol) : symbol(symbol) {}
};