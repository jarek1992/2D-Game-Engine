#pragma once

#include "ecs.hpp"
#include "eventBus.hpp"
#include "keyPressedEvent.hpp"
#include "keyboardControlledComponent.hpp"
#include "rigidBodyComponent.hpp"
#include "spriteComponent.hpp"

#include <SDL2/SDL.h>

class KeyboardControlSystem : public System {
public:
	KeyboardControlSystem() {
		requireComponent<KeyboardControlledComponent>();
		requireComponent<SpriteComponent>();
		requireComponent<RigidBodyComponent>();
	}

	void subscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
		eventBus->subscribeToEvent<KeyPressedEvent>(this, &KeyboardControlSystem::onKeyPressed);
	}

	void onKeyPressed(KeyPressedEvent& event) {
		for (auto entity : getSystemEntities()) {
			const auto& keyboardcontrol = entity.getComponent<KeyboardControlledComponent>();
			auto& sprite = entity.getComponent<SpriteComponent>();
			auto& rigidbody = entity.getComponent<RigidBodyComponent>();

			switch (event.symbol) {
				case SDLK_UP: {
					rigidbody.velocity = keyboardcontrol.upVelocity;
					sprite.srcRect.y = sprite.height * 0;
					break;
				}
				case SDLK_RIGHT: {
					rigidbody.velocity = keyboardcontrol.rightVelocity;
					sprite.srcRect.y = sprite.height * 1;
					break;
				}
				case SDLK_DOWN: {
					rigidbody.velocity = keyboardcontrol.downVelocity;
					sprite.srcRect.y = sprite.height * 2;
					break;
				}
				case SDLK_LEFT: {
					rigidbody.velocity = keyboardcontrol.leftVelocity;
					sprite.srcRect.y = sprite.height * 3;
					break;
				}
			}
		}
	}

	void Update() {

	}
};