#pragma once

#include "DGravity/Utils.hpp"
#include "DGravity/Settings.hpp"

namespace DGravity {
	class Camera {
		private:
			double scale;
			Settings& settings;
		public:
			Vec2 position;
			Camera(Settings& settings_);

			Vec2 Convert(const Vec2& v);
	};
}