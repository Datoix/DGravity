#include "DGravity/UserInterface.hpp"

namespace DGravity {
	UserInterface::UserInterface(Application& application_) 
		: application(application_) {}

	void UserInterface::RenderMenuBar() {
		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				if (ImGui::MenuItem("New")) {
					delete application.universe;
					application.universe = new Physics::Universe(application.config.settings);
				}
				
				if (ImGui::BeginMenu("Open")) {
					ImGui::PushID(0);
					ImGui::InputText("", openPath, 100);
					ImGui::PopID();

					if (ImGui::Button("Open")) {
						application.OpenFile(std::string(openPath));
					}
					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Save")) {
					ImGui::PushID(1);
					ImGui::InputText("", savePath, 100);
					ImGui::PopID();

					if (ImGui::Button("Save")) {
						application.SaveFile(std::string(savePath));
					}
					ImGui::EndMenu();
				}

				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
	}

	void UserInterface::RenderSettings() {
		ImGui::Begin("Settings");

		if (!ImGui::CollapsingHeader("Guide")) {
			RenderInfo();
		}

		Settings& settings = application.config.settings;

		ImGui::SliderInt("Timestep ", &settings.timestep, 3600*24, 99999999);
		ImGui::InputInt("Timestep", &settings.timestep);
		ImGui::Checkbox("Show orbits", &settings.showOrbits);
		ImGui::ColorEdit4("Background", settings.backgroundColor);

		std::string name = settings.simulationRunning ? "Stop" : "Start";
		
		if (ImGui::Button(name.c_str())) {
			settings.simulationRunning = !settings.simulationRunning;
		}

		ImGui::SameLine();
		
		if (ImGui::Button("Add new body")) {
			Physics::BodyConfig config;
			Physics::Body* body = new Physics::Body(config, settings);

			application.universe->bodies.push_back(body);
		}

		if (ImGui::Button("Clear orbits")) {
			for (Physics::Body* body : application.universe->bodies) {
				body->orbit.Clear();
			}
		}

		ImGui::End();
	}

	void UserInterface::RenderBodyConfigs() {
		ImGui::Begin("Bodies");

		for (int i = 0; i < application.universe->bodies.size(); ++i) {
			std::string name = "Body " + std::to_string(i);
			
			if (!ImGui::CollapsingHeader(name.c_str())) {
				ImGui::PushID(i);

				Physics::Body* body = application.universe->bodies[i];

				ImGui::InputText("Name", body->name, 50);
				ImGui::InputDouble("Mass", &body->mass);
				ImGui::SliderInt("Radius", &body->radius, 1, 1000);
				
				ImGui::Text("Position");
				ImGui::InputDouble("pX ", &body->position.x);
				ImGui::InputDouble("pY ", &body->position.y);
				
				ImGui::Text("Velocity");
				ImGui::InputDouble("vX ", &body->velocity.x);
				ImGui::InputDouble("vY ", &body->velocity.y);

				ImGui::ColorEdit4("Color", body->color);
				
				if (ImGui::Button("Delete")) {
					application.universe->bodies.erase(application.universe->bodies.begin() + i);
				}
				
				ImGui::SameLine();
				if (ImGui::Button("Clear orbit")) {
					body->orbit.Clear();
				}

				ImGui::PopID();
			}
		}

		ImGui::End();
	}

	void UserInterface::RenderInfo() {
		ImGui::BulletText("Scroll to zoom in/out");
		ImGui::BulletText("Middle mouse button to navigate around");
		ImGui::BulletText("Right mouse button to move planets");
	}

	void UserInterface::Render() {
		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();

		ImGui::NewFrame();
		
		RenderMenuBar();
		RenderSettings();
		RenderBodyConfigs();
		
		ImGui::Render();
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
	}
}