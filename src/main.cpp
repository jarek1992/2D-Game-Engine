#include "game.hpp"

//#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_ttf.h>
//#include <SDL_mixer.h>
//#include <glm/glm.hpp>
//#include <imgui.h>
//#include <imgui_impl_sdl2.h>
//#include <imgui_impl_sdlrenderer2.h>
//#include <sol/sol.hpp>

int main(int argc, char* argv[]) {
	Game game;

	game.Initialize();
	game.Run();
	game.Destroy();
	
	/*sol::state lua;

	lua.open_libraries(sol::lib::base);
	lua.script("print('Sol2 & Lua works!')");

	glm::vec2 velocity = glm::vec2(2.0, -1.0);

	SDL_Init(SDL_INIT_EVERYTHING);
	std::cout << "Engine works!" << std::endl;*/

	return 0;
}