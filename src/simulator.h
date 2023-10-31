#pragma once

#include <sc2api/sc2_api.h>

#include "player.h"
#include "recorder.h"
#include "configurator.h"

class Simulator {
private:
	int argc;
	char** argv;
	const SimulatorConfig config;
	Recorder recorder;

	Player p1;
	Player p2;
	sc2::Agent* a1;
	sc2::Agent* a2;

	bool neednewsquad;
	bool SquadFromJSON;
	const int32_t nround;  // i.e iteration
	const int32_t nrepeat; // number of repetition of same simulation
	int32_t cround;
	int32_t crepeat = 0;
	std::string squad_path;
	const int32_t stepsize;

	sc2::Coordinator* _coordinator;

public:
	~Simulator();
	Simulator(int argc, char* argv[], const SimulatorConfig& config, std::string path);
	sc2::Coordinator* Coordinator();
	void set();
	void reset();
	int Begin();
	int Update();
	void squadgen();
};
