#pragma once

#include <bitset>
#include <vector>

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
		bool operator ==(const Entity& other) const {
			return id == other.id;
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
		// Vector index == component type ID
		// Pool index == entity ID
		std::vector<iPool*> componentPools;

	public:
		//Registry() = default;
		//~Registry() = default;

		//Entity createEntity();
		//void destroyEntity(Entity entity);
		//void addComponentToEntity(Entity entity, int componentId);
		//void removeComponentFromEntity(Entity entity, int componentId);
		//const Signature& getEntitySignature(Entity entity) const;
};

template<typename tComponent>
void System::requireComponent() {
	const auto componentId = Component<tComponent>::getId();
	// Set the bit corresponding to the component type T in the component signature.
	componentSignature.set(componentId);
}