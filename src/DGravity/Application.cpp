#include "DGravity/Application.hpp"

namespace DGravity {
	Application::Application(ApplicationConfig& config_) : config(config_) {
		graphicsManager = nullptr;
		universe = nullptr;
		window = nullptr;
		renderer = nullptr;
		io = nullptr;
		ui = nullptr;

		selectedBody = nullptr;
	}

	Application::~Application() {
		delete ui;
		delete universe;
		delete graphicsManager;

		ImGui_ImplSDLRenderer_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();

		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
	
	void Application::InitGraphics() {
		SDL_Init(config.initFlags);
		SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

		window = SDL_CreateWindow(
			config.name.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			config.width, 
			config.height,
			config.windowFlags
		);

		renderer = SDL_CreateRenderer(window, -1, config.renderFlags);
		
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		io = &ImGui::GetIO();

		ImGui::StyleColorsDark();

		ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
		ImGui_ImplSDLRenderer_Init(renderer);

		graphicsManager = new GraphicsManager(config.settings, renderer);
		ui = new UserInterface(*this);
	}

	void Application::Update(int time) {
		if (config.settings.simulationRunning) {
			universe->Update(time);
		}
	}

	void Application::Render() {
		graphicsManager->SetColor(Color(config.settings.backgroundColor));
		graphicsManager->Clear();
		
		universe->Render(graphicsManager);
		ui->Render();
		graphicsManager->Show();
	}

	void Application::HandleEvents() {
		SDL_Event e;

		while (SDL_PollEvent(&e)) {
			ImGui_ImplSDL2_ProcessEvent(&e);

			switch (e.type) {
				case SDL_WINDOWEVENT:
					if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
						graphicsManager->OnResize(Vec2(e.window.data1, e.window.data2));
					}
					break;
				case SDL_MOUSEWHEEL:	
					OnMouseWheel(e);
					break;
				case SDL_MOUSEBUTTONDOWN:
					OnButtonDown(e);
					break;
				case SDL_MOUSEBUTTONUP:
					OnButtonUp(e);
					break;
				case SDL_MOUSEMOTION:
					OnMouseMotion(e);
					break;
				case SDL_QUIT:
					isRunning = false;
					break;
			}
		}
	}
	
	std::string* Application::Split(std::string str, char c, int n) {
		std::string* data = new std::string[n];
		int idx = 0;

		for (int i = 0; i < str.length(); ++i) {
			if (str[i] == ';')
				++idx;
			else
				data[idx] += str[i];
		}

		return data;
	}

	void Application::ParseSettings(std::string str) {
		std::string* data = Split(str, ';', 8);
		
		config.settings.scaleMultiplier = std::stod(data[0]);
		config.settings.timestep = std::stoi(data[1]);
		config.settings.showOrbits = std::stoi(data[2]);
		config.settings.simulationRunning = std::stoi(data[3]);

		config.settings.backgroundColor[0] = std::stof(data[4]);
		config.settings.backgroundColor[1] = std::stof(data[5]);
		config.settings.backgroundColor[2] = std::stof(data[6]);
		config.settings.backgroundColor[3] = std::stof(data[7]);
	}

	void Application::ParseBody(std::string str) {
		std::string* data = Split(str, ';', 11);

		Physics::BodyConfig bodyConfig;

		bodyConfig.name = data[0].c_str();
		bodyConfig.mass = std::stod(data[1]);
		bodyConfig.radius = std::stoi(data[2]);
		bodyConfig.position.x = std::stod(data[3]);
		bodyConfig.position.y = std::stod(data[4]);
		bodyConfig.velocity.x = std::stod(data[5]);
		bodyConfig.velocity.y = std::stod(data[6]);

		bodyConfig.color[0] = std::stof(data[7]);
		bodyConfig.color[1] = std::stof(data[8]);
		bodyConfig.color[2] = std::stof(data[9]);
		bodyConfig.color[3] = std::stof(data[10]);

		universe->bodies.push_back(new Physics::Body(bodyConfig, config.settings));
	}

	void Application::OnMouseWheel(SDL_Event& e) {
		Vec2 mousePosition(e.wheel.mouseX, e.wheel.mouseY);
		Vec2 mid = graphicsManager->GetSize() / 2;
		Vec2 diff = mousePosition - mid;

		graphicsManager->GetCamera().position += -diff.Normalize() * panSpeed;

		if (e.wheel.y > 0) {
			graphicsManager->ZoomIn(1.1);
			panSpeed *= 1.05;
		}

		if (e.wheel.y < 0) {
			graphicsManager->ZoomOut(1.1);
			panSpeed /= 1.05;
		}
	}

	void Application::OnButtonDown(SDL_Event& e) {
		if (e.button.button == SDL_BUTTON_MIDDLE) {
			isMiddleButtonPressed = true;
			midBtnPressedPosition.x = e.button.x;
			midBtnPressedPosition.y = e.button.y;
		}

		if (e.button.button == SDL_BUTTON_RIGHT) {
			Vec2 mousePosition(e.button.x, e.button.y);

			for (Physics::Body* body : universe->bodies) {
				Vec2 pixelPosition = graphicsManager->GetCamera().Convert(body->position);

				if ((mousePosition - pixelPosition).Magnitude() <= body->radius * config.settings.scaleMultiplier) {
					selectedBody = body;
					selectedBody->drawOrbit = false;
					break;
				}
			}
		}
	}

	void Application::OnButtonUp(SDL_Event& e) {
		if (e.button.button == SDL_BUTTON_MIDDLE) {
			isMiddleButtonPressed = false;
		}

		if (e.button.button == SDL_BUTTON_RIGHT && selectedBody != nullptr) {
			selectedBody->drawOrbit = true;
			selectedBody = nullptr;
		}
	}  
	
	void Application::OnMouseMotion(SDL_Event& e) {
		if (isMiddleButtonPressed) {
			Vec2 mousePosition(e.button.x, e.button.y);

			graphicsManager->GetCamera().position += mousePosition - midBtnPressedPosition;
			midBtnPressedPosition.x = mousePosition.x;
			midBtnPressedPosition.y = mousePosition.y;
		}

		if (selectedBody != nullptr) {
			Vec2 mousePosition(e.button.x, e.button.y);
			Vec2 realPosition = (mousePosition - graphicsManager->GetCamera().position) 
				/ config.settings.scale / config.settings.scaleMultiplier;
			selectedBody->position = realPosition;
		}
	}
	
	void Application::Run() {
		universe = new Physics::Universe(config.settings);
		InitGraphics();

		int updateTime = config.settings.timeUnit / config.settings.fps;

		while (isRunning) {
			Uint32 frameStart = SDL_GetTicks();

			HandleEvents();

			for (int i = 0; i < config.settings.timestep / config.settings.timeUnit; ++i) {
				Update(updateTime);
			}
			Render();

			int frameTime = SDL_GetTicks() - frameStart;

			if (config.settings.frameDelay > frameTime) {
				SDL_Delay(config.settings.frameDelay - frameTime);
			}
		}
	}
	
	void Application::OpenFile(std::string path) {
		try {
			std::ifstream file(path);
			
			delete universe;
			universe = new Physics::Universe(config.settings);

			std::string line;
			while (std::getline(file, line)) {
				if (line[0] != '[') continue;

				std::string title;

				int i;
				for (i = 0; i < line.length(); ++i) {
					title += line[i];
					if (line[i] == ']') break;
				}

				if (title == "[settings]") {
					ParseSettings(line.substr(i + 1));
				} else if (title == "[body]") {
					ParseBody(line.substr(i + 1));
				}
			}
		} catch (std::exception e) {
			std::cout << e.what();
		}
	}

	void Application::SaveFile(std::string path) {
		try {
			std::ofstream file(path);

			file << "[settings]";
			file << config.settings.scaleMultiplier << ";";
			file << config.settings.timestep << ";";
			file << config.settings.showOrbits << ";";
			file << config.settings.simulationRunning << ";";

			file << config.settings.backgroundColor[0] << ";";
			file << config.settings.backgroundColor[1] << ";";
			file << config.settings.backgroundColor[2] << ";";
			file << config.settings.backgroundColor[3];
			
			for (Physics::Body* body : universe->bodies) {
				file << "\n[body]";

				file << body->name << ";";
				file << body->mass << ";";
				file << body->radius << ";";
				file << body->position.x << ";";
				file << body->position.y << ";";
				file << body->velocity.x << ";";
				file << body->velocity.y << ";";

				file << body->color[0] << ";";
				file << body->color[1] << ";";
				file << body->color[2] << ";";
				file << body->color[3];
			}
		} catch (std::exception e) {
			std::cout << e.what();
		}
	}

}