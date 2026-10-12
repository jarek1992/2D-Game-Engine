#pragma once

#include "ecs.hpp"
#include "eventBus.hpp"
#include "keyPressedEvent.hpp"
#include "rigidBodyComponent.hpp"
#include "spriteComponent.hpp"

class KeyboardControlSystem : public System {
public:
	KeyboardControlSystem() {
		requireComponent<SpriteComponent>();
		requireComponent<RigidBodyComponent>();
	}

	void subscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
		eventBus->subscribeToEvent<KeyPressedEvent>(this, &KeyboardControlSystem::onKeyPressed);
	}

	void onKeyPressed(KeyPressedEvent& event) {
		std::string keyCode = std::to_string(event.symbol);
		std::string keySymbol(1, event.symbol);
		Logger::Log("Key pressed: " + keySymbol + " (code: " + keyCode + ")");
	}

	void Update() {

	}
};