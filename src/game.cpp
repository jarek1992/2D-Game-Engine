#include "game.hpp"
#include <iostream>
#include <SDL2/SDL.h>

Game::Game() {
	// Constructor implementation
	isRunning = false;
	std::cout << "Game object created." << std::endl;
}

Game::~Game() {
	// Destructor implementation
	std::cout << "Game object destroyed." << std::endl;
}

void Game::Initialize() {
	// Initialize SDL, create window and renderer, load resources, etc. 
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "SDL_Init Error: " << std::endl;
		return;
	}

	//// Get the current display mode to determine the screen resolution
	//SDL_DisplayMode displayMode;
	//SDL_GetCurrentDisplayMode(0, &displayMode);
	//windowWidth = displayMode.w;
	//windowHeight = displayMode.h;

	window = SDL_CreateWindow(
		NULL, 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		800,
		600,
		SDL_WINDOW_BORDERLESS
	);
	if (!window) {
		std::cerr << "Error initializing SDL window" << std::endl;
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		std::cerr << "Error creating SDL renderer" << std::endl;
		return;
	}

	isRunning = true;
}

void Game::Run() {
	// Main game loop
	while (isRunning) {
		ProcessInput();
		Update();
		Render();
	}
}

void Game::ProcessInput() {
	// Handle user input (keyboard, mouse, etc.)
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
					isRunning = false;
				}
				break;
		}
	}
}

void Game::Update() {
	// Update game state (physics, AI, etc.)
}

void Game::Render() {
	// Render the game scene
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);

	// Render game objects here ... 

	SDL_RenderPresent(renderer);
}

void Game::Destroy() {
	// Clean up resources, destroy window and renderer, quit SDL, etc.
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}