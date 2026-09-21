#pragma once

#include "logger.hpp"

#include <map>
#include <typeindex>
#include <list>

class iEventCallBack {

};

template <typename TEvent>
class EventCallBack : public iEventCallBack{
	// Callback function pointer that needs to be invoked

};

typedef std::list<std::unique_ptr<iEventCallBack>> HandlerList;

class EventBus {
	private:
		std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers;

	public:
		EventBus() {
			Logger::Log("EventBus constructor called!");
		}
		~EventBus() {
			Logger::Log("EventBus decstructor called!");
		}
		// Subscribie to an event type  <T>
		// In our implementation, a listener subscribes to an event
		// example: eventBus->subscribeToEvent<CollisionEvent>(&Game::onCollision);
		void subscribeToEvent<>() {
			//........
		}

		// Emit an event of type <T>
		// In our implementation as soon as sth emit an event 
		// we go ahead and execute all the listener callback functions
		// example: eventBus->emitEvent<CollisionEvent>(player, enemy);
		void emitEvent<>() {
			//........
		}
};