#pragma once

#include "ecs.hpp"
#include "eventBus.hpp"
#include "boxColliderComponent.hpp"
#include "transformComponent.hpp"
#include "collisionEvent.hpp"

class CollisionSystem : public System {
	public:
		CollisionSystem() {
			requireComponent<TransformComponent>();
			requireComponent<BoxColliderComponent>();
		}

		void Update(std::unique_ptr<EventBus>& eventBus) {
			auto entities = getSystemEntities();

			// Loop all the entities that syste is interested in
			for (auto i = entities.begin(); i != entities.end(); i++) {
				Entity entityA = *i;
				const auto& aTransform = entityA.getComponent<TransformComponent>();
				const auto& aCollider = entityA.getComponent<BoxColliderComponent>();
				
				// Loop all the entities towards the rights (from i) side that still need to be checked
				for (auto j = std::next(i); j != entities.end(); ++j) {
					Entity entityB = *j;

					const auto& bTransform = entityB.getComponent<TransformComponent>();
					const auto& bCollider = entityB.getComponent<BoxColliderComponent>();

					// Check the collision between entityA and entityB
					bool isColliding = aabbCheckCollison(
						aTransform.position.x + aCollider.offset.x,
						aTransform.position.y + aCollider.offset.y,
						aCollider.width,
						aCollider.height,
						bTransform.position.x + bCollider.offset.x,
						bTransform.position.y + bCollider.offset.y,
						bCollider.width,
						bCollider.height
					);

					if (isColliding) {
						Logger::Log("Entity " + std::to_string(entityA.getId()) + " is colliding with entity " + std::to_string(entityB.getId()));
						eventBus->emitEvent<CollisionEvent>(entityA, entityB);

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