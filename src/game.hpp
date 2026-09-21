#pragma once

#include <SDL2/SDL.h>
#include <memory>

#include "ecs.hpp"
#include "assetStore.hpp"

const int fps = 60;
const  int milisecsPerFrame = 1000 / fps ;

class Game {
private:
	bool isRunning;
	bool isDebugging;
	int millisecsPrevFrame = 0;
	SDL_Window *window;
	SDL_Renderer *renderer;

	// Registry* registry
	std::unique_ptr<Registry> registry;
	// Asset Store
	std::unique_ptr<AssetStore> assetStore;

	std::unique_ptr<EventBus> eventBus;

public:
	Game();
	~Game();

	void Initialize();
	void Run();
	void ProcessInput();
	void LoadLevel(int level);
	void Setup();
	void Update();
	void Render();
	void Destroy();

	int windowWidth = 0;
	int windowHeight = 0;
};