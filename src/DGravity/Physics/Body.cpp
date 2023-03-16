#include "DGravity/Physics/Body.hpp"

namespace DGravity::Physics {
	Body::Body(BodyConfig& config, Settings& settings_) 
		: orbit(settings_.orbitLength, color), settings(settings_)
	{
		strcpy(name, config.name);

		mass = config.mass;
		radius = config.radius;
		position = config.position; 
		velocity = config.velocity;
		
		color[0] = config.color[0];
		color[1] = config.color[1];
		color[2] = config.color[2];
		color[3] = config.color[3];
	}
	
	Vec2 Body::Interact(Body* body) {
		Vec2 distance = body->position - position;
		
		// F = G*m2/R^2
		double accelerationValue = settings.G * body->mass / (std::pow(distance.Magnitude(), 2));

		return distance.Normalize() * accelerationValue;
	}

	void Body::SetAcceleration(const Vec2& a) {
		acceleration = a;
	}

	void Body::Update(int time) {
		velocity += acceleration * time;

		if (drawOrbit && orbitCounter == settings.orbitStep) {
			orbit.Add(position);
			orbitCounter = 0;
		}
		
		++orbitCounter;
		
		position += velocity * time;
	}

	void Body::Render(GraphicsManager* g) {
		if (settings.showOrbits) {
			orbit.Render(g);
		}

		g->SetColor(Color(color));

		Vec2 scaledPosition = g->Scale(position);
		
		g->DrawCircle(scaledPosition, radius * settings.scaleMultiplier);
	}
}
