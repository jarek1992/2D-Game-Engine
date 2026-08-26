cmake_minimum_required(VERSION 3.20)
project(2DGameEngine CXX)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Download dependencies with vcpkg
find_package(sdl2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(unofficial-lua CONFIG REQUIRED)
find_package(sol2 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

# Source files (to be updated)
add_executable(${PROJECT_NAME}
	src/main.cpp
    src/game.cpp
    src/logger.cpp
    libs/imgui_backend/imgui_impl_sdl2.cpp
    libs/imgui_backend/imgui_impl_sdlrenderer2.cpp
 "src/transformComponent.cpp")

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/libs/imgui_backend
)

if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE LUA_BUILD_AS_DLL)
endif()

# Link libraries 
target_link_libraries(${PROJECT_NAME} PRIVATE
	SDL2::SDL2main
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
    $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>
    $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
    $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>
    unofficial::lua::lua
    sol2::sol2
    glm::glm
    imgui::imgui
)
