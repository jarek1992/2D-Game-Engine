#pragma once

#include "ecs.hpp"
#include "transformComponent.hpp"
#include "rigidBodyComponent.hpp"
#include "spriteComponent.hpp"
#include "assetStore.hpp"

#include <SDL2/SDL.h>
#include <algorithm>

class RenderSystem : public System {
public:
	RenderSystem() {
		requireComponent<TransformComponent>();
		requireComponent<SpriteComponent>();
	}

	void Update(SDL_Renderer* renderer, std::unique_ptr<AssetStore>& assetStore) {
		// Sort all the entities based on their zIndex value in the SpriteComponent
		// add entity to a vector and sort it based on zIndex
		std::vector<Entity> sortedEntities = getSystemEntities();
		std::sort(sortedEntities.begin(), sortedEntities.end(), [](const Entity& a, const Entity& b) {
			const auto& spriteA = a.getComponent<SpriteComponent>();
			const auto& spriteB = b.getComponent<SpriteComponent>();

			return spriteA.zIndex < spriteB.zIndex;
		});

		// Update all entities with a TransformComponent
		for (auto entity : sortedEntities) {
			// Update the entity's position based on its velocity
			const auto& transform = entity.getComponent<TransformComponent>();
			const auto& sprite = entity.getComponent<SpriteComponent>();

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