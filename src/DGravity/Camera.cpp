#include "DGravity/Camera.hpp"

namespace DGravity {
	Camera::Camera(Settings& settings_) : settings(settings_) {
		scale = 1;
	}

	Vec2 Camera::Convert(const Vec2& v) {
		return v * settings.scale * settings.scaleMultiplier + position;
	}
}