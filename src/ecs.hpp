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
		Signature& getComponentSignature() const;

		// Defines the components that an entity must have to be added to this system.
		template<typename tComponent> void requireComponent();
};

class Registry {

};

template<typename tComponent>
void System::requireComponent() {
	const auto componentId = Component<tComponent>::getId();
	// Set the bit corresponding to the component type T in the component signature.
	componentSignature.set(componentId);
}