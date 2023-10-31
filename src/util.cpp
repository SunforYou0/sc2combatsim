#include "util.h"

#include "lodepng.h"
#include "combinator.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include<algorithm>
#include "json/json.h"
//#define TEST

/*
* struct RED_SQUAD {
	POS_SQUAD wave1;
	POS_SQUAD wave2;
	POS_SQUAD wave3;
	POS_SQUAD wave4;
};
*/


namespace Util {

	template <typename T>
	void PrintVector(std::vector<T>& vec) {
		std::cout << "[";
		for (const T& element : vec) {
			std::cout << element << ",";
		}
		std::cout << "]";

	}
	template <typename Key, typename Value>
	void PrintUnorderedMap(const std::unordered_map<Key, Value>& map) {
		std::cout << "{";
		for (const auto& pair : map) {
			std::cout << "Key: [" << pair.first << "] - Value: [" << pair.second << "],";
		}
		std::cout << "}" << std::endl;
	}


	inline std::unordered_map<std::string, std::unordered_map<std::string, int>> InitUnit() {
		std::unordered_map<std::string, std::unordered_map<std::string, int>>  units_id;
		std::unordered_map<std::string, int> Zerg;
		std::unordered_map<std::string, int> Protoss;
		std::unordered_map<std::string, int> Terran;
		std::unordered_map<std::string, int> Neutral;

		Neutral["BattleStationMineralField"] = 886;
		Neutral["BattleStationMineralField750"] = 887;
		Neutral["CarrionBird"] = 322;
		Neutral["CleaningBot"] = 612;
		Neutral["CollapsibleRockTower"] = 609;
		Neutral["CollapsibleRockTowerDebris"] = 490;
		Neutral["CollapsibleRockTowerDebrisRampLeft"] = 518;
		Neutral["CollapsibleRockTowerDebrisRampRight"] = 517;
		Neutral["CollapsibleRockTowerDiagonal"] = 588;
		Neutral["CollapsibleRockTowerPushUnit"] = 561;
		Neutral["CollapsibleRockTowerPushUnitRampLeft"] = 564;
		Neutral["CollapsibleRockTowerPushUnitRampRight"] = 563;
		Neutral["CollapsibleRockTowerRampLeft"] = 664;
		Neutral["CollapsibleRockTowerRampRight"] = 663;
		Neutral["CollapsibleTerranTower"] = 610;
		Neutral["CollapsibleTerranTowerDebris"] = 485;
		Neutral["CollapsibleTerranTowerDiagonal"] = 589;
		Neutral["CollapsibleTerranTowerPushUnit"] = 562;
		Neutral["CollapsibleTerranTowerPushUnitRampLeft"] = 559;
		Neutral["CollapsibleTerranTowerPushUnitRampRight"] = 560;
		Neutral["CollapsibleTerranTowerRampLeft"] = 590;
		Neutral["CollapsibleTerranTowerRampRight"] = 591;
		Neutral["Crabeetle"] = 662;
		Neutral["Debris2x2NonConjoined"] = 475;
		Neutral["DebrisRampLeft"] = 486;
		Neutral["DebrisRampRight"] = 487;
		Neutral["DestructibleBillboardTall"] = 350;
		Neutral["DestructibleCityDebris4x4"] = 628;
		Neutral["DestructibleCityDebris6x6"] = 629;
		Neutral["DestructibleCityDebrisHugeDiagonalBLUR"] = 630;
		Neutral["DestructibleDebris4x4"] = 364;
		Neutral["DestructibleDebris6x6"] = 365;
		Neutral["DestructibleDebrisRampDiagonalHugeBLUR"] = 377;
		Neutral["DestructibleDebrisRampDiagonalHugeULBR"] = 376;
		Neutral["DestructibleIce4x4"] = 648;
		Neutral["DestructibleIce6x6"] = 649;
		Neutral["DestructibleIceDiagonalHugeBLUR"] = 651;
		Neutral["DestructibleRampDiagonalHugeBLUR"] = 373;
		Neutral["DestructibleRampDiagonalHugeULBR"] = 372;
		Neutral["DestructibleRock6x6"] = 371;
		Neutral["DestructibleRockEx14x4"] = 638;
		Neutral["DestructibleRockEx16x6"] = 639;
		Neutral["DestructibleRockEx1DiagonalHugeBLUR"] = 641;
		Neutral["DestructibleRockEx1DiagonalHugeULBR"] = 640;
		Neutral["DestructibleRockEx1HorizontalHuge"] = 643;
		Neutral["DestructibleRockEx1VerticalHuge"] = 642;
		Neutral["Dog"] = 336;
		Neutral["InhibitorZoneMedium"] = 1958;
		Neutral["InhibitorZoneSmall"] = 1957;
		Neutral["KarakFemale"] = 324;
		Neutral["LabBot"] = 661;
		Neutral["LabMineralField"] = 665;
		Neutral["LabMineralField750"] = 666;
		Neutral["Lyote"] = 321;
		Neutral["MineralField"] = 341;
		Neutral["MineralField450"] = 1961;
		Neutral["MineralField750"] = 483;
		Neutral["ProtossVespeneGeyser"] = 608;
		Neutral["PurifierMineralField"] = 884;
		Neutral["PurifierMineralField750"] = 885;
		Neutral["PurifierRichMineralField"] = 796;
		Neutral["PurifierRichMineralField750"] = 797;
		Neutral["PurifierVespeneGeyser"] = 880;
		Neutral["ReptileCrate"] = 877;
		Neutral["RichMineralField"] = 146;
		Neutral["RichMineralField750"] = 147;
		Neutral["RichVespeneGeyser"] = 344;
		Neutral["Scantipede"] = 335;
		Neutral["ShakurasVespeneGeyser"] = 881;
		Neutral["SpacePlatformGeyser"] = 343;
		Neutral["UnbuildableBricksDestructible"] = 473;
		Neutral["UnbuildablePlatesDestructible"] = 474;
		Neutral["UnbuildableRocksDestructible"] = 472;
		Neutral["UtilityBot"] = 330;
		Neutral["VespeneGeyser"] = 342;
		Neutral["XelNagaDestructibleBlocker8NE"] = 1904;
		Neutral["XelNagaDestructibleBlocker8SW"] = 1908;
		Neutral["XelNagaTower"] = 149;

		Protoss["Adept"] = 311;
		Protoss["AdeptPhaseShift"] = 801;
		Protoss["Archon"] = 141;
		Protoss["Assimilator"] = 61;
		Protoss["AssimilatorRich"] = 1955;
		Protoss["Carrier"] = 79;
		Protoss["Colossus"] = 4;
		Protoss["CyberneticsCore"] = 72;
		Protoss["DarkShrine"] = 69;
		Protoss["DarkTemplar"] = 76;
		Protoss["Disruptor"] = 694;
		Protoss["DisruptorPhased"] = 733;
		Protoss["FleetBeacon"] = 64;
		Protoss["ForceField"] = 135;
		Protoss["Forge"] = 63;
		Protoss["Gateway"] = 62;
		Protoss["HighTemplar"] = 75;
		Protoss["Immortal"] = 83;
		Protoss["Interceptor"] = 85;
		Protoss["Mothership"] = 10;
		Protoss["MothershipCore"] = 488;
		Protoss["Nexus"] = 59;
		Protoss["Observer"] = 82;
		Protoss["ObserverSurveillanceMode"] = 1911;
		Protoss["Oracle"] = 495;
		Protoss["Phoenix"] = 78;
		Protoss["PhotonCannon"] = 66;
		Protoss["Probe"] = 84;
		Protoss["Pylon"] = 60;
		Protoss["PylonOvercharged"] = 894;
		Protoss["RoboticsBay"] = 70;
		Protoss["RoboticsFacility"] = 71;
		Protoss["Sentry"] = 77;
		Protoss["ShieldBattery"] = 1910;
		Protoss["Stalker"] = 74;
		Protoss["Stargate"] = 67;
		Protoss["StasisTrap"] = 732;
		Protoss["Tempest"] = 496;
		Protoss["TemplarArchive"] = 68;
		Protoss["TwilightCouncil"] = 65;
		Protoss["VoidRay"] = 80;
		Protoss["WarpGate"] = 133;
		Protoss["WarpPrism"] = 81;
		Protoss["WarpPrismPhasing"] = 136;
		Protoss["Zealot"] = 73;


		Terran["Armory"] = 29;
		Terran["AutoTurret"] = 31;
		Terran["Banshee"] = 55;
		Terran["Barracks"] = 21;
		Terran["BarracksFlying"] = 46;
		Terran["BarracksReactor"] = 38;
		Terran["BarracksTechLab"] = 37;
		Terran["Battlecruiser"] = 57;
		Terran["Bunker"] = 24;
		Terran["CommandCenter"] = 18;
		Terran["CommandCenterFlying"] = 36;
		Terran["Cyclone"] = 692;
		Terran["EngineeringBay"] = 22;
		Terran["Factory"] = 27;
		Terran["FactoryFlying"] = 43;
		Terran["FactoryReactor"] = 40;
		Terran["FactoryTechLab"] = 39;
		Terran["FusionCore"] = 30;
		Terran["Ghost"] = 50;
		Terran["GhostAcademy"] = 26;
		Terran["GhostAlternate"] = 144;
		Terran["GhostNova"] = 145;
		Terran["Hellion"] = 53;
		Terran["Hellbat"] = 484;
		Terran["KD8Charge"] = 830;
		Terran["Liberator"] = 689;
		Terran["LiberatorAG"] = 734;
		Terran["MULE"] = 268;
		Terran["Marauder"] = 51;
		Terran["Marine"] = 48;
		Terran["Medivac"] = 54;
		Terran["MissileTurret"] = 23;
		Terran["Nuke"] = 58;
		Terran["OrbitalCommand"] = 132;
		Terran["OrbitalCommandFlying"] = 134;
		Terran["PlanetaryFortress"] = 130;
		Terran["PointDefenseDrone"] = 11;
		Terran["Raven"] = 56;
		Terran["Reactor"] = 6;
		Terran["Reaper"] = 49;
		Terran["Refinery"] = 20;
		Terran["RefineryRich"] = 1960;
		Terran["RepairDrone"] = 1913;
		Terran["SCV"] = 45;
		Terran["SensorTower"] = 25;
		Terran["SiegeTank"] = 33;
		Terran["SiegeTankSieged"] = 32;
		Terran["Starport"] = 28;
		Terran["StarportFlying"] = 44;
		Terran["StarportReactor"] = 42;
		Terran["StarportTechLab"] = 41;
		Terran["SupplyDepot"] = 19;
		Terran["SupplyDepotLowered"] = 47;
		Terran["TechLab"] = 5;
		Terran["Thor"] = 52;
		Terran["ThorHighImpactMode"] = 691;
		Terran["VikingAssault"] = 34;
		Terran["VikingFighter"] = 35;
		Terran["WidowMine"] = 498;
		Terran["WidowMineBurrowed"] = 500;


		Zerg["Baneling"] = 9;
		Zerg["BanelingBurrowed"] = 115;
		Zerg["BanelingCocoon"] = 8;
		Zerg["BanelingNest"] = 96;
		Zerg["BroodLord"] = 114;
		Zerg["BroodLordCocoon"] = 113;
		Zerg["Broodling"] = 289;
		Zerg["BroodlingEscort"] = 143;
		Zerg["Changeling"] = 12;
		Zerg["ChangelingMarine"] = 15;
		Zerg["ChangelingMarineShield"] = 14;
		Zerg["ChangelingZealot"] = 13;
		Zerg["ChangelingZergling"] = 17;
		Zerg["ChangelingZerglingWings"] = 16;
		Zerg["Cocoon"] = 103;
		Zerg["Corruptor"] = 112;
		Zerg["CreepTumor"] = 87;
		Zerg["CreepTumorBurrowed"] = 137;
		Zerg["CreepTumorQueen"] = 138;
		Zerg["Drone"] = 104;
		Zerg["DroneBurrowed"] = 116;
		Zerg["EvolutionChamber"] = 90;
		Zerg["Extractor"] = 88;
		Zerg["ExtractorRich"] = 1956;
		Zerg["GreaterSpire"] = 102;
		Zerg["Hatchery"] = 86;
		Zerg["Hive"] = 101;
		Zerg["Hydralisk"] = 107;
		Zerg["HydraliskBurrowed"] = 117;
		Zerg["HydraliskDen"] = 91;
		Zerg["InfestationPit"] = 94;
		Zerg["InfestedTerran"] = 7;
		Zerg["InfestedTerranBurrowed"] = 120;
		Zerg["InfestedTerranCocoon"] = 150;
		Zerg["Infestor"] = 111;
		Zerg["InfestorBurrowed"] = 127;
		Zerg["Lair"] = 100;
		Zerg["Larva"] = 151;
		Zerg["Locust"] = 489;
		Zerg["LocustFlying"] = 693;
		Zerg["Lurker"] = 502;
		Zerg["LurkerBurrowed"] = 503;
		Zerg["LurkerDen"] = 504;
		Zerg["LurkerCocoon"] = 501;
		Zerg["Mutalisk"] = 108;
		Zerg["NydusCanal"] = 142;
		Zerg["NydusNetwork"] = 95;
		Zerg["Overlord"] = 106;
		Zerg["OverlordTransport"] = 893;
		Zerg["OverlordTransportCocoon"] = 892;
		Zerg["Overseer"] = 129;
		Zerg["OverseerCocoon"] = 128;
		Zerg["OverseerOversightMode"] = 1912;
		Zerg["ParasiticBombDummy"] = 824;
		Zerg["Queen"] = 126;
		Zerg["QueenBurrowed"] = 125;
		Zerg["Ravager"] = 688;
		Zerg["RavagerBurrowed"] = 690;
		Zerg["RavagerCocoon"] = 687;
		Zerg["Roach"] = 110;
		Zerg["RoachBurrowed"] = 118;
		Zerg["RoachWarren"] = 97;
		Zerg["SpawningPool"] = 89;
		Zerg["SpineCrawler"] = 98;
		Zerg["SpineCrawlerUprooted"] = 139;
		Zerg["Spire"] = 92;
		Zerg["SporeCrawler"] = 99;
		Zerg["SporeCrawlerUprooted"] = 140;
		Zerg["SwarmHost"] = 494;
		Zerg["SwarmHostBurrowed"] = 493;
		Zerg["Ultralisk"] = 109;
		Zerg["UltraliskBurrowed"] = 131;
		Zerg["UltraliskCavern"] = 93;
		Zerg["Viper"] = 499;
		Zerg["Zergling"] = 105;
		Zerg["ZerglingBurrowed"] = 119;


		units_id["Neutral"] = Neutral;
		units_id["Protoss"] = Protoss;
		units_id["Terran"] = Terran;
		units_id["Zerg"] = Zerg;

#ifdef UnitTEST
		std::cout << "Unit ids of Protoss,Terran and Zerg:" << std::endl;
		PrintUnorderedMap(units_id["Protoss"]);
		PrintUnorderedMap(units_id["Terran"]);
		PrintUnorderedMap(units_id["Zerg"]);
		std::cout << "Protoss.Stalker:" << units_id["Protoss"]["Stalker"] << std::endl;
#endif // UnitTEST
		return units_id;
	}

	// Convert BGR image (24bpp) to RGB and save as .png
	void save_BGR_image(const std::string& filename, const char* imagedata, int32_t width, int32_t height) {
		int32_t length = width * height * 3; // 3 bytes per pixel

		std::vector<unsigned char> map_RGB(length);
		for (int i = 0; i < length; i += 3) {
			//BRG to RGB
			map_RGB[i] = imagedata[i + 2];
			map_RGB[i + 1] = imagedata[i + 1];
			map_RGB[i + 2] = imagedata[i];
		}

		unsigned error = lodepng::encode(filename, (unsigned char*)map_RGB.data(), width, height, LCT_RGB, 8);
		if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
	}

	std::string gettimestr() {
		time_t rawtime;
		struct tm timeinfo;
		time(&rawtime);
#if defined(_WIN32)
		localtime_s(&timeinfo, &rawtime);
#else
		timeinfo = *localtime(&rawtime);
#endif
		char buffer[80];
		strftime(buffer, 80, "%Y-%m-%d %H-%M-%S", &timeinfo);
		return std::string(buffer);
		/*
		std::ostringstream o;
		o << timeinfo.tm_year + 1900 << '-'
			<< std::setw(2) << std::setfill('0') << timeinfo.tm_mon + 1 << '-'
			<< std::setw(2) << std::setfill('0') << timeinfo.tm_mday << ' '
			<< std::setw(2) << std::setfill('0') << timeinfo.tm_hour << '-'
			<< std::setw(2) << std::setfill('0') << timeinfo.tm_min << '-'
			<< std::setw(2) << std::setfill('0') << timeinfo.tm_sec;
		return o.str();
		*/
	}

	std::tuple<std::vector<sc2::UnitTypeID>, std::vector<int>, std::vector<sc2::UnitTypeID>, std::vector<int> >
		ReadPresetSquad(const std::string& path) {
		std::ifstream fin;

		std::vector<sc2::UnitTypeID> squad_unittypeid1;
		std::vector<int> squad_quantity1;
		std::vector<sc2::UnitTypeID> squad_unittypeid2;
		std::vector<int> squad_quantity2;

		std::string line;
		std::stringstream linestream;
		std::string buffer;

		InitUnit();//unit_id

		std::cout << "\nReading sqauds from : " << path << std::endl;
		fin.open(path);
		if (!fin.good()) {
			std::cout << "Failed to open file." << std::endl;
			fin.close();
			exit(1);
		}

		std::getline(fin, line);
		std::cout << line << std::endl;
		linestream << line;
		while (std::getline(linestream, buffer, ' ')) {
			squad_unittypeid1.push_back(std::stoi(buffer));
		}
		linestream.clear();
		std::getline(fin, line);
		std::cout << line << std::endl;
		linestream << line;
		while (std::getline(linestream, buffer, ' ')) {
			squad_quantity1.push_back(std::stoi(buffer));
		}
		linestream.clear();
		std::getline(fin, line);
		std::cout << line << std::endl;
		linestream << line;
		while (std::getline(linestream, buffer, ' ')) {
			squad_unittypeid2.push_back(std::stoi(buffer));
		}
		linestream.clear();
		std::getline(fin, line);
		std::cout << line << std::endl;
		linestream << line;
		while (std::getline(linestream, buffer, ' ')) {
			squad_quantity2.push_back(std::stoi(buffer));
		}
		fin.close();
		std::cout << squad_unittypeid1.size() << squad_quantity1.size() << squad_unittypeid2.size() << squad_quantity2.size() << std::endl;
		return std::make_tuple(squad_unittypeid1, squad_quantity1, squad_unittypeid2, squad_quantity2);

	}

	std::tuple<std::vector<sc2::UnitTypeID>, std::vector<int>, std::vector<std::string>, std::vector<sc2::UnitTypeID>, std::vector<int>, std::vector<std::string>>
		ReadPresetJSONSquad(const std::string& path) {
		//std::ifstream fin;

		std::vector<sc2::UnitTypeID> squad_unittypeid1;
		std::vector<int> squad_quantity1;
		std::vector<std::string> squad_unit_position1;
		std::vector<sc2::UnitTypeID> squad_unittypeid2;
		std::vector<int> squad_quantity2;
		std::vector<std::string> squad_unit_position2;
		std::string line;
		std::stringstream linestream;
		std::string buffer;
		std::unordered_map<std::string, std::unordered_map<std::string, int>> units_id = InitUnit();//unit_id

		std::cout << "\nReading sqauds from : " << path << std::endl;
		Json::Value root;

		// 打开JSON文件
		std::ifstream file(path);
		if (!file.is_open()) {
			std::cerr << "无法打开文件" << std::endl;
			// 返回一个空的Json::Value表示失败
			exit(1);
		}

		// 解析JSON文件
		Json::CharReaderBuilder builder;
		Json::CharReader* reader = builder.newCharReader();
		std::string errs;
		Json::parseFromStream(builder, file, &root, &errs);
		delete reader;

		// 关闭文件
		file.close();

		// 检查解析是否成功
		if (!errs.empty()) {
			std::cerr << "JSON解析错误: " << errs << std::endl;
			// 返回一个空的Json::Value表示失败
			exit(1);
		}
		Json::Value redTeam = root["red"];
		if (redTeam.isArray()) {
			for (const Json::Value& member : redTeam) {

				squad_unittypeid1.push_back(units_id[member["race"].asString()][member["unit"].asString()]);
				squad_quantity1.push_back(member["num"].asInt());
				squad_unit_position1.push_back(member["pos"].asString());

			}
		}
		Json::Value blueTeam = root["blue"];
		if (blueTeam.isArray()) {
			for (const Json::Value& member : blueTeam) {

				squad_unittypeid2.push_back(units_id[member["race"].asString()][member["unit"].asString()]);
				squad_quantity2.push_back(member["num"].asInt());
				squad_unit_position2.push_back(member["pos"].asString());

			}
		}
		std::cout << "squad_unittypeid1.size():`" << squad_unittypeid1.size() << std::endl;

		return std::make_tuple(squad_unittypeid1, squad_quantity1, squad_unit_position1, squad_unittypeid2, squad_quantity2, squad_unit_position2);

	}

	std::tuple< std::vector<POS_SQUAD>, std::vector<sc2::UnitTypeID>, std::vector<int>, std::vector<std::string>>
		ReadPresetJSONSquadWithTactic(const std::string& path) {
		
		std::vector<sc2::UnitTypeID> squad_unittypeid2;
		std::vector<int> squad_quantity2;
		std::vector<std::string> squad_unit_position2;
		std::string line;
		std::stringstream linestream;
		std::string buffer;

		std::vector<POS_SQUAD> red_squad_vector;
		//std::vector<std::string> red_tactic; //红方策略
		std::cout << "\nReading sqauds from : " << path << std::endl;
		Json::Value root;

		std::unordered_map<std::string, std::unordered_map<std::string, int>> units_id = InitUnit();//unit_id


		// 打开JSON文件
		std::ifstream file(path);
		if (!file.is_open()) {
			std::cerr << "无法打开文件" << std::endl;
			// 返回一个空的Json::Value表示失败
			exit(1);
		}

		// 解析JSON文件
		Json::CharReaderBuilder builder;
		Json::CharReader* reader = builder.newCharReader();
		std::string errs;
		Json::parseFromStream(builder, file, &root, &errs);
		delete reader;

		// 关闭文件
		file.close();

		// 检查解析是否成功
		if (!errs.empty()) {
			std::cerr << "JSON解析错误: " << errs << std::endl;
			// 返回一个空的Json::Value表示失败
			exit(1);
		}
		Json::Value redTeam = root["red"];
		//Json::Value tactic = redTeam["tactic"];
		/*
		for (const Json::Value& WaveTactic : tactic) {
			red_tactic.push_back(WaveTactic.asString());
		}
		*/
		// Json::Value red_squad = redTeam["squad"];

		std::vector<Json::Value> RedSquadVector = { redTeam["wave1"], redTeam["wave2"], redTeam["wave3"]};
		int i = 0;
		for (const Json::Value& pos_squad : RedSquadVector) {
			POS_SQUAD pos_squad_struct;

			std::vector<sc2::UnitTypeID> unit_vec;
			std::vector<int> num_vec;
			std::vector<std::string> pos_vec;

			for (const Json::Value& member : pos_squad) {
				//std::cout << member["race"].asString() << std::endl;
				//PrintUnorderedMap(units_id[member["race"].asString()]);
				//std::cout << units_id["Protoss"][member["unit"].asString()] << std::endl;
				unit_vec.push_back(units_id[member["race"].asString()][member["unit"].asString()]);
				num_vec.push_back(member["num"].asInt());
				pos_vec.push_back(member["pos"].asString());
			}

			pos_squad_struct.unit_id = unit_vec;
			pos_squad_struct.num = num_vec;
			pos_squad_struct.pos = pos_vec;

			red_squad_vector.push_back(pos_squad_struct);
		}


		Json::Value blueTeam = root["blue"];
		if (blueTeam.isArray()) {
			for (const Json::Value& member : blueTeam) {

				squad_unittypeid2.push_back(units_id[member["race"].asString()][member["unit"].asString()]);
				squad_quantity2.push_back(member["num"].asInt());
				squad_unit_position2.push_back(member["pos"].asString());
			}
		}
#ifdef TEST
		std::cout << "unit id size::" << units_id.size() << std::endl;
		std::cout << "Let me show you what is in the JSON:" << std::endl;
		std::cout << "Tactics:";
		PrintVector(red_tactic);
		std::cout << "Let me show you what is in the Red Squad:" << std::endl;
		for (POS_SQUAD& element : red_squad_vector) {
			PrintVector(element.unit_id);
			PrintVector(element.num);
			PrintVector(element.pos);
		}
#endif // TEST

		return std::make_tuple(red_squad_vector, squad_unittypeid2, squad_quantity2, squad_unit_position2);
	}
	inline std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_map<std::string, int>>> InitUnitForMassGeneration() {
		std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_map<std::string, int>>>  units_id;
		
		std::unordered_map<std::string, std::unordered_map<std::string, int>> Protoss;
		std::unordered_map<std::string, std::unordered_map<std::string, int>> Terran;
		std::unordered_map<std::string, std::unordered_map<std::string, int>> Zerg;

		std::unordered_map<std::string, int> Protoss_NoArmor;
		std::unordered_map<std::string, int> Protoss_LightArmor;
		std::unordered_map<std::string, int> Protoss_HeavyArmor;
		std::unordered_map<std::string, int> Terran_NoArmor;
		std::unordered_map<std::string, int> Terran_LightArmor;
		std::unordered_map<std::string, int> Terran_HeavyArmor;
		std::unordered_map<std::string, int> Zerg_NoArmor;
		std::unordered_map<std::string, int> Zerg_LightArmor;
		std::unordered_map<std::string, int> Zerg_HeavyArmor;
		
		Protoss_LightArmor["Adept"] = 311;// 圣徒
		Protoss_NoArmor["Archon"] = 141;//执政官	-
		Protoss_HeavyArmor["Colossus"] = 4;//巨像	+
		Protoss_LightArmor["HighTemplar"] = 75;//高阶圣堂武士
		Protoss_HeavyArmor["Immortal"] = 83;//不朽者	+
		Protoss_LightArmor["Sentry"] = 77;//机械哨兵
		Protoss_HeavyArmor["Stalker"] = 74;//追猎者	+
		Protoss_LightArmor["Zealot"] = 73;//狂热者
		Protoss["NoArmor"] = Protoss_NoArmor;
		Protoss["LightArmor"] = Protoss_LightArmor;
		Protoss["HeavyArmor"] = Protoss_HeavyArmor;

		Terran_HeavyArmor["Cyclone"] = 692;//飓风		+
		Terran_NoArmor["Ghost"] = 50;//幽灵	-
		Terran_LightArmor["Hellion"] = 53;//恶火
		Terran_LightArmor["Hellbat"] = 484;//恶蝠
		Terran_HeavyArmor["Marauder"] = 51;//劫掠者		+
		Terran_LightArmor["Marine"] = 48;//陆战队员
		Terran_LightArmor["Reaper"] = 49;//收割者
		Terran_HeavyArmor["SiegeTank"] = 33;//攻城坦克	+
		Terran_HeavyArmor["Thor"] = 52;//雷神		+
		Terran["NoArmor"] = Terran_NoArmor;
		Terran["LightArmor"] = Terran_LightArmor;
		Terran["HeavyArmor"] = Terran_HeavyArmor;


		Zerg_NoArmor["Baneling"] = 9;//爆虫	-
		Zerg_LightArmor["Hydralisk"] = 107;//刺蛇
		Zerg_HeavyArmor["Lurker"] = 502;//潜伏者	+
		Zerg_NoArmor["Queen"] = 126;//虫后	-
		Zerg_NoArmor["Ravager"] = 688;//破坏者	-
		Zerg_HeavyArmor["Roach"] = 110;//蟑螂	+
		Zerg_LightArmor["Ultralisk"] = 109;//跳虫
		Zerg_HeavyArmor["Zergling"] = 105;//雷兽	+
		Zerg["NoArmor"] = Zerg_NoArmor;
		Zerg["LightArmor"] = Zerg_LightArmor;
		Zerg["HeavyArmor"] = Zerg_HeavyArmor;
						
		units_id["Protoss"] = Protoss;
		units_id["Terran"] = Terran;
		units_id["Zerg"] = Zerg;

#ifdef UnitTEST
		std::cout << "Unit ids of Protoss,Terran and Zerg:" << std::endl;
		PrintUnorderedMap(units_id["Protoss"]);
		PrintUnorderedMap(units_id["Terran"]);
		PrintUnorderedMap(units_id["Zerg"]);
		std::cout << "Protoss.Stalker:" << units_id["Protoss"]["Stalker"] << std::endl;
#endif // UnitTEST
		return units_id;
	}

	int GenerateMassSquad(const std::string& path,Combinator &combinator){
		float red_total_mineral = 20000;
		float red_total_gas = 20000;
		float red_total_food = 200;

		float blue_total_mineral = 15000;
		float blue_total_gas = 15000;
		float blue_total_food = 150;
		
		float ResourceRatio[6][3] = { {0.2,0.3,0.5},{0.2,0.5,0.3},{0.3,0.2,0.5},{0.3,0.5,0.2},{0.5,0.2,0.3},{0.5,0.3,0.2} };// 无甲，轻甲，重甲
		std::string	 Race[3] = {"Protoss","Terran","Zerg"};
		
		std::string locations[4][3] = { {"E","S","W"},{"S","W","N"},{"W","N","E"},{"N","E","S"}};//方向轮换
		
		int count = 0;
		
		std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_map<std::string, int>>> units_map=InitUnitForMassGeneration();
		std::unordered_map<std::string, int> blue_armor_num;

		std::cout << "!!!There1111!!!" << std::endl;
		blue_armor_num["NoArmor"] = std::floor(combinator.GetUnitsAffordable(blue_total_mineral * 0.3, blue_total_gas * 0.3, blue_total_food * 0.3, units_map["Zerg"]["NoArmor"]));
		std::cout << "!!!There2222!!!" << std::endl;
		blue_armor_num["LightArmor"] = std::floor(combinator.GetUnitsAffordable(blue_total_mineral * 0.3, blue_total_gas * 0.3, blue_total_food * 0.3, units_map["Zerg"]["LightArmor"]));
		std::cout << "!!!There3333!!!" << std::endl;
		blue_armor_num["HeavyArmor"] = std::floor(combinator.GetUnitsAffordable(blue_total_mineral * 0.4, blue_total_gas * 0.4, blue_total_food * 0.4, units_map["Zerg"]["HeavyArmor"]));

		Json::Value blue;
		std::cout << "!!!There!!!" << std::endl;
		for (const std::string armor_str : { "NoArmor", "LightArmor", "HeavyArmor" })
		{	//blue-player
			std::cout << "!!!There!!!" << std::endl;
			for (const auto& unit : units_map["Zerg"][armor_str]) {
				Json::Value unit_in_wave;
				unit_in_wave["race"] = "Zerg";
				unit_in_wave["unit"] = unit.first;
				unit_in_wave["num"] = static_cast<int>(std::floor(blue_armor_num[armor_str] ));
				unit_in_wave["pos"] = "M";
				blue.append(unit_in_wave);
			}
		}
		
		for (std::string race:Race) {
			//	种族轮换
			std::unordered_map<std::string, std::unordered_map<std::string, int>> RaceUnits = units_map[race];
			for (const auto ratio:ResourceRatio) {
				//	resource ratio 轮换
				// 生成player1的阵容
				// int get_unit_affordable();
				// 护甲类型相同的单位，数量也相同
				
				std::unordered_map<std::string, int> ArmorNums;
				ArmorNums["NoArmor"] = std::floor(combinator.GetUnitsAffordable(red_total_mineral * ratio[0], red_total_gas * ratio[0], red_total_food * ratio[0], RaceUnits["NoArmor"]));
				ArmorNums["LightArmor"] = std::floor(combinator.GetUnitsAffordable(red_total_mineral * ratio[1], red_total_gas * ratio[1], red_total_food * ratio[1], RaceUnits["LightArmor"]));
				ArmorNums["HeavyArmor"] = std::floor(combinator.GetUnitsAffordable(red_total_mineral * ratio[2], red_total_gas * ratio[2], red_total_food * ratio[2], RaceUnits["HeavyArmor"]));

				for (const auto loc:locations) {
					// 波次的位置轮换
					for(const auto num:ResourceRatio){
						//每个波次的数量比例轮换
						
						Json::Value root;
						Json::Value red;
						//Json::Value tactic;
						Json::Value wave1;
						Json::Value wave2;
						Json::Value wave3;
						
						for (const auto armor_str : { "NoArmor", "LightArmor", "HeavyArmor" }) 
						{
							// red-player
							
							for(const auto & unit : RaceUnits[armor_str]) {
								std::cout << " unit name" << unit.first << std::endl;
							Json::Value unit_in_wave_1;
							unit_in_wave_1["race"] = race;
							unit_in_wave_1["unit"] = unit.first;
							unit_in_wave_1["num"] = static_cast<int>(std::floor(ArmorNums[armor_str] * num[0]));
							unit_in_wave_1["pos"] = loc[0];
							wave1.append(unit_in_wave_1);

							Json::Value unit_in_wave_2;
							unit_in_wave_2["race"] = race;
							unit_in_wave_2["unit"] = unit.first;
							unit_in_wave_2["num"] = static_cast<int>(std::floor(ArmorNums[armor_str] * num[1]));
							unit_in_wave_2["pos"] = loc[1];
							wave2.append(unit_in_wave_2);

							Json::Value unit_in_wave_3;
							unit_in_wave_3["race"] = race;
							unit_in_wave_3["unit"] = unit.first;
							unit_in_wave_3["num"] = static_cast<int>(ArmorNums[armor_str] - std::floor(ArmorNums[armor_str] * num[0]) - std::floor(ArmorNums[armor_str] * num[1]));
							unit_in_wave_3["pos"] = loc[2];
							wave3.append(unit_in_wave_3);
						}
						}
						
						red["wave1"] = wave1;
						red["wave2"] = wave2;
						red["wave3"] = wave3;
						root["red"] = red;
						root["blue"] = blue;
						//生成json，写入配置
						std::stringstream ss;
						ss << std::setw(4) << std::setfill('0') << count;
						
						std::ofstream outputFile(path+"\\" + ss.str() + ".json");//count作为编号
						Json::StreamWriterBuilder writer;
						std::string jsonStr = Json::writeString(writer, root);
						outputFile << jsonStr;
						outputFile.close();
						count++;
					}
				}
			}
		}
		return 0;
	}

	std::vector<std::filesystem::path> get_all_files_with_extension(const std::filesystem::path& root, const std::string& ext) {
		std::vector<std::filesystem::path> paths;
		if (std::filesystem::exists(root) && std::filesystem::is_directory(root)) {
			for (const auto& entry : std::filesystem::recursive_directory_iterator(root)) {
				if (entry.is_regular_file() && entry.path().extension() == ext) {
					paths.push_back(entry.path());
				}
			}
		}
		return paths;
	}

}


