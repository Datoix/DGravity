#include "DGravity/Application.hpp"
#include "DGravity/Settings.hpp"

int main(int argc, char* argv[]) {
	DGravity::Settings settings;
	 
	DGravity::ApplicationConfig appConfig = { 
		"DGravity", 
		1200, 700,
		SDL_INIT_VIDEO,
		SDL_WINDOW_RESIZABLE,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC,
		settings
	};

	DGravity::Application app(appConfig);
	app.Run();

	return 0;
}
