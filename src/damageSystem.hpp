#pragma once

#include "ecs.hpp"
#include "boxColliderComponent.hpp"
#include "eventBus.hpp"
#include "collisionEvent.hpp"
#include "logger.hpp"


class DamageSystem : public System {
	public:
		DamageSystem() {
			requireComponent<BoxColliderComponent>();
		}

		void subscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
			eventBus->subscribeToEvent<CollisionEvent>(this, &DamageSystem::onCollision);
		}

		void onCollision(CollisionEvent& event) {
			Logger::Log("Damage system received an event collision between entities " 
				+ std::to_string(event.a.getId()) 
				+ " and " 
				+ std::to_string(event.b.getId())
			);
			event.a.destroy();
			event.b.destroy();
		}

		void Update() {

		}
};