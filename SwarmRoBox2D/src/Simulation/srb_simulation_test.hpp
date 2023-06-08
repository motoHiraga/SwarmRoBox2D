/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#ifndef SIMULATION_SRB_SIMULATION_TEST_HPP_
#define SIMULATION_SRB_SIMULATION_TEST_HPP_

#include "../Dynamics/srb_simulation.hpp"
#include "../Object/srb_arena.hpp"
#include "../Object/srb_item.hpp"
#include "../Object/srb_robot.hpp"

class srbSimulationTest: public srbSimulation
{
public:
	srbSimulationTest(srbSettings *settings, srbNetworkParams* params, int32 seed);
	virtual ~srbSimulationTest()
	{
	}

	static const int32 item_count = 2;
	static const int32 robot_count = 20;

	srbArena *arena;
	srbItem *item[item_count];
	srbRobot *robot[robot_count];

	srbRandomTools rt;
};

#endif /* SIMULATION_SRB_SIMULATION_TEST_HPP_ */
