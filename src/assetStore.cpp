#include "assetStore.hpp"
#include "logger.hpp"

#include <SDL2/SDL_image.h>

AssetStore::AssetStore() {
	Logger::Log("Asset Store constructor created");
}

AssetStore::~AssetStore() {
	clearAssets();
	Logger::Log("Asset Store destructor called");
}

void AssetStore::clearAssets() {
	for(auto texture : textures) {
		SDL_DestroyTexture(texture.second);
	}
	textures.clear();
}

void AssetStore::addTexture(SDL_Renderer* renderer, const std::string& assetId, const std::string& filePath) {
	SDL_Surface* surface = IMG_Load(filePath.c_str());
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	// Add texture to the map
	textures[assetId] = texture;
}

SDL_Texture* AssetStore::getTexture(const std::string& assetId) {
	return textures[assetId];

	Logger::Log("New texture with assetId: " + assetId + " added to asset store");
}