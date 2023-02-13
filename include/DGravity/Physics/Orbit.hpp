#pragma once

#include "DGravity/Utils.hpp"
#include "DGravity/GraphicsManager.hpp"

namespace DGravity::Physics {
	class Orbit {
		private:
			Vec2* points;
			int current = -1;
			int length;
			
			bool isFull = false;

			float* color;
		public:
			Orbit(int length, float color[4]);

			void Add(const Vec2& v);
			void Render(GraphicsManager* g);
			void Clear();
	};
}