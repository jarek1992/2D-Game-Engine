#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <glm/glm.hpp>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <sol/sol.hpp>

int main(int argc, char* argv[]) {
	sol::state lua;
	lua.open_libraries(sol::lib::base);

	lua.script("print('Sol2 & Lua works!')");
	std::cout << "Engine works!" << std::endl;
	return 0;
}