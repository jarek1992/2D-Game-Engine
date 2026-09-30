#pragma once

#include "ecs.hpp"
#include "boxColliderComponent.hpp"
#include "eventBus.hpp"
#include "collisionEvent.hpp"


class DamageSystem : public System {
	public:
		DamageSystem() {
			requireComponent<BoxColliderComponent>();
		}

		void subscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
			eventBus->subscribeToEvent<CollisionEvent>(this, &DamageSystem::onCollision);
		}

		void onCollision(CollisionEvent& event) {

		}

		void Update() {

		}
};