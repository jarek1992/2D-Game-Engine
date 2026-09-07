#pragma once

#include "logger.hpp"

#include <bitset>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <set>
#include <memory>

const unsigned int MAX_COMPONENTS = 32;

//SIGNATURE
// A signature is a bitset (1s and 0s) that represents which components an entity has,
// and also helps keep track of which entities a system is interested in.
typedef std::bitset<MAX_COMPONENTS> Signature;

struct iComponent {
	protected: 		
		static int nextId;
};

// Used to assign a unique ID to each component type.
template<typename T> 
class Component: public iComponent {
	//returns a unique ID for each component type T
	public:
		static int getId() {
			static auto id = nextId++;
			return id;
		}
};

class Entity {
	private:
		int id;
	public:
		Entity(int id) : id(id) {};
		int getId() const;

		// Overload the equality operator to compare entities based on their IDs.
		Entity& operator =(const Entity& other) = default;
		bool operator ==(const Entity& other) const { 
			return id == other.id; 
		}
		bool operator !=(const Entity& other) const { 
			return id != other.id; 
		}
		bool operator >(const Entity& other) const { 
			return id > other.id; 
		}
		bool operator <(const Entity& other) const { 
			return id < other.id; 
		}

};

// SYSTEM
// A system is a collection of entities that have a specific set of components.
class System {
	private:
		Signature componentSignature;
		std::vector<Entity> entities;

	public:
		System() = default;
		~System() = default;

		void addEntityToSystem(Entity entity);
		void removeEntityFromSystem(Entity entity);
		std::vector<Entity> getSystemEntities() const;
		const Signature& getComponentSignature() const;

		// Defines the components that an entity must have to be added to this system.
		template<typename tComponent> void requireComponent();
};

class iPool {
	public:
		virtual ~iPool() {}
};

// POOL
// A pool is just a vector (contiguous data) of objects of type T.
template <typename T>
class Pool: iPool {
	private:
		std::vector<T> data; // Vector of pointers to component data

	public:
		Pool(int size = 100) {
			data.resize(size);
		}
		virtual ~Pool() = default;

		bool isEmpty() const {
			return data.empty();
		}

		int getSize() const {
			return data.size();
		}

		void resize(int n) {
			data.resize(n);
		}

		void clear() {
			data.clear();
		}

		void add(T object) {
			data.push_back(object);
		}

		void set(int index, T object) {
			data[index] = object;
		}

		T& get(int index) {
			return static_cast<T&>(data[index]);
		}

		T& operator [](unsigned int index) {
			return data[index];
		
		}
};

// REGISTRY
// The Registry manages the creation and destruction of entities, 
// as well as the addition and removal of components from entities.
class Registry {
	private:
		// Keep track of number of entities added to the scene.
		int numEntities = 0;

		// Vector of component pools, where each pool contains all the data for the certain component type.
		// [Vector index == component type ID]
		// [Pool index == entity ID]
		std::vector<std::shared_ptr<iPool>> componentPools;

		// Vector of component signatures per entity, saying which components each entity has.
		// [Vector index == entity ID]
		std::vector<Signature> entityComponentSignatures;

		std::unordered_map<std::type_index, std::shared_ptr<System>> systems;

		// Set of entities that are flagged to be added or removed in the next registry Update().
		std::set<Entity> entitiesToAdd;
		std::set<Entity> entitiesToRemove;

	public:
		Registry() {
			Logger::Log("Registry constructor created.");
		}
		~Registry() {
			Logger::Log("Registry destructor called.");
		}

		// The registry Update() finally processes the entities that are flagged to be added or removed, and updates the systems accordingly.
		void Update();

		// Entity management functions
		Entity createEntity();

		//Component management functions
		template <typename TComponent, typename ...TArgs> void addComponent(Entity entity, TArgs&& ...args);
		template <typename TComponent> void removeComponent(Entity entity);
		template <typename TComponent> bool hasComponent(Entity entity) const;

		// System management functions
		template <typename TSystem, typename ...TArgs> void addSystem(TArgs&& ... args);
		template <typename TSystem> void removeSystem();
		template <typename TSystem> bool hasSystem() const;
		template <typename TSystem> TSystem& getSystem() const;

		// Helper function to add an entity to all systems that it qualifies for based on its component signature.
		void addEntityToSystems(Entity entity);
};

template<typename tComponent>
void System::requireComponent() {
	const auto componentId = Component<tComponent>::getId();
	// Set the bit corresponding to the component type T in the component signature.
	componentSignature.set(componentId);
}

template <typename TSystem, typename ...TArgs> 
void Registry::addSystem(TArgs&& ... args) {

	std::shared_ptr<TSystem> new System = std::make_shared<TSystem>(std::forward<TArgs>(args)...);
	systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
}

template <typename TSystem> 
void Registry::removeSystem() {
	auto system = systems.find(std::type_index(typeid(TSystem)));
	systems.erase(system);
}

template <typename TSystem> 
bool Registry::hasSystem() const {
	return systems.find(std::type_index(typeid(TSystem))) != systems.end();
}

template <typename TSystem> 
TSystem& Registry::getSystem() const {
	auto system = systems.find(std::type_index(typeid(TSystem)));
	return *(std::static_pointer_cast<TSystem>(system->second));
}

template <typename TComponent, typename ...TArgs> 
void Registry::addComponent(Entity entity, TArgs&& ...args) {
	// Get the unique ID for the component type TComponent and the entity ID.
	const auto componentId = Component<TComponent>::getId();
	const auto entityId = entity.getId();

	// Ensure that the componentPools vector is large enough to hold a pool for this component type.
	if (componentId >= componentPools.size()) {
		componentPools.resize(componentId + 1, nullptr);
	}

	// Ensure that the entityComponentSignatures vector is large enough to hold a signature for this entity.
	if (!componentPools[componentId]) {
		std::shared_ptr<Pool<TComponent>> newComponentPool = std::make_shared<Pool<TComponent>>();
		componentPools[componentId] = newComponentPool;
	}

	// Get the component pool for this component type.
	std::shared_ptr<Pool<TComponent>> componentPool = std::static_pointer_cast<Pool<TComponent>>(componentPools[componentId]);

	// Ensure that the component pool is large enough to hold a component for this entity.
	if (entityId >= componentPool->getSize()) {
		componentPool->resize(numEntities);
	}

	// Crete a new component of type TComponent using the provided arguments.
	TComponent newComponent(std::forward<TArgs>(args)...);

	// Set the component for this entity in the component pool and update the entity's signature to reflect that it now has this component.
	componentPool->set(entityId, newComponent);
	// Turn on the bit corresponding to the component type TComponent in the entity's signature.
	entityComponentSignatures[entityId].set(componentId);

	Logger::Log("Added component of type " + std::string(componentId) + " to entity ID  " + std::to_string(entityId));
}

template <typename TComponent>
void Registry::removeComponent(Entity entity) {
	const auto componentId = Component<TComponent>::getId();
	const auto entityId = entity.getId();

	entityComponentSignatures[entityId].set(componentId, false);
}

template <typename TComponent>
bool Registry::hasComponent(Entity entity) const {
	const auto componentId = Component<TComponent>::getId();
	const auto entityId = entity.getId();

	return entityComponentSignatures[entityId].test(componentId);
}