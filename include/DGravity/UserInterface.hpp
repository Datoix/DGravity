#pragma once

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>
#include <vector>
#include <string>
#include "DGravity/Physics/Universe.hpp"
#include "DGravity/Physics/Body.hpp"
#include "DGravity/Application.hpp"

namespace DGravity {
	class Application;

	class UserInterface {
		private:
			Application& application;
			
			char openPath[100] = "";
			char savePath[100] = "";

			void RenderMenuBar();
			void RenderSettings();
			void RenderBodyConfigs();
			void RenderInfo();
		public:
			UserInterface(Application& application);

			void Render();
	};
}