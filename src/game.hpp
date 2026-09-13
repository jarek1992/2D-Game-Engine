#pragma once

#include <SDL2/SDL.h>

#include "ecs.hpp"
#include "assetStore.hpp"

const int fps = 2;
const  int milisecsPerFrame = 1000 / fps ;

class Game {
private:
	bool isRunning;
	int millisecsPrevFrame = 0;
	SDL_Window *window;
	SDL_Renderer *renderer;

	// Registry* registry
	std::unique_ptr<Registry> registry;
	// Asset Store
	std::unique_ptr<assetStore> assetStore;

public:
	Game();
	~Game();

	void Initialize();
	void Run();
	void ProcessInput();
	void Setup();
	void Update();
	void Render();
	void Destroy();

	int windowWidth = 0;
	int windowHeight = 0;;
};