#pragma once

#include <glm/glm.hpp>

struct rigidBodyComponent {
	glm::vec2 velocity;

	rigidBodyComponent(glm::vec2 velocity = glm::vec2(0.0, 0.0)) {
		this->velocity = velocity;
	}
};