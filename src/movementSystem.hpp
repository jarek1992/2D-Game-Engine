#pragma once

#include "ecs.hpp"
#include "transformComponent.hpp"
#include "rigidBodyComponent.hpp"

class MovementSystem : public System {
	public:
		MovementSystem() {
			requireComponent<TransformComponent>();
			requireComponent<RigidBodyComponent>();
		}

		void Update(double deltaTime) {
			// Update all entities with a TransformComponent
			for(auto entity : getSystemEntities()) {
				// Update the entity's position based on its velocity
				auto& transform = entity.getComponent<TransformComponent>();
				const auto rigidBody = entity.getComponent<RigidBodyComponent>();

				transform.position.x += rigidBody.velocity.x * deltaTime;
				transform.position.y += rigidBody.velocity.y * deltaTime;
			}
		}
};