#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include "DGravity/Utils.hpp"
#include "DGravity/Settings.hpp"
#include "DGravity/Physics/Body.hpp"


namespace DGravity::Physics {
	class Universe {
		private:
			Settings& settings;
		public:
			std::vector<Body*> bodies;

			Universe(Settings& settings_);
			~Universe();

			void Update(int time);
			void Render(GraphicsManager* g);
	};
}