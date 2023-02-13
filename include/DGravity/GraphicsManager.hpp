#pragma once

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>

#include "DGravity/Utils.hpp"
#include "DGravity/Camera.hpp"
#include "DGravity/Settings.hpp"

namespace DGravity {
	class GraphicsManager {
		private:
			SDL_Renderer* renderer;
			Camera camera;
			Color currentColor;
			Settings& settings;
		public:
			GraphicsManager(Settings& settings, SDL_Renderer* renderer);
			
			Camera& GetCamera();
			Vec2 GetSize();

			void OnResize(const Vec2& size);
			void Show();
			void Clear();

			void SetColor(Color color);
			void DrawCircle(const Vec2& position, int radius);
			void DrawLine(const Vec2& v1, const Vec2& v2);

			Vec2 Scale(const Vec2& v);
			double Scale(double s);

			void ZoomIn(double n);
			void ZoomOut(double n);
	};
}