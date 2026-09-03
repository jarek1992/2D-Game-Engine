#pragma once

#include <glm/glm.hpp>

struct transformComponent {
	glm::vec2 postition;
	glm::vec2 scale;
	double rotation;

	transformComponent(glm::vec2 position = glm::vec2(0.0, 0.0), glm::vec2 scale = glm::vec2(1.0, 1.0), double rotation = 0.0) {
		this->postition = position;
		this->scale = scale;
		this->rotation = rotation;
	}
};

