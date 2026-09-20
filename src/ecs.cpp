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

	if (freeIds.empty()) {
		// If there are no free ids to be reused
		entityId = numEntities++;
		// Resize entityComponentSignatures vector
		if (entityId >= entityComponentSignatures.size()) {
			entityComponentSignatures.resize(entityId + 1);
		}
	} else {
		// Reused  and id from the list of previously removed entities
		entityId = freeIds.front();
		freeIds.pop_front();
	}

	Entity entity(entityId);
	entity.registry = this;
	entitiesToAdd.insert(entity);

	Logger::Log("Entity created with ID: " + std::to_string(entityId));

	return entity;
}

void Registry::killEntity(Entity entity) {
	entitiesToRemove.insert(entity);


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
}

void Registry::removeEntityFromSystems(Entity entity) {
	for (auto system : systems) {
		system.second->removeEntityFromSystem(entity);
	}
}

void Registry::Update() {
	// Proccessing the entities that are waiting to be created to the active systems
	for (auto entity : entitiesToAdd) {
		addEntityToSystems(entity);
	}
	entitiesToAdd.clear();

	// Proccess the entities that are waiting to be killed from the active Systems
	for (auto entity : entitiesToRemove) {
		removeEntityFromSystems(entity);

		entityComponentSignatures[entity.getId()].reset();
		
		// Make the entity available to be reused
		freeIds.push_back(entity.getId());
	}
	entitiesToRemove.clear();
}