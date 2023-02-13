#pragma once

#include <iostream>
#include "DGravity/Utils.hpp"
#include "DGravity/Settings.hpp"
#include "DGravity/Physics/Orbit.hpp"
#include "DGravity/GraphicsManager.hpp"

namespace DGravity::Physics {
	struct BodyConfig {
		const char* name = "Untitled";
		double mass = 1;
		int radius = 1;
		Vec2 position = Vec2(0, 0);
		Vec2 velocity = Vec2(0, 0);

		float color[4] = { 1.0, 1.0, 1.0, 1.0 };
	};

	class Body {
		private:
			Vec2 acceleration;
			Settings& settings;

			int orbitCounter = 0;
		public:
			char name[50];
			double mass;
			int radius;
			Vec2 position;
			Vec2 velocity;

			bool drawOrbit { true };

			Orbit orbit;
			float color[4];
			
			Body(BodyConfig& config_, Settings& settings);

			Vec2 Interact(Body* body);
			void SetAcceleration(const Vec2& a);
			void Update(int time);
			void Render(GraphicsManager* g);
	};
}