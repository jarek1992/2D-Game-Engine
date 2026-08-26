#pragma once

class movementSystem : public System {
	public:
		movementSystem() {
			//RequireComponent<transformComponent>();
			//...
		}

		void Update() {
			// Update all entities with a transformComponent
			//for(auto entity : getEntities()) {
			//	// Update the position based on velocity, input, etc.
			//	// Example: transform.position += velocity * deltaTime;
			//}
		}
};