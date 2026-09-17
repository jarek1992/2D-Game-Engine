#pragma once 

#include "ecs.hpp"
#include "spriteComponent.hpp"
#include "animationComponent.hpp"

#include <SDL2/SDL.h>

class AnimationSystem : public System {
	public:
		AnimationSystem() {
			requireComponent<SpriteComponent>();
			requireComponent<AnimationComponent>();
		}

		void Update() {
			for (auto entity : getSystemEntities()) {
				auto& animation = entity.getComponent<AnimationComponent>();
				auto& sprite = entity.getComponent<SpriteComponent>();

				animation.currentFrame = ((SDL_GetTicks() - animation.startFrame) * animation.frameSpeed / 1000) % animation.numFrames;
				sprite.srcRect.x = animation.currentFrame * sprite.width;
			}
		}

	private:
};