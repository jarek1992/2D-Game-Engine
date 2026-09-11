#pragma once

struct spriteComponent {
	int width;
	int height;

	spriteComponent(int width, int height) {
		this->height = height;
		this->width = width;
	}
};