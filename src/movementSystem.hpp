#pragma once

#include "ecs.hpp"
#include "transformComponent.hpp"
#include "rigidBodyComponent.hpp"

class movementSystem : public System {
	public:
		movementSystem() {
			requireComponent<transformComponent>();
			requireComponent<rigidBodyComponent>();
		}

		void Update(double deltaTime) {
			// Update all entities with a transformComponent
			for(auto entity : getSystemEntities()) {
				// Update the entity's position based on its velocity
				auto& transform = entity.getComponent<transformComponent>();
				const auto rigidBody = entity.getComponent<rigidBodyComponent>();

				transform.position.x += rigidBody.velocity.x * deltaTime;
				transform.position.y += rigidBody.velocity.y * deltaTime;
			}
		}
};