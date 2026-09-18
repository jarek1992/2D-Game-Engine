#pragma once

#include "ecs.hpp"
#include "boxColliderComponent.hpp"
#include "transformComponent.hpp"

class CollisionSystem : public System {
	public:
		CollisionSystem() {
			requireComponent<TransformComponent>();
			requireComponent<BoxColliderComponent>();
		}

		void Update() {
			auto entities = getSystemEntities();

			// Loop all the entities that syste is interested in
			for (auto i = entities.begin(); i != entities.end(); i++) {
				Entity entityA = *i;
				auto aTransform = entityA.getComponent<TransformComponent>();
				auto aCollider = entityA.getComponent<BoxColliderComponent>();
				
				// Loop all the entities towards the rights (from i) side that still need to be checked
				for (auto j = i; j != entities.end(); j++) {
					Entity entityB = *j;

					// Bypass if we are trying to test the same entity
					if (entityA == entityB) {
						continue;
					}

					auto bTransform = entityB.getComponent<TransformComponent>();
					auto bCollider = entityB.getComponent<BoxColliderComponent>();

					// Check the collision between entityA and entityB
					bool isColliding = aabbCheckCollison(
						aTransform.position.x,
						aTransform.position.y,
						aCollider.width,
						aCollider.height,
						bTransform.position.x,
						bTransform.position.y,
						bCollider.width,
						bCollider.height
					);

					if (isColliding) {
						Logger::Log("Entity " + std::to_string(a.getId()) + " is colliding with entity " + std::to_string(b.getId()));
						// EVENT HAPPENING WHEN THEY COLLIDE WITH EACH OTHER
					}
				}
			}
		}

		bool aabbCheckCollison(double aX, double aY, double aW, double aH, double bX, double bY, double bW, double bH) {
			return (
				aX < bX + bW &&
				aX + aW > bX &&
				aY < bY + bH &&
				aY + aH > bY
			);
		}
};