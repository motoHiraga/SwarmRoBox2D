/*
 * SwarmRoBox2D
 * Author: Motoaki Hiraga
 */

#include "srb_simulation_test.hpp"

srbSimulationTest::srbSimulationTest(srbSettings *settings,
		srbNetworkParams *params, int32 seed) :
		srbSimulation(settings)
{
	/// Initialize random tools.
	rt.SetSeed(seed);
//	rt.SetSeed(time(NULL));
	rt.Refresh();

	{
		srbArenaConf ac;
		arena = (srbArena*) CreateObject(&ac);
	}

	{
		b2CircleShape shape;
		srbItemConf ic;
		ic.mainBodyConf.shape = &shape;
		ic.mainBodyConf.circleShape.m_radius = 4.0f;
		ic.mainBodyConf.density = 0.07f;
		ic.position.Set(10.0f, 5.0f);
		item[0] = (srbItem*) CreateObject(&ic);

		ic.position.Set(-10.0f, 5.0f);
		item[1] = (srbItem*) CreateObject(&ic);
	}

	{
		srbRobotConf rc;

		for (int32 i = 0; i < robot_count; i++)
		{
			float pos_x = rt.GetRandf() * 40.0f - 20.0f;
			float pos_y = rt.GetRandf() * 15.0f - 25.0f;
			rc.position.Set(pos_x, pos_y);
			rc.random_tools = &rt;
			robot[i] = (srbRobot*) CreateObject(&rc);
			robot[i]->network->SetNetworkParams(params);
			robot[i]->network->SetRobotID(i);
		}
	}

	for (int32 i = 0; i < robot_count; i++)
	{
		for (int32 j = 0; j < robot_count; j++)
		{
			if (i != j)
				robot[i]->omniCamera[0]->AddTarget(robot[j]);
		}
	}

	for (int32 i = 0; i < robot_count; i++)
	{
		for (int32 j = 0; j < item_count; j++)
		{
			robot[i]->omniCamera[1]->AddTarget(item[j]);
		}
	}
}

