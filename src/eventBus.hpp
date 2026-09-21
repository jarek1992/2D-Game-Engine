#pragma once

#include "logger.hpp"

class EventBus {
	public:
		EventBus() {
			Logger::Log("EventBus constructor called!");
		}
		~EventBus() {
			Logger::Log("EventBus decstructor called!");
		}
		// Subscribie to an event type  <T>
		// In our implementation, a listener subscribes to an event
		// example: eventBus->subscribeToEvent<CollisionEvent>(&Game::onCollision)
		void subscribeToEvent<>() {
			//........
		}
		// Emit an event of type <T>
		// In our implementation as soon as sth emit an event 
		// we go ahead and execute all the listener callback functions
		void emitEvent<>() {
			//........
		}
};