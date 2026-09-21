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
};