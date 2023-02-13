#pragma once

#include <SDL.h>
#include <string>
#include "DGravity/Settings.hpp"
#include "DGravity/Physics/Universe.hpp"
#include "DGravity/GraphicsManager.hpp"
#include "DGravity/UserInterface.hpp"

namespace DGravity {
	class UserInterface;

	struct ApplicationConfig {
		std::string name;
		int width;
		int height;

		unsigned int initFlags;
		unsigned int windowFlags;
		unsigned int renderFlags;
		Settings& settings;
	};

	class Application {
		private:
			GraphicsManager* graphicsManager;

			SDL_Window* window;
			SDL_Renderer* renderer;
			ImGuiIO* io;
			UserInterface* ui;

			double panSpeed { 10 };
			bool isMiddleButtonPressed { false };
			Vec2 midBtnPressedPosition;

			Physics::Body* selectedBody;

			bool isRunning { true };

			void InitGraphics();
			void Update(int time);
			void Render();
			void HandleEvents();
			
			std::string* Split(std::string str, char c, int n);
			void ParseSettings(std::string str);
			void ParseBody(std::string str);
			
			void OnMouseWheel(SDL_Event& e);
			void OnButtonDown(SDL_Event& e);
			void OnButtonUp(SDL_Event& e);
			void OnMouseMotion(SDL_Event& e);
		public:
			Application(ApplicationConfig& config_);
			~Application();

			ApplicationConfig& config;
			Physics::Universe* universe;

			void Run();
			void OpenFile(std::string path);
			void SaveFile(std::string path);
	};
}
