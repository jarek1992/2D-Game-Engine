#pragma once

#include <glm/glm.hpp>

struct KeyboardControlledComponent {
	glm::vec2 upVelocity;
	glm::vec2 rightVelocity;
	glm::vec2 downVelocity;
	glm::vec2 leftVelocity;

	KeyboardControlledComponent(
		glm::vec2 upVelocity = glm::vec(0),
		glm::vec2 rightVelocity = glm::vec(0),
		glm::vec2 downVelocity = glm::vec(0),
		glm::vec2 leftVelocity = glm::vec(0)) 
	{
		this->upVelocity = upVelocity;
		this->rightVelocity = rightVelocity;
		this->downVelocity = downVelocity;
		this->leftVelocity = leftVelocity;
	}
};