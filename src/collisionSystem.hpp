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
					auto bTransform = entityB.getComponent<TransformComponent>();
					auto bCollider = entityB.getComponent<BoxColliderComponent>();

					// Check the collision between entityA and entityB

				}
			}
		}
};