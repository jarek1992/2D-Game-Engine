#pragma once

struct spriteComponent {
	int width;
	int height;

	spriteComponent(int width = 0, int height = 0) {
		this->height = height;
		this->width = width;
	}
};