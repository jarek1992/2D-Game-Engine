#include "ecs.hpp"

int Entity::getId() const {
	return id;
}

void System::addEntityToSystem(Entity entity) {
	entities.push_back(entity);
};

void System::removeEntityFromSystem(Entity entity) {
	entities.erase(std::remove_if(entities.begin(), entities.end(),
		[&entity](Entity e) { 
			return entity == e; 
		}), entities.end());
};

std::vector<Entity> System::getSystemEntities() const {
	return entities;
};

const Signature& System::getComponentSignature() const {
	return componentSignature;
};


