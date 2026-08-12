#include "game.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>

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

	// Get the current display mode to determine the screen resolution
	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	windowWidth = 800;
	windowHeight = 600;
	window = SDL_CreateWindow(
		NULL, 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		windowWidth,
		windowHeight,
		SDL_WINDOW_BORDERLESS
	);
	if (!window) {
		std::cerr << "Error initializing SDL window" << std::endl;
		return;
	}

	Uint32 preffed_flags[] = { 
		SDL_RENDERER_ACCELERATED, SDL_RENDERER_PRESENTVSYNC, // 1. GPU + V-Sync
		SDL_RENDERER_ACCELERATED, // 2. GPU only
		0 // 3. Fallback use whatever works
	};

	for(Uint32 flags : preffed_flags) {
		renderer = SDL_CreateRenderer(window, -1, flags);
		if(renderer) {
			break;
		}
	}
	if (!renderer) {
		std::cerr << "Error creating SDL renderer: " << SDL_GetError() << std::endl;
		return;
	}

	// Set the window to fullscreen mode
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	isRunning = true;
}

void Game::Run() {
	// Main game loop
	Setup();
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

glm::vec2 playerPost;
glm::vec2 playerVel;

void Game::Setup() {
	// Set up game objects, load resources, etc.
	playerPost = glm::vec2(5.0, 5.0);
	playerVel = glm::vec2(0.1, 0.0);
}

void Game::Update() {
	// Update game state (physics, AI, etc.)
	playerPost.x += playerVel.x; // Move the player to the right
	playerPost.y += playerVel.y; // Move the player down
}

void Game::Render() {
	// Render the game scene
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	// Draw PNG texture
	// Tank
	SDL_Surface* surface = IMG_Load("libs/assets/tank_top.png");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	SDL_Rect destRect = {
		static_cast<int>(playerPost.x), 
		static_cast<int>(playerPost.y),
		32, 
		32
	};

	SDL_RenderCopy(renderer, texture, NULL, &destRect);
	SDL_DestroyTexture(texture);

	SDL_RenderPresent(renderer);
}

void Game::Destroy() {
	// Clean up resources, destroy window and renderer, quit SDL, etc.
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}