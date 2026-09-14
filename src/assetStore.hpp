#pragma once 

#include <map>
#include <string>
#include <SDL2/SDL.h>

class AssetStore {
	private:
		std::map<std::string, SDL_Texture*> textures;
		// TODO: create a map for fonts and sounds
		// TODO: create a map for music, audio etc

	public:
		AssetStore();
		~AssetStore();

		void clearAssets();
		void addTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string& filePath);
		SDL_Texture* getTexture(const std::string& assetId);
};