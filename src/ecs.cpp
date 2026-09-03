#include "ecs.hpp"
#include "logger.hpp"

int iComponent::nextId = 0;

int Entity::getId() const {
	return id;
}

void System::addEntityToSystem(Entity entity) {
	entities.push_back(entity);
}

void System::removeEntityFromSystem(Entity entity) {
	entities.erase(std::remove_if(entities.begin(), entities.end(),
		[&entity](Entity e) { 
			return entity == e; 
		}), entities.end());
}

std::vector<Entity> System::getSystemEntities() const {
	return entities;
}

const Signature& System::getComponentSignature() const {
	return componentSignature;
}

Entity Registry::createEntity() {
	int entityId;

	entityId = numEntities++;
	Entity entity(entityId);
	entitiesToAdd.insert(entity);

	Logger::Log("Entity created with ID: " + std::to_string(entityId));

	return entity;
}

void Registry::addEntityToSystems(Entity entity) {
	const auto entityId = entity.getId();

	const auto& entityComponentSignature = entityComponentSignatures[entityId];

	// Loop through all systems and check if the entity's component signature matches the system's component signature
	for (auto& system : systems) {
		const auto& systemComponentSignature = system.second->getComponentSignature();

		bool isMatched = (entityComponentSignature & systemComponentSignature) == systemComponentSignature;

		if (isMatched) {
			system.second->addEntityToSystem(entity);
		}
}

void Registry::Update() {

}