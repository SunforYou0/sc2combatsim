	#include "simulator.h"

#include "bots.h"
#include "util.h"
#include "ProjectConfig.h"
#include <sc2api/sc2_api.h>
#include <sc2utils/sc2_manage_process.h>
#include <thread>
#include <chrono>
#include <iostream>
#include "util.h"
//#define SCREENCAPTURE
//#define PATH_SQUAD "D:/scII/sc2combatsim/config//squad.json"
//#define WORK_PATH	"D:/scII/sc2combatsim/config"
//#define REPLAY_PATH "D:/scII/sc2combatsim/config//1.SC2Replay"


int Simulator::Begin() {

	set();
	bool CREATE_FLAG = false;
	// nround 不同剧本的数量
	

	//for (std::filesystem::path file :files) { // While simulation is not finished. cround |-> Z_[1, nround] 
		//std::cout << std::endl << "begin::croung/nround:" << cround << "/" << nround << std::endl;
		std::cout << "launch!" << std::endl;
		_coordinator->LaunchStarcraft();

		std::cout << "start!" << std::endl;
		// maximum 2 player, visions are shared.
		_coordinator->StartGame(config.mapname);

		std::cout << "Game Begins!" << std::endl;
		Update();	// while (simulator.update()){}

		bool properexit;

#if defined(__linux__)
		properexit = false;
#else
		// code to check disconnection in windows OS.
		properexit = true;

		sc2::Agent* sim1 = p1.Bot();
		sc2::Agent* sim2 = p2.Bot();

		if (sim1->Control()->GetAppState() != sc2::AppState::normal ||
			sim2->Control()->GetAppState() != sc2::AppState::normal) {
			std::cout << "sim1 is " << static_cast<int>(sim1->Control()->GetAppState()) << std::endl;
			std::cout << "sim2 is " << static_cast<int>(sim2->Control()->GetAppState()) << std::endl;
			properexit = false;
		}
		if (sim1->Control()->IsInGame() || !sim1->Control()->IsReadyForCreateGame()) {
			std::cout << "sim1 is in game!" << std::endl;
			properexit = false;
		}
		if (sim2->Control()->IsInGame() || !sim2->Control()->IsReadyForCreateGame()) {
			std::cout << "sim2 is in game!" << std::endl;
			properexit = false;
		}
#endif
		// if the game is not properly terminated, do these.
		if (!properexit) {
			std::cout << "Something's wrong! Trying to reset!" << std::endl;
			_coordinator->LeaveGame();
			sc2::SleepFor(1000);

			reset();
		}

		// wait child processes for 1 sec to die.
		sc2::SleepFor(1000);

		cround++;
		std::cout << std::endl << "croung/nround" << cround << std::endl;
	//}
	return 0;
}

int Simulator::Update() {
	bool INGAME_CREATE = true;
	enum {
		onstart,	// 初始化，开启游戏视野。
		onchange,//获取新的小队。
		indelay,	//延迟等待，用于等待尸体消失。
		oncreate,	//创建小队。
		increate,	//等待单位创建完成。
		oncheck,	//检查游戏状态，判断是否有一方被淘汰。
		ingamecreate,//用于等待游戏过程中的创建，防止两个小队同时创建出来
		oncount,	//计算游戏结果。
		onremove,//移除所有小队。
		inremove,//等待所有单位清除。
		onfinish,	//游戏模拟结束。
		infinish	//结束中。

	} simflag = onstart;

	// nframe: frame limit for timeout
	// nbattle: battle limit for one sc2 process. total process time < 6:07:09
	const int32_t nframe = 10000 / stepsize;	// currently 5.5minutes 帧数限制
	const int32_t nbattle = 500; // 200	战斗限制
	const int32_t ndelay = 5;//延迟
	int32_t cframe = 0;
	int32_t cbattle = 0;
	int32_t cdelay = 0;
	int player2_total_num = 0;
	std::vector<std::string> red_tactic;
	std::vector<Util::POS_SQUAD> red_squad_vector;
	int wave_num = 3;
	int wave = 0;	// attack wave
	std::vector<sc2::UnitTypeID> squad_unittypeid1, squad_unittypeid2;	// 类型id，要先找到这个sc2::UnitTypeID
	std::vector<int> squad_quantity1, squad_quantity2;	// 数量
	std::vector<std::string> squad_unit_position1, squad_unit_position2; // 放置位置 
	while (_coordinator->Update()) {
		std::cout << std::hex << simflag << std::dec << std::flush;
#if !defined(__linux__)
		sc2::SleepFor(1);	// to reduce load to cpu and prevent disconnection.
#endif
		// std::cout << cround << std::endl;
		if (simflag != oncheck) {
			recorder.err() << simflag;
		}
		switch (simflag) {
			// initialization, turn on vision
		case onstart: {
			p1.GameInit();
			p2.GameInit();
			p1.ShowMap();
			p2.ShowMap();
			simflag = onchange;
			crepeat = 0; //同一个剧本模拟次数
			break;
		}
					// fetch battles randomly
		case onchange: {
			neednewsquad = true;
			std::cout << "On change" << std::endl;

			wave = 0;
			
			std::cout << "SquadFromJSON && Need New Squad" << std::endl;
			auto& p1comb = p1.combinator();
			auto& p2comb = p2.combinator();
			//std::tie(squad_unittypeid1, squad_quantity1, squad_unit_position1, squad_unittypeid2, squad_quantity2, squad_unit_position2) = Util::ReadPresetJSONSquad(PATH_SQUAD);
			std::tie( red_squad_vector, squad_unittypeid2, squad_quantity2, squad_unit_position2) = Util::ReadPresetJSONSquadWithTactic(squad_path);
			for (int player2_num : squad_quantity2) {
				player2_total_num += player2_num;
			}
			squad_unittypeid1 = red_squad_vector[wave].unit_id;
			squad_quantity1 = red_squad_vector[wave].num;
			squad_unit_position1 = red_squad_vector[wave].pos;

			p1comb.load_predefined_squad(squad_unittypeid1, squad_quantity1); //加载定义好的
			p2comb.load_predefined_squad(squad_unittypeid2, squad_quantity2);
			//neednewsquad = false;
			//std::cout << "p1comb.size:" << std::get<0>(p1comb.get_squad()).size()  << std::endl;

#if !defined(__linux__)
			cdelay = ndelay;
#endif
			simflag = indelay;
			break;
		}
					 // delay for waiting dead body to disappear
		case indelay: {
			std::cout << "indelay" << std::endl;
			if (cdelay) {
				cdelay--;
			}
			else {
				simflag = oncreate;
			}
			break;
		}
					// create units for battle
		case oncreate: {
			std::cout << "on create" << std::endl;
			auto& p1comb = p1.combinator();
			auto& p2comb = p2.combinator();
			std::tie(squad_unittypeid1, squad_quantity1) = p1comb.get_squad();
			std::tie(squad_unittypeid2, squad_quantity2) = p2comb.get_squad();
			//p1.PlaceUnits(squad_unittypeid1, squad_quantity1);
			//p2.PlaceUnits(squad_unittypeid2, squad_quantity2);
			std::cout << "should create here" << std::endl;
			p1.PlaceUnitsPOS(squad_unittypeid1, squad_quantity1, squad_unit_position1);
			p2.PlaceUnitsPOS(squad_unittypeid2, squad_quantity2, squad_unit_position2);
			wave++;
			simflag = increate;
			break;
		}
					 // wait until the units to be created,
					 // because units are not created instantly.
		case increate: {
			//std::cout << "in create" << std::endl;
			size_t sim1size = p1.CountPlayerUnit();
			size_t sim2size = p2.CountPlayerUnit();
			//std::cout << "sim1size:" << sim1size << "	" << "sim2size:" << sim2size << std::endl;
			if (sim1size != 0 && sim2size != 0) {
				
				cframe = 0;
				simflag = oncheck;
#if !defined(__linux__)
#ifdef SCREENCAPTURE
				const std::string imgname1 =
					config.outpath + "/s" + std::to_string(config.squadoffset + cround) + "_a" + std::to_string(crepeat) + ".png";
				const std::string imgname2 =
					config.outpath + "/s" + std::to_string(config.squadoffset + cround) + "_b" + std::to_string(crepeat) + ".png";

				// TODO: Move Camera Properly (on CvC)
				p1.MoveCamera();
				p1.ScreenCapture(imgname1);
				p2.MoveCamera();
				p2.ScreenCapture(imgname2);
#endif // SCREENCAPTURE
#endif // !defined(__linux__)
			}
			break;
		}
					 // check if one side is eliminated.
		case oncheck: {

			size_t sim1size = p1.CountPlayerUnit();
			size_t sim2size = p2.CountPlayerUnit();
			// in battle
			cframe++;
			if (cframe < nframe) {
				if (sim2size < 0.2 * player2_total_num) {
					//原判定条件sim2size == 0
					std::cout << "player2 lose" << std::endl;
					simflag = oncount;
				}
				else {
					//player2 exist

					if (sim1size == 0) {
						std::cout << "player1 dead" << std::endl;
						if (wave < wave_num) {
							//player1 策略没用完，player1当前小队全部阵亡，创建下一小队units
							std::cout << "player2 not defeated && player1 have other tactics" << std::endl;
							//player1被团灭，需要创建player1的新单位
							std::cout << std::endl << "Total wave:" << wave_num << "current wave:" << (wave + 1) << std::endl;
							auto& p1comb = p1.combinator();
							squad_unittypeid1 = red_squad_vector[wave].unit_id;
							squad_quantity1 = red_squad_vector[wave].num;
							squad_unit_position1 = red_squad_vector[wave].pos;
							wave++;
							p1comb.load_predefined_squad(squad_unittypeid1, squad_quantity1); //加载定义好的

							if (SquadFromJSON) {
								std::tie(squad_unittypeid1, squad_quantity1) = p1comb.get_squad();
								p1.PlaceUnitsPOS(squad_unittypeid1, squad_quantity1, squad_unit_position1);

							}
							int create_unit_num = 0;
							for (auto& num : squad_quantity1) {
								create_unit_num += num;
							}
							std::cout << "Should create " << create_unit_num << " units" << std::endl;
							simflag = ingamecreate;//切换到ingamecreate等待创建完成
						}
						else {
							std::cout << "player1 have no other tactics" << std::endl;
							//player1没有策略了，就看是否有player团灭，团灭则准备结束
							if (sim1size == 0 || sim2size <0.2*player2_total_num) {

								simflag = oncount;
							}
						}


					}
					else
					{
						//player1,player2都存在
					}
				}
			}
			else {//frame 超出设定范围，结束
				std::cout << " elapsed frames: " << cframe << std::endl;
				simflag = oncount;
				//break;
			}

			break;
		}
		case ingamecreate: {
			//std::cout << "in create" << std::endl;
			size_t sim1size = p1.CountPlayerUnit();
			size_t sim2size = p2.CountPlayerUnit();
			//std::cout << "sim1size:" << sim1size << "	" << "sim2size:" << sim2size << std::endl;
			if (sim1size != 0) {
				cframe++;
				simflag = oncheck;
#if !defined(__linux__)
#ifdef SCREENCAPTURE
				const std::string imgname1 =
					config.outpath + "/s" + std::to_string(config.squadoffset + cround) + "_a" + std::to_string(crepeat) + ".png";
				const std::string imgname2 =
					config.outpath + "/s" + std::to_string(config.squadoffset + cround) + "_b" + std::to_string(crepeat) + ".png";

				// TODO: Move Camera Properly (on CvC)
				p1.MoveCamera();
				p1.ScreenCapture(imgname1);
				p2.MoveCamera();
				p2.ScreenCapture(imgname2);
#endif // SCREENCAPTURE
#endif // !defined(__linux__)
			}
			cdelay = ndelay;

			break;
		}
		case oncount: {
			size_t sim1size = p1.CountPlayerUnit();
			size_t sim2size = p2.CountPlayerUnit();
			std::cout << "on count" << std::endl;
			std::string result;
			// timeout
			if (cframe >= nframe) {
				result = "timeout";
			}
			// sim1 win
			else if (sim1size != 0) {
				result = "p1_win";
			}
			// sim2 win
			else if (sim2size != 0) {
				result = "p2_win";
			}
			// draw
			else {
				result = "draw";
			}
			cbattle++;
			crepeat++;

			std::cout << "Result:" << result << std::endl;
			std::cout << "crepeat:" << crepeat << ",nrepeat" << nrepeat << std::endl;
			std::cout << "cround:" << cround << ",nround" << nround << std::endl;
			std::cout << "cbattle:" << cbattle << ",nbattle" << nbattle << std::endl;
			recorder.record_result(p1, p2, result, cframe);
			/*
			if (crepeat >= nrepeat) {
				std::cout << "branch:crepeat >= nrepeat" << std::endl;
				recorder.writefile(config.outpath + "/r_" + std::to_string(config.squadoffset + cround) + ".json");
				recorder.clear();
				//neednewsquad = true;
				cround++; // after printing, count the rounds.
			}
			*/
			//if (cround <= nround && cbattle < nbattle) {
			if (crepeat < nrepeat) {
				std::cout << "crepeat < nrepeat" << std::endl;
				simflag = onremove;
				break;
			}
			else { // finish the simulation (and restart if needed).
				std::cout << "branch:else" << std::endl;
				simflag = onfinish;
				break;
			}
		}
		case onremove: {
			std::cout << "onremove" << std::endl;
			p1.KillPlayerUnit();
			p2.KillPlayerUnit();
			simflag = inremove;
			cdelay = ndelay;

			break;
		}
					 // wait until all units are cleared
		case inremove: {
			std::cout << "inremove" << std::endl;
			size_t sim1size = p1.CountPlayerUnit();
			size_t sim2size = p2.CountPlayerUnit();

			if (sim1size == 0 && sim2size == 0) {
				simflag = onchange;
				std::cout << "!!!from inremove to onchange!!!" << std::endl;
			}
			// to prevent an infinite loop, remove units again
			// (e.g. merging archon is not cleared)
			else if (cdelay) {
				cdelay--;
			}
			else {
				simflag = onremove;
			}
			break;
		}
					 // simulation end
		case onfinish: {
			std::cout << "onfinish" << std::endl;
			sc2::Agent* sim1 = p1.Bot();
			//sim1->Control()->SaveReplay(REPLAY_PATH);
			p1.KillPlayerUnit();
			p2.KillPlayerUnit();
			_coordinator->LeaveGame();
			std::cout << "Leave Game" << std::endl;
			cdelay = 0;
			simflag = infinish;
			std::cout << simflag << std::endl;
			break;
		}
					 // finishing. it takes about 4 steps to finish.
		case infinish: {
			crepeat++;
			cround++;
			//std::cout << std::endl << "Game to finish" << std::endl;

			break;
		}
					 // error
		default: {
			std::cerr << "FATAL: simulation state error." << std::endl;
			exit(1);
			break;
		}
		}

		// Execute debug actions
		p1.SendDebug();
		if (p1.Bot() != p2.Bot()) {
			p2.SendDebug();
		}
	}
	std::cout << "end of a game." << std::endl;
	return 0;
}


Simulator::~Simulator() {
	delete _coordinator;
}

Simulator::Simulator(int argc, char* argv[], const SimulatorConfig& config, std::string path) :
	cround(1),	// 轮次
	crepeat(1),
	neednewsquad(true),
	argc(argc),
	argv(argv),
	config(config),
	nround(config.numround),
	nrepeat(config.numrepeat),
	stepsize(config.stepsize),
	a1(nullptr),
	a2(nullptr),
	_coordinator(nullptr),
	squad_path(path)
{
	
}

void Simulator::set() {
	_coordinator = new sc2::Coordinator();
	//#ifdef SCREENCAPTURE
#if !defined(__linux__)
	sc2::RenderSettings settings(800, 600, 300, 300);
	_coordinator->SetRender(settings);
#endif // !defined(__linux__)
	//#endif // SCREENCAPTURE

	_coordinator->LoadSettings(argc, argv);
	_coordinator->SetWindowSize(960, 720);
	_coordinator->SetRealtime(false);
	_coordinator->SetMultithreaded(true);
	_coordinator->SetStepSize(stepsize);

	p1.SetConfig(config.player1);
	p2.SetConfig(config.player2);
	p1.combinator().set_config(config.combin1);
	p2.combinator().set_config(config.combin2);

	if (config.simmode == SimulatorConfig::SimMode::CvC) {
		a1 = new Camerabot("CameraBot");
		p1.SetBot(a1, 3);
		p2.SetBot(a1, 4);
		_coordinator->SetParticipants({
			CreateParticipant(config.player1.race, a1)
			});
	}
	else if (config.simmode == SimulatorConfig::SimMode::PvC) {
		a1 = new Simbot("PlayerBot");
		a2 = new Camerabot("CameraBot");
		p1.SetBot(a1, 1);
		p2.SetBot(a2, 5);
		_coordinator->SetParticipants({
			CreateParticipant(config.player1.race, a1),
			CreateParticipant(config.player2.race, a2),
			});
	}
	else {  // config.simmode == SimulatorConfig::SimMode::PvP
		a1 = new Simbot("Player1Bot");
		a2 = new Simbot("Player2Bot");
		p1.SetBot(a1, 1);
		p2.SetBot(a2, 2);
		_coordinator->SetParticipants({
			CreateParticipant(config.player1.race, a1),
			CreateParticipant(config.player2.race, a2),
			});
	}

	_coordinator->SetPortStart(config.port);

#ifdef SCREENCAPTURE
#if defined(__linux__)
#if LINUX_USE_SOFTWARE_RENDER
	_coordinator->AddCommandLine("-osmesapath /usr/lib/x86_64-linux-gnu/libOSMesa.so");
#else
	_coordinator->AddCommandLine("-eglpath libEGL.so");
#endif // LINUX_USE_SOFTWARE_RENDER
#endif // defined(__linux__)
#endif // SCREENCAPTURE
}

void Simulator::reset() {
	delete _coordinator;
	if (config.simmode == SimulatorConfig::SimMode::CvC) {
		delete a1;
	}
	else if (config.simmode == SimulatorConfig::SimMode::PvC) {
		delete a1;
	}
	else {  // config.simmode == SimulatorConfig::SimMode::PvP
		delete a1;
		delete a2;
	}
	set();
}

sc2::Coordinator* Simulator::Coordinator() {
	return _coordinator;
}
