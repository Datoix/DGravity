#include "DGravity/Physics/Orbit.hpp"

namespace DGravity::Physics {
	Orbit::Orbit(int length_, float color_[4]) {
		length = length_;
		
		color = color_;
		points = new Vec2[length];
	}

	void Orbit::Add(const Vec2& v) {
		if (++current == length) {
			current = 0;
			isFull = true;
		}

		points[current].x = v.x;
		points[current].y = v.y;
	}

	void Orbit::Render(GraphicsManager* g) {
		if (current <= 0) return;

		g->SetColor(Color(color));

		Vec2 prev = g->Scale(points[current]);

		int i = current - 1;

		while (i != current) {
			Vec2 scaled = g->Scale(points[i]);
		
			g->DrawLine(prev, scaled);
			prev = scaled;

			if (--i < 0) {
				if (!isFull) {
					break;
				} else {
					i = length - 1;
				}
			}
		}
	}
	
	void Orbit::Clear() {
		isFull = false;
		current = -1;
	}
}