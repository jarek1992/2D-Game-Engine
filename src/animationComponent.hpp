#pragma once

#include <SDL2/SDL.h>

struct AnimationComponent {
	int numFrames;
	int currentFrame;
	int frameSpeed;
	bool isLoop;
	int startFrame;


	AnimationComponent(int numFrames = 1, int frameSpeed = 1, bool isLoop = true) {
		this->numFrames = numFrames;
		this->currentFrame = 1;
		this->frameSpeed = frameSpeed;
		this->isLoop = isLoop;
		this->startFrame = SDL_GetTicks();
	}
};