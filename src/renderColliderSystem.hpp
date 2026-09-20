#pragma once 

#include "ecs.hpp"
#include "transformComponent.hpp"
#include "boxColliderComponent.hpp"

#include <SDL2/SDL.h>

class RenderColliderSystem : public System {
	public:
		RenderColliderSystem() {
			requireComponent<TransformComponent>();
			requireComponent<BoxColliderComponent>();
		}

		void Update(SDL_Renderer * renderer) {
			for (auto entity : getSystemEntities()) {
				const auto transform = entity.getComponent<TransformComponent>();
				const auto collider = entity.getComponent<BoxColliderComponent>();

				SDL_Rect colliderRect = {
					static_cast<int>(transform.position.x + collider.offset.x),
					static_cast<int>(transform.position.y + collider.offset.y),
					static_cast<int>(collider.width * transform.scale.x),
					static_cast<int>(collider.height * transform.scale.y)
				};
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
				SDL_RenderDrawRect(renderer, &colliderRect);
			}
		}
};