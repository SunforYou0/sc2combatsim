#include "simulator.h"
#include "configurator.h"
#include "util.h"
#include "ProjectConfig.h"
#include <iostream>
#define SquadFolder "D:/scII/sc2combatsim/config/squad"
int main(int argc, char* argv[]) {

	


	std::cout << "SC2Sim version "
		<< SC2CombatSim_VERSION_MAJOR
		<< "."
		<< SC2CombatSim_VERSION_MINOR
		<< std::endl;

	SimulatorConfig config(PATH_CONFIG);
	std::vector<std::filesystem::path> files = Util::get_all_files_with_extension(SquadFolder, ".json");
	for (std::filesystem::path file: files) {
		std::cout << "Simulate Squad file:" << file.string() << "	/	Total file num:" <<files.size()<< std::endl;
		Simulator simulator(argc, argv, config,file.string() );
		simulator.Begin();
	}
	
	

	return 0;
}
