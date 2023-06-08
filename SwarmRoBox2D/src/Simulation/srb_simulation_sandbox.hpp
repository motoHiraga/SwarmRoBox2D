/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#ifndef SIMULATION_SRB_SIMULATION_SANDBOX_HPP_
#define SIMULATION_SRB_SIMULATION_SANDBOX_HPP_

#include "../Dynamics/srb_simulation.hpp"
#include "../Object/srb_arena.hpp"
#include "../Object/srb_item.hpp"
#include "../Object/srb_robot_sandbox.hpp"

class srbSimulationSandbox: public srbSimulation
{
public:
	srbSimulationSandbox(srbSettings *settings);
	virtual ~srbSimulationSandbox()
	{
	}
	void Step();

	srbArena *arena;
	srbItem *item[2];
	srbRobotSB *robot[2];

	b2Body *object[2];
};

#endif /* SIMULATION_SRB_SIMULATION_SANDBOX_HPP_ */
