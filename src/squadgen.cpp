
#include "simulator.h"
#include "configurator.h"
#include "util.h"
#include "ProjectConfig.h"
#include <iostream>
#include <fstream>
#define SquadFolder "D:/scII/sc2combatsim/config/squad"
int main(int argc, char* argv[]) {
	std::cout << "SC2SquadGen version " 
		      << SC2CombatSim_VERSION_MAJOR 
		      << "."
		      << SC2CombatSim_VERSION_MINOR 
		      << std::endl;
	SimulatorConfig config(PATH_CONFIG);
	Simulator simulator(argc, argv, config,"");

	simulator.squadgen();

	return 0;
}


void Simulator::squadgen(){
    
    set();
    
    int ngen = 20000;

	std::cout << "launch!" << std::endl;
	Coordinator()->LaunchStarcraft();

	std::cout << "start!" << std::endl;
    Coordinator()->StartGame(config.mapname);

	std::cout << "Game Begins!" << std::endl;

    Coordinator()->Update();
    
    p1.GameInit();
	Combinator &cb = p1.combinator();
	Util::GenerateMassSquad(SquadFolder,cb);
    
    return;
}
