#include "game.hpp"
#include <iostream>
#include <SDL2/SDL.h>

Game::Game() {
	// Constructor implementation
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
	SDL_Window* window = SDL_CreateWindow(
		"Game Window", 
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

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		std::cerr << "Error creating SDL renderer" << std::endl;
		return;
	}
}

void Game::Run() {
	// Main game loop
	//while (true) {
	//	ProcessInput();
	//	Update();
	//	Render();
	//}
}

void Game::ProcessInput() {
	// Handle user input (keyboard, mouse, etc.)
}

void Game::Update() {
	// Update game state (physics, AI, etc.)
}

void Game::Render() {
	// Render the game scene
}

void Game::Destroy() {
	// Clean up resources, destroy window and renderer, quit SDL, etc.
}