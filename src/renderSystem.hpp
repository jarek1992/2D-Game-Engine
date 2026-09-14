#pragma once

#include "ecs.hpp"
#include "transformComponent.hpp"
#include "rigidBodyComponent.hpp"
#include "spriteComponent.hpp"
#include "assetStore.hpp"

#include <SDL2/SDL.h>

class renderSystem : public System {
public:
	renderSystem() {
		requireComponent<transformComponent>();
		requireComponent<spriteComponent>();
	}

	void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore) {
		// Update all entities with a transformComponent
		for (auto entity : getSystemEntities()) {
			// Update the entity's position based on its velocity
			const auto transform = entity.getComponent<transformComponent>();
			const auto sprite = entity.getComponent<spriteComponent>();

			// Set the source rectangle for the sprite texture
			SDL_Rect srcRect = sprite.srcRect;

			// Set the destination rectangle with x and y position for rendering the sprite texture
			SDL_Rect dstRect = {
				static_cast<int>(transform.position.x),
				static_cast<int>(transform.position.y),
				static_cast<int>(sprite.width * transform.scale.x),
				static_cast<int>(sprite.height* transform.scale.y)
			};

			// Render the PNG texture to the screen at the entity's position
			SDL_RenderCopyEx(
				renderer, 
				assetStore->getTexture(sprite.assetId),
				&srcRect,
				&dstRect,
				transform.rotation,
				NULL,
				SDL_FLIP_NONE
			);
		}
	}
};