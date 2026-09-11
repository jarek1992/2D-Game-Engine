#pragma once

#include <SDL2/SDL.h>

#include "ecs.hpp"
#include "transformComponent.hpp"
#include "rigidBodyComponent.hpp"
#include "spriteComponent.hpp"

class renderSystem : public System {
public:
	renderSystem() {
		requireComponent<transformComponent>();
		requireComponent<spriteComponent>();
	}

	void Update(SDL_Renderer* renderer) {
		// Update all entities with a transformComponent
		for (auto entity : getSystemEntities()) {
			// Update the entity's position based on its velocity
			const auto transform = entity.getComponent<transformComponent>();
			const auto sprite = entity.getComponent<spriteComponent>();

			SDL_Rect objRect = {
				static_cast<int>(transform.position.x),
				static_cast<int>(transform.position.y),
				sprite.width,
				sprite.height
			};
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderFillRect(renderer, &objRect);

		}
	}
};