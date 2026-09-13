#pragma once 

#include <map>
#include <string>
#include <SDL2/SDL.h>

class assetStore {
	private:
		std::map<std::string, SDL_Texture*> textures;
		// TODO: create a map for fonts and sounds
		// TODO: create a map for music, audio etc

	public:
		assetStore();
		~assetStore();

		void clearAssets();
		void addexture(const std::string& assetId, const std::string& filePath);
		SDL_Texture* getTexture(const std::string& assetId) const;
};