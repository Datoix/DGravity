#include "DGravity/GraphicsManager.hpp"

namespace DGravity {
	GraphicsManager::GraphicsManager(Settings& settings_, SDL_Renderer* renderer_)
		: settings(settings_), camera(settings_) 
	{
		renderer = renderer_;
		OnResize(GetSize());
	}
	
	Camera& GraphicsManager::GetCamera() {
		return camera;
	}

	Vec2 GraphicsManager::GetSize() {
		int w, h;
		SDL_GetRendererOutputSize(renderer, &w, &h);

		return Vec2(w, h);
	}

	void GraphicsManager::OnResize(const Vec2& size) {
		Vec2 center = size / 2;
		camera.position = center;
	}

	void GraphicsManager::Show() {
		SDL_RenderPresent(renderer);
	}

	void GraphicsManager::Clear() {
		SDL_RenderClear(renderer);
	}

	void GraphicsManager::SetColor(Color color) {
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		currentColor = color;
	}

	void GraphicsManager::DrawCircle(const Vec2& position, int radius) {
		filledCircleRGBA(renderer, 
			position.x, position.y, 
			radius - 1, 
			currentColor.r, currentColor.g, currentColor.b, currentColor.a);
	}

	void GraphicsManager::DrawLine(const Vec2& v1, const Vec2& v2) {
		SDL_RenderDrawLine(renderer, v1.x, v1.y, v2.x, v2.y);
	}

	Vec2 GraphicsManager::Scale(const Vec2& v) {
		return camera.Convert(v);
	}

	void GraphicsManager::ZoomIn(double n) {
		settings.scaleMultiplier *= n;
	}
	
	void GraphicsManager::ZoomOut(double n) {
		settings.scaleMultiplier /= n;
	}
}