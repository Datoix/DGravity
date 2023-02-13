#pragma once

#include "DGravity/Utils.hpp"

namespace DGravity {
	const double AU = 1.496e11; // m

	struct Settings {
		double G = 6.6743e-11;
		double scale = 250 / AU;

		double scaleMultiplier = 1;

		int timeUnit = 6 * 3600;

		int fps = 60;
		int frameDelay = 1000 / fps;

		int timestep = 3600 * 24;
	
		int orbitLength = 2000;
		bool showOrbits = true;
		int orbitStep = 150;

		bool simulationRunning = true;

		float backgroundColor[4] = { 0, 0, 0, 0 };
	};
}