#include "game.hpp"
#include "assetStore.hpp"

#include "logger.hpp"
#include "ecs.hpp"
#include "transformComponent.hpp"
#include "rigidBodyComponent.hpp"
#include "movementSystem.hpp"
#include "spriteComponent.hpp"
#include "renderSystem.hpp"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <sstream>
#include <fstream>
#include <string>

Game::Game() {
	// Constructor implementation
	isRunning = false;
	registry = std::make_unique<Registry>();
	assetStore = std::make_unique<AssetStore>();
	Logger::Log("Game object created!");
}

Game::~Game() {
	// Destructor implementation
	Logger::Log("Game object destroyed!");
}

void Game::Initialize() {
	// Initialize SDL, create window and renderer, load resources, etc. 
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		Logger::Err("SDL_Init Error.");
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
		Logger::Err("Error initializing SDL window");
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
		Logger::Err("Error creating SDL renderer");
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

void Game::LoadLevel(int level) {
	// Add the systems to be proccessed in the game loop
	registry->addSystem<MovementSystem>();
	registry->addSystem<RenderSystem>();

	// Load assets into the asset store
	assetStore->addTexture(renderer, "tank_blue", "./libs/assets/tank_top_blue.png");
	assetStore->addTexture(renderer, "tank_green", "./libs/assets/tank_top_green.png");
	assetStore->addTexture(renderer, "tilemap_image", "./libs/assets/tileset.png");

	// Load the tilemap
	int tileSize = 24;
	double tileScale = 1.0;
	int mapColumns = 20;
	int mapRows = 20;

	int tilesetColumns = 5;

	std::fstream mapFile;
	mapFile.open("./libs/assets/tileset.map");

	if (!mapFile.is_open()) { return; }

	for (int y = 0; y < mapRows; y++) {
		std::string line;
		if (!std::getline(mapFile, line)) { break; }

		std::stringstream ss(line);

		for (int x = 0; x < mapColumns; x++) {
			std::string strTileIndex;

			if (!std::getline(ss, strTileIndex, ',')) { break; }
			if (strTileIndex.empty()) { continue; }

			int tileIndex = std::stoi(strTileIndex);

			int srcRectX = (tileIndex % tilesetColumns) * tileSize;
			int srcRectY = (tileIndex / tilesetColumns) * tileSize;

			Entity tile = registry->createEntity();

			tile.addComponent<TransformComponent>(
				glm::vec2(x * (tileSize * tileScale), y * (tileSize * tileScale)), 
				glm::vec2(tileScale, tileScale), 
				0.0
			);

			tile.addComponent<SpriteComponent>(
				"tilemap_image", 
				tileSize, 
				tileSize, 
				0,
				srcRectX, 
				srcRectY
			);
		}
	}
	mapFile.close();

	// Create entities and add components to them
	Entity tank_blue = registry->createEntity();
	tank_blue.addComponent<TransformComponent>(glm::vec2(50.0, 50.0), glm::vec2(0.042, 0.042), -90.0);
	tank_blue.addComponent<RigidBodyComponent>(glm::vec2(20.0, 0.0));
	tank_blue.addComponent<SpriteComponent>("tank_blue", 620, 691, 1);

	// Create entities and add components to them
	Entity tank_green = registry->createEntity();
	tank_green.addComponent<TransformComponent>(glm::vec2(10.0, 10.0), glm::vec2(0.05, 0.05), 0.0);
	tank_green.addComponent<RigidBodyComponent>(glm::vec2(40.0, 0.0));
	tank_green.addComponent<SpriteComponent>("tank_green", 512.0, 512.0, 1);
}

void Game::Setup() {
	LoadLevel(1);
}

void Game::Update() {
	// Update game state (physics, AI, etc.)

	int timeToWait = milisecsPerFrame - (SDL_GetTicks() - millisecsPrevFrame);
	if (timeToWait > 0 && timeToWait <= milisecsPerFrame) {
		SDL_Delay(timeToWait);
	}

	// Difference in ticks since the last frame, converted to seconds (delta time)
	double deltaTime = (SDL_GetTicks() - millisecsPrevFrame) / 1000.0; // Convert milliseconds to seconds

	// Calculate the time elapsed since the last frame
	millisecsPrevFrame = SDL_GetTicks();

	// Update the registry to process the entities that are waiting to be added/deleted to the systems
	registry->Update();

	// Invoke all the system that need to update
	registry->getSystem<MovementSystem>().Update(deltaTime);
}

void Game::Render() {
	// Render the game scene
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
	SDL_RenderClear(renderer);

	// Invoke all the system that need to render
	registry->getSystem<RenderSystem>().Update(renderer, assetStore);

	SDL_RenderPresent(renderer);
}

void Game::Destroy() {
	// Clean up resources, destroy window and renderer, quit SDL, etc.
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}