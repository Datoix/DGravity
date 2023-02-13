#include "DGravity/Physics/Universe.hpp"

namespace DGravity::Physics {
	Universe::Universe(Settings& settings_) : settings(settings_) {}

	Universe::~Universe() {
		for (Body* body : bodies) {
			delete body;
		}
	}

	void Universe::Update(int time) {
		for (Body* b1 : bodies) {
			Vec2 acceleration = Vec2(0, 0);

			for (Body* b2 : bodies) {
				if (b1 == b2) continue;

				acceleration += b1->Interact(b2);
			}

			b1->SetAcceleration(acceleration);
			b1->Update(time);
		}
	}

	void Universe::Render(GraphicsManager* g) {
		for (Body* body : bodies) {
			body->Render(g);
		}
	}
}