#pragma once

#include "logger.hpp"
#include "event.hpp"

#include <map>
#include <typeindex>
#include <list>

class iEventCallBack {
	public:
		virtual ~iEventCallBack() = default;

		void execute(Event& e) {
			call(e);
		}

	private:
		virtual void call(Event& e) = 0;
};

template <typename TOwner, typename TEvent>
class EventCallBack : public iEventCallBack{
	// Callback function pointer that needs to be invoked
	public:
		EventCallBack(TOwner* ownerInstance, CallBackFunction callBackFunction) {
			this->onwerInstance = onwerInstance;
			this->callBackFunction = callBackFunction;
		}

		virtual ~iEventCallBack() override = default;

	private:
		typedef void (TOwner::* CallBackFunction)(TEvent&);

		TOwner* onwerInstance;
		CallBackFunction callBackFunction;

		virtual void call(Event& e) override {
			std::invoke(callBackFunction, onwerInstance, static_cast<TEvent&>(e));
		}
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
		// example: eventBus->subscribeToEvent<CollisionEvent>(this, &Game::onCollision);
		template <typename TEvent, typename TOwner>
		void subscribeToEvent(TOwner* ownerInstance, void (TOwner::*callBackFunction)(TEvent&)) {
			if (!subscribers[typeid(TEvent)].get()) {
				suscribers[typeid(TEvent)] = std::make_unique<HandlerList>();
			}
			auto suscriber = std::make_unique<EventCallBack<TOwner, TEvent>>(ownerInstance, callBackFunction);
			subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
		}

		// Emit an event of type <T>
		// In our implementation as soon as sth emit an event 
		// we go ahead and execute all the listener callback functions
		// example: eventBus->emitEvent<CollisionEvent>(player, enemy);
		template<typename TEvent, typename ...TArgs>
		void emitEvent(TArgs&& ...args) {
			auto handlers = subscribers[typeid(TEvent)].get();
			if (handlers) {
				for (auto it = handlers->begin(); it != handlers->end(); it++) {
					auto handler = it->get();
					TEvent event(std::forward<TArg>(args)...);
					handler->execute(event);
				}
			}
		}
};